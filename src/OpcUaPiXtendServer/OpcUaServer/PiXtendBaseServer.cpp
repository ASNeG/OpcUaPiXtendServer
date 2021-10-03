/*
   Copyright 2021 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
          Samuel Huebl (Samuel@huebl-sgh.de)
 */

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/ServiceSetApplication/CreateObjectInstance.h"
#include "OpcUaStackServer/ServiceSetApplication/ForwardNodeSync.h"
#include "OpcUaStackServer/ServiceSetApplication/RegisterForwardNode.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendBaseServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/NodeContextDigitalIO.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    PiXtendBaseServer::PiXtendBaseServer(
    	const std::string& typeName,
		uint32_t typeNodeId
	)
    : typeName_(typeName)
    , typeNodeId_(typeNodeId)
    {
    }

    PiXtendBaseServer::~PiXtendBaseServer(void)
    {
    }

    bool
	PiXtendBaseServer::startup(
		OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
		const std::string& instanceName,
		const std::string& namespaceName,
		uint16_t namespaceIndex,
		const OpcUaStackCore::OpcUaNodeId& parentNodeId
	)
    {
    	applicationServiceIf_ = applicationServiceIf;
    	instanceName_ = instanceName;
    	namespaceName_ = namespaceName;
    	namespaceIndex_ = namespaceIndex;
    	parentNodeId_ = parentNodeId;

    	// call specific startup handler
    	if (!handleStartup()) {
    		return false;
    	}

    	// create node context
    	createNodeContext(
    		dOConfigVec_,
			dIConfigVec_,
			aOConfigVec_,
			aIConfigVec_
		);

    	// create object instance in information model
    	if (!createObjectInstance()) {
    		return false;
    	}

    	// register opc ua service functions
    	if (!registerServiceFunctions()) {
    		return false;
    	}

    	return true;
    }

    bool
	PiXtendBaseServer::shutdown(void)
    {
    	// shutdown pixtend interface
    	if (!handleShutdown()) {
    		return false;
    	}

    	return true;
    }

    bool
	PiXtendBaseServer::createObjectInstance(void)
    {
   		//
		// create v2s object instance in opc ua information model
		//
		objectTypeNamespaceName(namespaceName_);
		objectTypeNodeId(OpcUaNodeId(typeNodeId_, namespaceIndex_));
		Object::SPtr obj = shared_from_this();
		CreateObjectInstance createObjectInstance(
			namespaceName_,									// namespace name of the object instance
			OpcUaLocalizedText("", instanceName_),			// display name of the object instance
			parentNodeId_,									// parent node of the object instance
			OpcUaNodeId(OpcUaId_Organizes),					// reference type between object and variable instance
			obj
		);
		if (!createObjectInstance.query(applicationServiceIf_)) {
			Log(Error, "create object response error (query)")
				.parameter("TypeName", typeName_);
			return false;
		}
		if (createObjectInstance.resultCode() != Success) {
			Log(Error, "create PiXtendV2S object response error (result code)")
			    .parameter("ResultCode", createObjectInstance.resultCode())
				.parameter("TypeName", typeName_);
			return false;
		}

    	return true;
    }

    bool PiXtendBaseServer::createNodeContext(
    	const DOConfig::Vec& dOconfigVec,
		const DIConfig::Vec& dIconfigVec,
		const AOConfig::Vec& aOconfigVec,
		const AIConfig::Vec& aIconfigVec
	)
    {
    	for (auto dOConfig : dOconfigVec) {
        	// create server variable and register server variable
           	auto serverVariable = boost::make_shared<ServerVariable>(dOConfig.nodeName_);
        	serverVariables().registerServerVariable(serverVariable);

    		auto rc = createNodeContextDigitalIO(
    			serverVariable,
				dOConfig.nodeName_,
				dOConfig.readFunc_,
				dOConfig.writeFunc_
    		);
    	}

    	for (auto dIConfig : dIconfigVec) {
        	// create server variable and register server variable
           	auto serverVariable = boost::make_shared<ServerVariable>(dIConfig.nodeName_);
        	serverVariables().registerServerVariable(serverVariable);

    		auto rc = createNodeContextDigitalIO(
    			serverVariable,
				dIConfig.nodeName_,
				dIConfig.readFunc_
    		);
    	}

    	for (auto aOConfig : aOconfigVec) {
        	// create server variable and register server variable
           	auto serverVariable = boost::make_shared<ServerVariable>(aOConfig.nodeName_);
        	serverVariables().registerServerVariable(serverVariable);

    		auto rc = createNodeContextAnalogIO(
    			serverVariable,
				aOConfig.nodeName_,
				aOConfig.readFunc_,
				aOConfig.writeFunc_
    		);
    	}

    	for (auto aIConfig : aIconfigVec) {
        	// create server variable and register server variable
           	auto serverVariable = boost::make_shared<ServerVariable>(aIConfig.nodeName_);
        	serverVariables().registerServerVariable(serverVariable);

    		auto rc = createNodeContextAnalogIO(
    			serverVariable,
				aIConfig.nodeName_,
				aIConfig.readFunc_
    		);
    	}

    	return true;
    }

    bool
	PiXtendBaseServer::createNodeContextDigitalIO(
	    ServerVariable::SPtr& serverVariable,
     	const std::string& nodeName,
		NodeContextDigitalIO::ReadFunc readFunc,
		NodeContextDigitalIO::WriteFunc writeFunc
	)
    {
    	// create node context
    	auto nodeContext = boost::make_shared<NodeContextDigitalIO>();
    	nodeContext->setReadFunc(readFunc);
    	nodeContext->setWriteFunc(writeFunc);
    	BaseClass::SPtr context = nodeContext;
    	serverVariable->applicationContext(context);

    	return true;
    }

    bool
	PiXtendBaseServer::createNodeContextDigitalIO(
	    ServerVariable::SPtr& serverVariable,
     	const std::string& nodeName,
		NodeContextDigitalIO::ReadFunc readFunc
	)
    {
    	// create node context
    	auto nodeContext = boost::make_shared<NodeContextDigitalIO>();
    	nodeContext->setReadFunc(readFunc);
    	BaseClass::SPtr context = nodeContext;
    	serverVariable->applicationContext(context);

    	return true;
    }

    bool
	PiXtendBaseServer::createNodeContextAnalogIO(
	    ServerVariable::SPtr& serverVariable,
     	const std::string& nodeName,
		NodeContextAnalogIO::ReadFunc readFunc,
		NodeContextAnalogIO::WriteFunc writeFunc
	)
    {
    	// create node context
    	auto nodeContext = boost::make_shared<NodeContextAnalogIO>();
    	nodeContext->setReadFunc(readFunc);
    	nodeContext->setWriteFunc(writeFunc);
    	BaseClass::SPtr context = nodeContext;
    	serverVariable->applicationContext(context);

    	return true;
    }

    bool
 	PiXtendBaseServer::createNodeContextAnalogIO(
 	    ServerVariable::SPtr& serverVariable,
      	const std::string& nodeName,
 		NodeContextAnalogIO::ReadFunc readFunc
 	)
     {
     	// create node context
     	auto nodeContext = boost::make_shared<NodeContextAnalogIO>();
     	nodeContext->setReadFunc(readFunc);
     	BaseClass::SPtr context = nodeContext;
     	serverVariable->applicationContext(context);

     	return true;
     }

    bool
	PiXtendBaseServer::registerServiceFunctions(void)
    {
    	// get nodeids from digital and analog variables
    	for (auto serverVariable : serverVariables().serverVariableMap()) {
    		auto variable = serverVariable.second;
    		auto applicationContext = variable->applicationContext();
    		if (applicationContext.get() == nullptr) continue;
    		auto nodeContext = boost::static_pointer_cast<NodeContext>(applicationContext);

    		switch (nodeContext->contextType())
    		{
    			case ContextType::DigitalIO:
    			{
    			   	// register service functions for digital variable
    			    RegisterForwardNode registerForwardNode(variable->nodeId());
    			    registerForwardNode.addApplicationContext(applicationContext);
    			    registerForwardNode.setReadCallback(boost::bind(&PiXtendBaseServer::readDigitalValue, this, _1));
    			    registerForwardNode.setWriteCallback(boost::bind(&PiXtendBaseServer::writeDigitalValue, this, _1));
    				registerForwardNode.setMonitoredItemStartCallback(boost::bind(&PiXtendBaseServer::receiveMonotoredItemStart, this, _1));
    				registerForwardNode.setMonitoredItemStopCallback(boost::bind(&PiXtendBaseServer::receiveMonitoredItemStop, this, _1));
    			    if (!registerForwardNode.query(applicationServiceIf_, true)) {
    			    	Log(Error, "register forward node response error");
    			    	return false;
    			    }
    				break;
    			}
    			case ContextType::AnalogIO:
    			{
       			   	// register service functions for analog variable
        			RegisterForwardNode registerForwardNode(variable->nodeId());
        			registerForwardNode.addApplicationContext(applicationContext);
        			registerForwardNode.setReadCallback(boost::bind(&PiXtendBaseServer::readAnalogValue, this, _1));
        			registerForwardNode.setWriteCallback(boost::bind(&PiXtendBaseServer::writeAnalogValue, this, _1));
    				registerForwardNode.setMonitoredItemStartCallback(boost::bind(&PiXtendBaseServer::receiveMonotoredItemStart, this, _1));
    				registerForwardNode.setMonitoredItemStopCallback(boost::bind(&PiXtendBaseServer::receiveMonitoredItemStop, this, _1));
        			if (!registerForwardNode.query(applicationServiceIf_, true)) {
        			    Log(Error, "register forward node response error");
        			    return false;
        			}
    				break;
    			}
    		}
    	}

    	return true;
    }

    void
	PiXtendBaseServer::readDigitalValue(
    	ApplicationReadContext* applicationReadContext
	)
    {
    	auto applicationContext = applicationReadContext->applicationContext_;
    	if (!applicationContext) {
    		applicationReadContext->statusCode_ = BadUnexpectedError;
    		return;
    	}
    	auto nodeContext = boost::static_pointer_cast<NodeContextDigitalIO>(applicationContext);

    	// check if read function exist
    	if (!nodeContext->existReadFunc()) {
    		applicationReadContext->statusCode_ = BadUserAccessDenied;
    		return;
    	}

    	// read pixtend variable
    	auto value = nodeContext->getReadFunc()();

    	// write pixtend variabe to opc ua node
    	OpcUaDataValue dataValue((OpcUaBoolean)value);
    	dataValue.copyTo(applicationReadContext->dataValue_);
    	applicationReadContext->statusCode_ = Success;
    }

    void
	PiXtendBaseServer::writeDigitalValue(
		ApplicationWriteContext* applicationWriteContext
	)
    {
       	auto applicationContext = applicationWriteContext->applicationContext_;
        auto nodeContext = boost::static_pointer_cast<NodeContextDigitalIO>(applicationContext);

        // check if write function exist
        if (!nodeContext->existWriteFunc()) {
        	applicationWriteContext->statusCode_ = BadUserAccessDenied;
        	return;
        }

        // check type of opc ua variable
        OpcUaBoolean value;
        if (!applicationWriteContext->dataValue_.getValue(value)) {
        	applicationWriteContext->statusCode_ = BadTypeMismatch;
        	return;
        }

        // set pixtend variable
        nodeContext->getWriteFunc()((bool)value);
        applicationWriteContext->statusCode_ = Success;
    }

    void
	PiXtendBaseServer::readAnalogValue(
    	ApplicationReadContext* applicationReadContext
	)
    {
    	auto applicationContext = applicationReadContext->applicationContext_;
    	if (!applicationContext) {
    		applicationReadContext->statusCode_ = BadUnexpectedError;
    		return;
    	}
    	auto nodeContext = boost::static_pointer_cast<NodeContextAnalogIO>(applicationContext);

    	// check if read function exist
    	if (!nodeContext->existReadFunc()) {
    		applicationReadContext->statusCode_ = BadUserAccessDenied;
    		return;
    	}

    	// read pixtend variable
    	auto value = nodeContext->getReadFunc()();

    	// write pixtend variabe to opc ua node
    	OpcUaDataValue dataValue(value);
    	dataValue.copyTo(applicationReadContext->dataValue_);
    	applicationReadContext->statusCode_ = Success;
    }

    void
 	PiXtendBaseServer::writeAnalogValue(
 		ApplicationWriteContext* applicationWriteContext
 	)
    {
        auto applicationContext = applicationWriteContext->applicationContext_;
        auto nodeContext = boost::static_pointer_cast<NodeContextAnalogIO>(applicationContext);

        // check if write function exist
        if (!nodeContext->existWriteFunc()) {
         	applicationWriteContext->statusCode_ = BadUserAccessDenied;
         	return;
        }

        // check type of opc ua variable
        double value;
        if (!applicationWriteContext->dataValue_.getValue(value)) {
         	applicationWriteContext->statusCode_ = BadTypeMismatch;
         	return;
        }

         // set pixtend variable
        nodeContext->getWriteFunc()(value);
        applicationWriteContext->statusCode_ = Success;
    }

	void
	PiXtendBaseServer::receiveMonotoredItemStart(
		OpcUaStackCore::ApplicationMonitoredItemStartContext* monitoredItemStartContext
	)
	{
		// FIXME: todo
	}

	void
	PiXtendBaseServer::receiveMonitoredItemStop(
		OpcUaStackCore::ApplicationMonitoredItemStopContext* monitoredItemStopContext
	)
	{
		// FIXME: todo
	}

}
