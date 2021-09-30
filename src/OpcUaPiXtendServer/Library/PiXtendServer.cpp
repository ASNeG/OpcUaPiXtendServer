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
 */

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackServer/ServiceSetApplication/GetNamespaceInfo.h"
#include "OpcUaStackServer/ServiceSetApplication/CreateNodeInstance.h"
#include "OpcUaPiXtendServer/Library/PiXtendServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2SServer.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{



	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// class PiXtendServer
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	PiXtendServer::PiXtendServer(void)
	{
	}

	PiXtendServer::~PiXtendServer(void)
	{
	}

	bool
	PiXtendServer::startup(
		IOThread::SPtr& ioThread,
		boost::shared_ptr<boost::asio::io_service::strand> strand,
		ApplicationServiceIf* applicationServiceIf,
		ApplicationInfo* applicationInfo,
		OpcUaStackCore::Config& config
	)
	{
		Log(Debug, "PiXtendServer::startup");

		ioThread_ = ioThread;
		strand_ = strand;
		applicationServiceIf_ = applicationServiceIf;
		applicationInfo_ = applicationInfo;

		// parse pixtend configuration
		// FIXME: TBD

		// find namespace
		if (!findNamespace()) {
			Log(Error, "find namespace error");
			return false;
		}

		// create pixtend root object in opc ua information model
		if (!createPiXtendRootObject()) {
			Log(Error, "create pixtend folder error");
			return false;
		}

		// FIXME: add configured objects
		// FIXME: The following lines are test code
		PiXtendV2SServer::SPtr v2s = boost::make_shared<PiXtendV2SServer>();
		v2s->startup(
			applicationServiceIf_,
			"PiXtendV2S",
			namespaceName_,
			namespaceIndex_,
			piXtendRootNodeId_
		);

		return true;
	}

	bool
	PiXtendServer::shutdown(void)
	{
		Log(Debug, "PiXtendServer::shutdown");

		return true;
	}

	bool
	PiXtendServer::findNamespace(void)
	{
		// create and get namespace list
		GetNamespaceInfo getNamespaceInfo;
		getNamespaceInfo.newNamespaceUri(namespaceName_);
		if (!getNamespaceInfo.query(applicationServiceIf_)) {
			Log(Error, "create namespace error")
				.parameter("NamespaceName", namespaceName_);
			return false;
		}

		namespaceIndex_ = getNamespaceInfo.getNamespaceIndex(namespaceName_);
		if (namespaceIndex_ == -1) {
			Log(Error, "get namesapce index error")
				.parameter("NamespaceName", namespaceName_);
			return false;
		}

		return true;
	}

	bool
	PiXtendServer::createPiXtendRootObject(void)
	{
		// create pixtend root object
		CreateNodeInstance createNodeInstance(
			"PiXtend1",										// name
			NodeClass::EnumObject,							// node class
			OpcUaNodeId(OpcUaId_ObjectsFolder),				// parent node id (Objects)
			piXtendRootNodeId_,								// node id
			OpcUaLocalizedText("en", "PiXtend"),			// dispplay name
			OpcUaQualifiedName("PiXtend", 1),				// browse name
			OpcUaNodeId(OpcUaId_HasComponent),				// reference type id
			OpcUaNodeId(OpcUaId_BaseObjectType)				// type node id
		);

		if (!createNodeInstance.query(applicationServiceIf_)) {
			return false;
		}

		return true;
	}

}
