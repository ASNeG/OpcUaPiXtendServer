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

#include <boost/make_shared.hpp>
#include "OpcUaPiXtendServer/ModuleEIO/PiXtendEIODOInst.h"
#include "OpcUaPiXtendServer/ModuleEIO/PiXtendEIOAOInst.h"
#include "OpcUaPiXtendServer/Factory/PiXtendModulesFactory.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/ModuleDummy/PiXtendEIOAODummy.h"
#include "OpcUaPiXtendServer/ModuleDummy/PiXtendEIODODummy.h"

#ifdef OPTION_OPCUAPIXTENDSERVER_SPI_ON
    #include "OpcUaPiXtendServer/ModuleSpi/PiXtendV2SInst.h"
    #include "OpcUaPiXtendServer/ModuleSpi/PiXtendV2LInst.h"
#elif defined OPTION_OPCUAPIXTENDSERVER_SPI_DUMMY
    #include "OpcUaPiXtendServer/ModuleDummy/PiXtendV2SDummy.h"
    #include "OpcUaPiXtendServer/ModuleDummy/PiXtendV2LDummy.h"
#endif

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendModulesFactory::PiXtendModulesFactory(void)
    {
    }

    PiXtendModulesFactory::~PiXtendModulesFactory(void)
    {
    }

    PiXtendV2S::SPtr
    PiXtendModulesFactory::createPiXtendV2S(const std::string& instanceName)
    {
#ifdef OPTION_OPCUAPIXTENDSERVER_SPI_ON
        return boost::make_shared<PiXtendV2SInst>(instanceName);
#elif defined OPTION_OPCUAPIXTENDSERVER_SPI_DUMMY
        return boost::make_shared<PiXtendV2SDummy>(instanceName);
#else
        Log(Error, "PiXtendModulesFactory cannot create module - module is undefined!")
                .parameter("instanceName", instanceName);
        return nullptr;
#endif
    }

    PiXtendV2L::SPtr
    PiXtendModulesFactory::createPiXtendV2L(const std::string& instanceName)
    {
#ifdef OPTION_OPCUAPIXTENDSERVER_SPI_ON
        return boost::make_shared<PiXtendV2LInst>(instanceName);
#elif defined OPTION_OPCUAPIXTENDSERVER_SPI_DUMMY
        return boost::make_shared<PiXtendV2LDummy>(instanceName);
#else
        Log(Error, "PiXtendModulesFactory cannot create module - module is undefined!")
                .parameter("instanceName", instanceName);
        return nullptr;
#endif
    }

    PiXtendEIOAO::SPtr
    PiXtendModulesFactory::createPiXtendEIOAO(
    	const std::string& instanceName,
		DeviceAccess::SPtr& deviceAccess
	)
    {
    	if (deviceAccess) {
    		if (deviceAccess->deviceAccessType() == DeviceAccessType::USB) {
    			return boost::make_shared<PiXtendEIOAOInst>(instanceName, deviceAccess);
    		}
    		else {
               	Log(Error, "PiXtendModulesFactory cannot create module - module is undefined!")
                	.parameter("instanceName", instanceName);
                return nullptr;
    		}
    	}
    	else {
    		return boost::make_shared<PiXtendEIOAODummy>(instanceName);
    	}

    	return nullptr;
    }

    PiXtendEIODO::SPtr
    PiXtendModulesFactory::createPiXtendEIODO(
    	const std::string& instanceName,
		DeviceAccess::SPtr& deviceAccess
	)
    {
    	if (deviceAccess) {
    		if (deviceAccess->deviceAccessType() == DeviceAccessType::USB) {
    			return boost::make_shared<PiXtendEIODOInst>(instanceName, deviceAccess);
    		}
    		else {
               	Log(Error, "PiXtendModulesFactory cannot create module - module is undefined!")
                	.parameter("instanceName", instanceName);
                return nullptr;
    		}
    	}
    	else {
    		return boost::make_shared<PiXtendEIODODummy>(instanceName);
    	}

    	return nullptr;
    }

}
