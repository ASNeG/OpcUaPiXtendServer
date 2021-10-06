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
#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"


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

        // startup pixtend modules
        if (!startupPiXtend(controllerCfg)) {
        	Log(Error, "startup pixtend error");
        	return false;
        }

        // add configured opc ua server objects
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
	PiXtendServer::startupPiXtend(PiXtendServerControllerCfg& cfg)
	{
	    for (auto module: cfg.configModules()) {
	    	switch (module.moduleType()) {
	    		case ServerModule::V2S:
	    		{
	    			piXtendV2S_ = PiXtendModulesFactory::createPiXtendV2S(module.moduleName());
	    			piXtendV2S_->contextIndex(contextIndex_);
	    			if (!piXtendV2S_->startup()) {
	    				Log(Error, "startup pixtend V2S error")
	    					.parameter("ModuleName", module.moduleName());
	    				return false;
	    			}
	    			break;
	    		}
	    		case ServerModule::V2L:
	    		{
	    			piXtendV2L_ = PiXtendModulesFactory::createPiXtendV2L(module.moduleName());
	    			piXtendV2L_->contextIndex(contextIndex_);
	    			if (!piXtendV2L_->startup()) {
	    				Log(Error, "startup pixtend V2l error")
							.parameter("ModuleName", module.moduleName());
	    				return false;
	    			}
	    			break;
	    		}
	    		case ServerModule::DO:
	    		{
	    			auto piXtendEIODO = PiXtendModulesFactory::createPiXtendEIODO(module.moduleName());
	    			piXtendEIODO->contextIndex(contextIndex_);
	    			if (!piXtendEIODO->startup(module.moduleAddress())) {
	    				Log(Error, "startup pixtend EIODO error")
						    .parameter("ModuleName", module.moduleName());
	    				return false;
	    			}
	    			piXtendEIODOMap_.insert(std::make_pair(module.moduleAddress(), piXtendEIODO));
					break;
	    		}
	    		case ServerModule::AO:
	    		{
	    			auto piXtendEIOAO = PiXtendModulesFactory::createPiXtendEIOAO(module.moduleName());
	    			piXtendEIOAO->contextIndex(contextIndex_);
	    			if (!piXtendEIOAO->startup(module.moduleAddress())) {
	    				Log(Error, "startup pixtend EIOAO error")
						    .parameter("ModuleName", module.moduleName());
	    				return false;
	    			}
	    			piXtendEIOAOMap_.insert(std::make_pair(module.moduleAddress(), piXtendEIOAO));
					break;
	    		}
	    	    default:
	    	    {
	    		    Log(Error, "found undefined type in control configuration!")
	    		        .parameter("Name", module.moduleName());
	    		    return false;
	    	    }
	    	}
	    }

		return true;
	}

	bool
	PiXtendServer::shutdown(void)
	{
		Log(Debug, "PiXtendServer::shutdown");

		// shutdown V2S server
		if (piXtendV2SServer_.get() != nullptr) {
			piXtendV2SServer_->shutdown();
			piXtendV2SServer_.reset();
		}

		// shutdown V2L server
		if (piXtendV2LServer_.get() != nullptr) {
			piXtendV2LServer_->shutdown();
			piXtendV2LServer_.reset();
		}

		// shutdown EIOAO server
		for (auto element : piXtendEIOAOServerMap_) {
			auto eIOAO = element.second;
			eIOAO->shutdown();
			eIOAO.reset();
		}
		piXtendEIOAOServerMap_.clear();

		// shutdown EIODO server
		for (auto element : piXtendEIODOServerMap_) {
			auto eIODO = element.second;
			eIODO->shutdown();
			eIODO.reset();
		}
		piXtendEIODOServerMap_.clear();

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
        	ioThread_,
			strand_,
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
			contextIndex_
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
        	ioThread_,
        	strand_,
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
			contextIndex_
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

        piXtendEIOAOServerMap_[address] = boost::make_shared<PiXtendEIOAOServer>(address);
        return piXtendEIOAOServerMap_[address]->startup(
        	ioThread_,
        	strand_,
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
			contextIndex_
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

        piXtendEIODOServerMap_[address] = boost::make_shared<PiXtendEIODOServer>(address);
        return piXtendEIODOServerMap_[address]->startup(
        	ioThread_,
        	strand_,
            applicationServiceIf_,
            name,
            namespaceName_,
            namespaceIndex_,
            piXtendRootNodeId_,
			contextIndex_
        );
    }
}
