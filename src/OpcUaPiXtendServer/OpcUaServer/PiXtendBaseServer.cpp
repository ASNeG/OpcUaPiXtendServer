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
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendBaseServer.h"

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
    	createNodeContext(dOConfigVec_);

    	// create object instance in information model
    	if (!createObjectInstance()) {
    		return false;
    	}

    	return true;
    }

    bool
	PiXtendBaseServer::handleShutdown(void)
    {
    	// shutdown pixtend interface
    	if (!handleShutdown()) {
    		return false;
    	}

    	return true;
    }

    bool PiXtendBaseServer::createNodeContext(
    	const DOConfig::Vec& dOconfigVec
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


}
