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

#include <boost/numeric/conversion/cast.hpp>
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/ServiceSetApplication/CreateObjectInstance.h"
#include "OpcUaStackServer/ServiceSetApplication/ForwardNodeSync.h"
#include "OpcUaStackServer/ServiceSetApplication/RegisterForwardNode.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendBaseServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/NodeContext.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendValueContext.h"
#include "OpcUaStackServer/ServiceSetApplication/GetNamespaceInfo.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    PiXtendBaseServer::PiXtendBaseServer(
    	const std::string& typeName,
        const std::string& namespaceName,
		uint32_t typeNodeId
	)
    : typeName_(typeName)
    , namespaceName_(namespaceName)
    , typeNodeId_(typeNodeId)
    {
    }

    PiXtendBaseServer::~PiXtendBaseServer(void)
    {
    }

    bool
	PiXtendBaseServer::startup(
        OpcUaStackCore::IOThread::SPtr& ioThread,
        boost::shared_ptr<boost::asio::io_service::strand>& strand,
		OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
		const std::string& instanceName,
		const OpcUaStackCore::OpcUaNodeId& parentNodeId,
        ContextIndex::SPtr& contextIndex,
        const UnitConversionConfig::Map& unitConversionConfigMap
	)
    {
    	ioThread_ = ioThread;
    	strand_ = strand;
    	applicationServiceIf_ = applicationServiceIf;
    	instanceName_ = instanceName;
    	parentNodeId_ = parentNodeId;
    	contextIndex_ = contextIndex;

        // find namespace
        if (!findNamespace())
        {
            Log(Error, "find namespace error");
            return false;
        }

    	// call specific startup handler
    	if (!handleStartup()) {
    		return false;
    	}

    	// create node context
        createNodeContext(nodePinConfigVec_, unitConversionConfigMap);

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
        const NodePinConfig::Vec& nodePinConfigVec,
        const UnitConversionConfig::Map& unitConversionConfigMap
	)
    {
    	for (auto nodePinConfig : nodePinConfigVec) {
        	// create server variable and register server variable
           	auto serverVariable = boost::make_shared<ServerVariable>(nodePinConfig.nodeName_);
        	serverVariables().registerServerVariable(serverVariable);

        	// find context
        	auto contextName = instanceName_ + "." + nodePinConfig.pinName_;
        	auto hardwareContext = contextIndex_->getContext(contextName);
        	if (hardwareContext.get() == nullptr) {
        		Log(Error, "context not exist in context index")
        			.parameter("ContextName", contextName);
        		return false;
        	}

        	// create node context
        	auto nodeContext = boost::make_shared<NodeContext>();
        	nodeContext->serverVariable(serverVariable);
        	nodeContext->hardwareContext(hardwareContext);
        	BaseClass::SPtr context = nodeContext;
        	serverVariable->applicationContext(context);

            Log(Debug, "create NodeContext")
                    .parameter("NodeName", nodePinConfig.nodeName_)
                    .parameter("ContextName", contextName);

            // check if unit converter information exists
            auto unitConversionConfig = unitConversionConfigMap.find(nodePinConfig.nodeName_);
            if (unitConversionConfig != unitConversionConfigMap.end())
            {
                UnitConverterContext::SPtr unitConverter = boost::make_shared<UnitConverterContext>(
                            unitConversionConfig->second->a(),
                            unitConversionConfig->second->b(),
                            unitConversionConfig->second->c(),
                            unitConversionConfig->second->d());
                nodeContext->unitConverterContext(unitConverter);

                Log(Debug, "create UnitConverterContext")
                        .parameter("NodeName", nodePinConfig.nodeName_)
                        .parameter("A", unitConversionConfig->second->a())
                        .parameter("B", unitConversionConfig->second->b())
                        .parameter("C", unitConversionConfig->second->c())
                        .parameter("D", unitConversionConfig->second->d());
            }
    	}

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

    		// register service functions
    		RegisterForwardNode registerForwardNode(variable->nodeId());
    		registerForwardNode.addApplicationContext(applicationContext);
    		registerForwardNode.setReadCallback(boost::bind(&PiXtendBaseServer::readValue, this, _1));
    		registerForwardNode.setWriteCallback(boost::bind(&PiXtendBaseServer::writeValue, this, _1));
    		registerForwardNode.setMonitoredItemStartCallback(boost::bind(&PiXtendBaseServer::receiveMonotoredItemStart, this, _1));
    		registerForwardNode.setMonitoredItemStopCallback(boost::bind(&PiXtendBaseServer::receiveMonitoredItemStop, this, _1));
    		if (!registerForwardNode.query(applicationServiceIf_, true)) {
    		    Log(Error, "register forward node response error")
    			    .parameter("NodeId", variable->nodeId())
					.parameter("NodeName", serverVariable.first)
					.parameter("ModulName", instanceName_);
    			return false;

    		}
    	}

    	return true;
    }

    void
	PiXtendBaseServer::readValue(
    	ApplicationReadContext* applicationReadContext
	)
    {
	Log(Debug, "receive read request")
	    .parameter("OpcUaNodeId", applicationReadContext->nodeId_);

    	// get node context
    	auto nodeContext = boost::static_pointer_cast<NodeContext>(applicationReadContext->applicationContext_);
    	if (!nodeContext) {
       		applicationReadContext->statusCode_ = BadUnexpectedError;
        	return;
    	}

    	// get hardware context
    	auto hardwareContext = boost::static_pointer_cast<PiXtendValueContext>(nodeContext->hardwareContext());
    	if (!hardwareContext) {
       		applicationReadContext->statusCode_ = BadUnexpectedError;
        	return;
    	}

    	// read pixtend variable
    	applicationReadContext->dataValue_ = hardwareContext->dataValueIn();
    	applicationReadContext->statusCode_ = Success;
    }

    void
	PiXtendBaseServer::writeValue(
		ApplicationWriteContext* applicationWriteContext
	)
    {
	Log(Debug, "receive write request")
	    .parameter("OpcUaNodeId", applicationWriteContext->nodeId_)
	    .parameter("OpcUaDataValue", applicationWriteContext->dataValue_);

       	// get node context
        auto nodeContext = boost::static_pointer_cast<NodeContext>(applicationWriteContext->applicationContext_);
        if (!nodeContext) {
        	applicationWriteContext->statusCode_ = BadUnexpectedError;
            return;
        }

        // get hardware context
        auto hardwareContext = boost::static_pointer_cast<PiXtendValueContext>(nodeContext->hardwareContext());
        if (!hardwareContext) {
        	applicationWriteContext->statusCode_ = BadUnexpectedError;
            return;
        }

    	// check if write function exist
    	if (!hardwareContext->writeAccess()) {
    		applicationWriteContext->statusCode_ = BadUserAccessDenied;
    		return;
    	}

        // write pixtend variable
    	hardwareContext->dataValueOut(applicationWriteContext->dataValue_);
    	applicationWriteContext->statusCode_ = Success;
    }

	void
	PiXtendBaseServer::receiveMonotoredItemStart(
		OpcUaStackCore::ApplicationMonitoredItemStartContext* monitoredItemStartContext
	)
	{
		// handle only the first start monitored item request for one node
		if (!monitoredItemStartContext->firstMonitoredItem_) {
			return;
		}

		// update function to write data value to node
		auto updateFunc = [this](OpcUaDataValue& dataValue, BaseClass::SPtr& context) {
			// get opc ua node base node class
			auto nodeContext = boost::static_pointer_cast<NodeContext>(context);
			auto baseNodeClass = nodeContext->serverVariable()->baseNode().lock();
			if (!baseNodeClass) return;

			// set variable
			Log(Debug, "update variable")
			    .parameter("Name", nodeContext->serverVariable()->name())
			    .parameter("NodeId", nodeContext->serverVariable()->nodeId())
			    .parameter("Data", dataValue);
			baseNodeClass->setValueSync(dataValue);
		};

       	// get node context
        auto nodeContext = boost::static_pointer_cast<NodeContext>(monitoredItemStartContext->applicationContext_);
        if (!nodeContext) {
            return;
        }

        // get hardware context
        auto hardwareContext = boost::static_pointer_cast<PiXtendValueContext>(nodeContext->hardwareContext());
        if (!hardwareContext) {
            return;
        }

        // register update function in hardware context
        hardwareContext->addMonitoredItem(
        	monitoredItemStartContext->nodeId_,
			updateFunc,
			monitoredItemStartContext->applicationContext_
        );

	// read pixtend variable
	auto dataValue = hardwareContext->dataValueIn();
	auto baseNodeClass = nodeContext->serverVariable()->baseNode().lock();
	if (!baseNodeClass) return;

	// set variable to opx ua node
	baseNodeClass->setValueSync(dataValue);
	}

	void
	PiXtendBaseServer::receiveMonitoredItemStop(
		OpcUaStackCore::ApplicationMonitoredItemStopContext* monitoredItemStopContext
	)
	{
		// handle only the last stop monitored item request for one node
		if (!monitoredItemStopContext->lastMonitoredItem_) {
			return;
		}

       	// get node context
        auto nodeContext = boost::static_pointer_cast<NodeContext>(monitoredItemStopContext->applicationContext_);
        if (!nodeContext) {
            return;
        }

        // get hardware context
        auto hardwareContext = boost::static_pointer_cast<PiXtendValueContext>(nodeContext->hardwareContext());
        if (!hardwareContext) {
            return;
        }

        // deregister update function in hardware context
        hardwareContext->delMonitoredItem(
        	monitoredItemStopContext->nodeId_
        );
	}

    bool
    PiXtendBaseServer::findNamespace(void)
    {
        // get namespace list
        GetNamespaceInfo getNamespaceInfo;
        if (!getNamespaceInfo.query(applicationServiceIf_)) {
            Log(Error, "create namespace error")
                    .parameter("NamespaceName", namespaceName_);
            return false;
        }

        int32_t namespaceIndex = getNamespaceInfo.getNamespaceIndex(namespaceName_);
        if (namespaceIndex < 0) {
            Log(Error, "namespace not exist in opc ua information model")
                 .parameter("NamespaceName", namespaceName_);
            return false;
        }
        namespaceIndex_ = (uint16_t)namespaceIndex;

        return true;
    }

}
