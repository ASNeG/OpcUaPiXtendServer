/*
   Copyright 2021-2022 Kai Huebl (kai@huebl-sgh.de)

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
#include "OpcUaPiXtendServer/Factory/PiXtendModulesFactory.h"
#include "OpcUaPiXtendServer/ModuleEIO/USBAccess.h"


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
        OpcUaStackCore::Config& config,
        ContextIndex::SPtr contextIndexSPtr
	)
	{
		Log(Debug, "PiXtendServer::startup");

		ioThread_ = ioThread;
		strand_ = strand;
		applicationServiceIf_ = applicationServiceIf;
		applicationInfo_ = applicationInfo;
        contextIndex_ = contextIndexSPtr;

		// parse pixtend configuration
        if (!cfg_.parse(&config))
        {
            Log(Error, "parse controller configuration error")
                .parameter("File", config.configFileName());
            return false;
        }

        // create pixtend root object in opc ua information model
        Log(Debug,  "create pixtend root object");
        if (!createPiXtendRootObject())
        {
            Log(Error, "create pixtend folder error");
            return false;
        }

        // startup pixtend modules
        Log(Debug, "startup pixtend modules");
        if (!startupPiXtend()) {
        	Log(Error, "startup pixtend error");
        	return false;
        }

        // add configured opc ua server objects
        Log(Debug, "startup pixtend server");
        if (!startupServer()) {
        	Log(Error, "startup server error");
        	return false;
        }

        // startup pixtend loop
        Log(Debug, "startup pixtend loop");
        if (!startupPiXtendLoop()) {
        	Log(Error, "startup pixtend loop error");
        	return false;
        }

		return true;
	}

	bool
	PiXtendServer::shutdown(void)
	{
		Log(Debug, "PiXtendServer::shutdown");

		// shutdown pixtend loop
		Log(Debug, "shutdown pixtend loop");
		shutdownPiXtendLoop();

		// shutdown server
		Log(Debug, "shutdown pixtend server");
		shutdownServer();

		// shutdown pixtend
		Log(Debug, "shutdown pixtend modules");
		shutdownPiXtend();

		return true;
	}

	bool
	PiXtendServer::startupPiXtend(void)
	{
	    for (auto module: cfg_.configModules()) {
	    	switch (module.moduleType()) {
	    		case ServerModule::V2S:
	    		{
	    			if (!startupPiXtendV2S(module.moduleName())) {
	    				Log(Error, "cannot create v2s pixtend module");
	    				return false;
	    			}
	    			break;
	    		}
	    		case ServerModule::V2L:
	    		{
	                if (!startupPiXtendV2L(module.moduleName())) {
	                    Log(Error, "cannot create v2l pixtend module");
	                    return false;
	                }
	                break;
	    		}
	    		case ServerModule::DO:
	    		{
	    			if (!startupPiXtendEIODO(module)) {
	    				Log(Error, "cannot create do pixtend module");
	    				return false;
	    			}
	    			break;
	    		}
	    		case ServerModule::AO:
	    		{
	                if (!startupPiXtendEIOAO(module))
	                {
	                    Log(Error, "cannot create ao pixtend module");
	                    return false;
	                }
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
	PiXtendServer::shutdownPiXtend(void)
	{
		// shutdown pixtend v2s
		if (piXtendV2S_) {
			piXtendV2S_->shutdown();
			piXtendV2S_.reset();
		}

		// shutdown pixtend v2l
		if (piXtendV2L_) {
			piXtendV2L_->shutdown();
			piXtendV2L_.reset();
		}

		// shutdown pixtend EIOAO
		for (auto pixtendEIOAO : piXtendEIOAOMap_) {
			pixtendEIOAO.second->shutdown();
		}
		piXtendEIOAOMap_.clear();

		// shutdown pixtend EIODO
		for (auto pixtendEIODO : piXtendEIODOMap_) {
			pixtendEIODO.second->shutdown();
		}
		piXtendEIODOMap_.clear();

		// shutdown all device access
		deviceAccessManager_.deleteDeviceAccess();

		return true;
	}

    bool
    PiXtendServer::startupPiXtendV2S(const std::string& name)
    {
        piXtendV2S_ = PiXtendModulesFactory::createPiXtendV2S(name);
        if (piXtendV2S_ == nullptr) {
            Log(Error, "cannot create module v2s")
                .parameter("ModuleName", name);
            return false;
        }

        piXtendV2S_->contextIndex(contextIndex_);
        if (!piXtendV2S_->startup()) {
            Log(Error, "startup pixtend V2S error")
                .parameter("ModuleName", name);
            return false;
        }
        return true;
    }

    bool
    PiXtendServer::startupPiXtendV2L(const std::string& name)
    {
        piXtendV2L_ = PiXtendModulesFactory::createPiXtendV2L(name);
        if (piXtendV2L_ == nullptr) {
            Log(Error, "cannot create module v2l")
                .parameter("ModuleName", name);
            return false;
        }

        piXtendV2L_->contextIndex(contextIndex_);
        if (!piXtendV2L_->startup()) {
            Log(Error, "startup pixtend V2l error")
                .parameter("ModuleName", name);
            return false;
        }
        return true;
    }

    bool
	PiXtendServer::startupPiXtendEIODO(PiXtendServerCfgModule& moduleCfg)
    {
    	DeviceAccess::SPtr deviceAccess;

    	// usb communication is used
    	if (moduleCfg.usbDeviceCfg()) {

    		// find assigned usb configuration element
    		auto it = cfg_.usbCfgMap().find(moduleCfg.usbDeviceCfg()->deviceName());
    		if (it == cfg_.usbCfgMap().end()) {
    			Log(Error, "USB device name not found in configuration")
    				.parameter("USBDevice", moduleCfg.usbDeviceCfg()->deviceName());
    			return false;
    		}

    		// create usb device access
    		auto usbCfg = it->second;
			deviceAccess = deviceAccessManager_.createDeviceAccess(
				usbCfg->device(),
				usbCfg->baud(),
				usbCfg->parity(),
				usbCfg->dataBit(),
				usbCfg->stopBit()
			);
			if (!deviceAccess) {
				Log(Error, "create usb device access error")
					.parameter("USBDevice", moduleCfg.usbDeviceCfg()->deviceName());
				return false;
			}
    	}

		auto piXtendEIODO = PiXtendModulesFactory::createPiXtendEIODO(moduleCfg.moduleName(), deviceAccess);

        if (piXtendEIODO == nullptr) {
            Log(Error, "cannot create module eIO DO")
                .parameter("ModuleName", moduleCfg.moduleName());
            return false;
        }

		piXtendEIODO->contextIndex(contextIndex_);
		if (!piXtendEIODO->startup(moduleCfg.moduleAddress())) {
			Log(Error, "startup pixtend EIODO error")
                .parameter("ModuleName", moduleCfg.moduleName())
                .parameter("ModuleAddress", moduleCfg.moduleAddress());
			return false;
		}
		piXtendEIODOMap_.insert(std::make_pair(moduleCfg.moduleAddress(), piXtendEIODO));
		return true;
    }

    bool
	PiXtendServer::startupPiXtendEIOAO(PiXtendServerCfgModule& moduleCfg)
    {
    	DeviceAccess::SPtr deviceAccess;

    	// usb communication is used
    	if (moduleCfg.usbDeviceCfg()) {

    		// find assigned usb configuration element
    		auto it = cfg_.usbCfgMap().find(moduleCfg.usbDeviceCfg()->deviceName());
    		if (it == cfg_.usbCfgMap().end()) {
    			Log(Error, "USB device not found in configuration")
    				.parameter("USBDevice", moduleCfg.usbDeviceCfg()->deviceName());
    			return false;
    		}

    		// create usb device access
    		auto usbCfg = it->second;
			deviceAccess = deviceAccessManager_.createDeviceAccess(
				usbCfg->device(),
				usbCfg->baud(),
				usbCfg->parity(),
				usbCfg->dataBit(),
				usbCfg->stopBit()
			);
			if (!deviceAccess) {
				Log(Error, "create usb device access error")
					.parameter("USBDevice", moduleCfg.usbDeviceCfg()->deviceName());
				return false;
			}
    	}

		auto piXtendEIOAO = PiXtendModulesFactory::createPiXtendEIOAO(moduleCfg.moduleName(), deviceAccess);
        if (piXtendEIOAO == nullptr) {
            Log(Error, "cannot create module eIO AO")
                .parameter("ModuleName", moduleCfg.moduleName());
            return false;
        }

		piXtendEIOAO->contextIndex(contextIndex_);
		if (!piXtendEIOAO->startup(moduleCfg.moduleAddress())) {
			Log(Error, "startup pixtend EIOAO error")
                .parameter("ModuleName", moduleCfg.moduleName())
                .parameter("ModuleAddress", moduleCfg.moduleAddress());
			return false;
		}
		piXtendEIOAOMap_.insert(std::make_pair(moduleCfg.moduleAddress(), piXtendEIOAO));
		return true;
    }


	bool
	PiXtendServer::startupServer(void)
	{
	    for (auto module: cfg_.configModules()) {

	    	// create unit converter context map
	    	UnitConverterContext::Map unitConverterContextMap;
	    	for (auto unitConv : module.unitConversionConfigMap()) {
	    		unitConverterContextMap.insert(std::make_pair(
	    			unitConv.first,
					boost::make_shared<UnitConverterContext>(
						unitConv.second->a(),
						unitConv.second->b(),
						unitConv.second->c(),
						unitConv.second->d()
					)
				));
	    	}

	    	switch (module.moduleType()) {
	    		case ServerModule::V2S:
	    		{
                    if (!startupServerV2S(module.moduleName(), unitConverterContextMap)) {
	    				Log(Error, "cannot create v2s server module");
	    				return false;
	    			}
	    			break;
	    		}
	    		case ServerModule::V2L:
	            {
                    if (!startupServerV2L(module.moduleName(), unitConverterContextMap)) {
	                    Log(Error, "cannot create v2l server module");
	                    return false;
	                }
	                break;
	            }
	    		case ServerModule::AO:
	            {
                    if (!startupServerEIOAO(module.moduleName(),
                    						unitConverterContextMap,
                                            module.moduleAddress())) {
                        Log(Error, "cannot create ao server module");
                        return false;
                    }
                    break;
                }
                case ServerModule::DO:
                {
                    if (!startupServerEIODO(module.moduleName(),
                    						unitConverterContextMap,
                                            module.moduleAddress())) {
                        Log(Error, "cannot create do server module");
                        return false;
                    }
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
    PiXtendServer::shutdownServer(void)
    {
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
    PiXtendServer::startupServerV2S(
    	const std::string& name,
    	const UnitConverterContext::Map& unitConverterContextMap
	)
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
            piXtendRootNodeId_,
            contextIndex_,
			unitConverterContextMap
        );
    }

    bool
    PiXtendServer::startupServerV2L(
    	const std::string& name,
    	const UnitConverterContext::Map& unitConverterContextMap
	)
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
            piXtendRootNodeId_,
            contextIndex_,
			unitConverterContextMap
        );
    }

    bool
    PiXtendServer::startupServerEIOAO(
    	const std::string& name,
    	const UnitConverterContext::Map& unitConverterContextMap,
        uint32_t address)
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
            piXtendRootNodeId_,
            contextIndex_,
			unitConverterContextMap
        );
    }

    bool
    PiXtendServer::startupServerEIODO(
    	const std::string& name,
    	const UnitConverterContext::Map& unitConverterContextMap,
        uint32_t address
	)
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
            piXtendRootNodeId_,
            contextIndex_,
			unitConverterContextMap
        );
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
    PiXtendServer::startupPiXtendLoop(void)
    {
        pixtendLoopstrand_ = ioThread_->createStrand();

        pixtendTimerElement_ = boost::make_shared<SlotTimerElement>();
        pixtendTimerElement_->timeoutCallback(
            pixtendLoopstrand_,
            [this](void) {
                piXtendLoop();
            }
        );

        Log(Debug, "start pixtend timer");
        pixtendTimerElement_->expireTime(
            boost::posix_time::microsec_clock::local_time() + boost::posix_time::millisec(pixtendTimerInterval_)
        );
        ioThread_->slotTimer()->start(pixtendTimerElement_);
        return true;
    }

    bool
    PiXtendServer::shutdownPiXtendLoop(void)
    {
        if (!pixtendLoopstrand_->running_in_this_thread()) {
            // the function was not called by the strand

            std::promise<void> promise;
            std::future<void> future = promise.get_future();

            pixtendLoopstrand_->dispatch(
                [this, &promise]() {
                    shutdownPiXtendLoop();
                    promise.set_value();
                }
            );

            future.wait();
            return true;
        }

        // stop pixtend timer loop
        if (pixtendTimerElement_.get() != nullptr) {
            ioThread_->slotTimer()->stop(pixtendTimerElement_);
            pixtendTimerElement_.reset();
        }

        return true;
    }

    void
    PiXtendServer::piXtendLoop(void)
    {
        Log(Debug, "run pixtend loop");

        // call v2s loop
        if (piXtendV2S_) {
            piXtendV2S_->loop();
        }

        // call v2l loop
        if (piXtendV2L_) {
            piXtendV2L_->loop();
        }

        // call EIOAO loops
        for (auto eIOAO : piXtendEIOAOMap_) {
            eIOAO.second->loop();
        }

        // call EIODO loops
        for (auto eIODO : piXtendEIODOMap_) {
            eIODO.second->loop();
        }

        // restart timer
        pixtendTimerElement_->expireTime(
            boost::posix_time::microsec_clock::local_time() + boost::posix_time::millisec(pixtendTimerInterval_)
        );
        ioThread_->slotTimer()->start(pixtendTimerElement_);
    }

}
