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
        // parse controller configuration
        PiXtendServerControllerCfg controllerCfg;
        if (!controllerCfg.parse(&config))
        {
            Log(Error, "parse controller configuration error")
                .parameter("File", config.configFileName());
            return false;
        }

		// find namespace
        if (!findNamespace())
        {
			Log(Error, "find namespace error");
			return false;
		}

		// create pixtend root object in opc ua information model
        if (!createPiXtendRootObject())
        {
			Log(Error, "create pixtend folder error");
			return false;
		}

        // add configured objects
        auto modules = controllerCfg.configModules();
        for (auto module: modules)
        {
            if (module.moduleType() == ServerModule::V2S)
            {
                if (!createSeverModuleV2S(module.moduleName()))
                {
                    Log(Error, "cannot create v2s module");
                    return false;
                }
            }
            else if (module.moduleType() == ServerModule::V2L)
            {
                if (!createServerModuleV2L(module.moduleName()))
                {
                    Log(Error, "cannot create v2l module");
                    return false;
                }
            }
            else if (module.moduleType() == ServerModule::AO)
            {
                if (!createServerModuleEIOAO(module.moduleName(), module.moduleAddress()))
                {
                    Log(Error, "cannot create ao module");
                    return false;
                }
            }
            else if (module.moduleType() == ServerModule::DO)
            {
                if (!createServerModuleEIODO(module.moduleName(), module.moduleAddress()))
                {
                    Log(Error, "cannot create do module");
                    return false;
                }
            }
            else
            {
                Log(Error, "found undefined type in control configuration!")
                        .parameter("Name", module.moduleName());
                return false;
            }
        }

		return true;
	}

	bool
	PiXtendServer::shutdown(void)
	{
		Log(Debug, "PiXtendServer::shutdown");

		// FIXME: TBD

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

        namespaceIndex_ = getNamespaceInfo.getNamespaceIndex(namespaceName_); // FIXME: cast from int32 to uint16!!
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

    bool
    PiXtendServer::createSeverModuleV2S(std::string name)
    {
        if (piXtendV2SServer_ != nullptr)
        {
            Log(Error, "pixtend module v2s already exists!")
                .parameter("Name", name);
            return false;
        }

        piXtendV2SServer_ = boost::make_shared<PiXtendV2SServer>();
        return piXtendV2SServer_->startup(
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_
        );
    }

    bool
    PiXtendServer::createServerModuleV2L(std::string name)
    {
        if (piXtendV2LServer_ != nullptr)
        {
            Log(Error, "pixtend module v2l already exists!")
                .parameter("Name", name);
            return false;
        }

        piXtendV2LServer_ = boost::make_shared<PiXtendV2LServer>();
        return piXtendV2LServer_->startup(
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_
        );
    }

    bool
    PiXtendServer::createServerModuleEIOAO(std::string name, uint32_t address)
    {
        if (piXtendEIOAOServerMap_.find(address) != piXtendEIOAOServerMap_.end())
        {
            Log(Error, "pixtend module eIO AO already exists!")
                .parameter("Name", name)
                .parameter("Address", address);
            return false;
        }

        piXtendEIOAOServerMap_[address] = boost::make_shared<PiXtendEIOAOServer>();
        return piXtendEIOAOServerMap_[address]->startup(
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
            address
        );
    }

    bool
    PiXtendServer::createServerModuleEIODO(std::string name, uint32_t address)
    {
        if (piXtendEIODOServerMap_.find(address) != piXtendEIODOServerMap_.end())
        {
            Log(Error, "pixtend module eIO DO already exists!")
                .parameter("Name", name)
                .parameter("Address", address);
            return false;
        }

        piXtendEIODOServerMap_[address] = boost::make_shared<PiXtendEIODOServer>();
        return piXtendEIODOServerMap_[address]->startup(
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
            address
        );
    }
}
