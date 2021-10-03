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

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIODOServer.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIODOServer::PiXtendEIODOServer(uint32_t moduleAddress)
    : PiXtendBaseServer("PiXtendEIODO", 1004)
    , moduleAddress_(moduleAddress)
    {
    }

    PiXtendEIODOServer::~PiXtendEIODOServer(void)
    {
    }

    bool
	PiXtendEIODOServer::handleStartup(void)
    {
    	// get pixtend v2s access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendEIODO();

       	// startup pixtend interface
        pixtend_->startup(moduleAddress_);

        // set digital output configuration
        dOConfigVec_ = {
            {"DO_DO0_Variable", EIODO_DO_RF(do0), EIODO_DO_WF(do0)},
            {"DO_DO1_Variable", EIODO_DO_RF(do1), EIODO_DO_WF(do1)},
            {"DO_DO2_Variable", EIODO_DO_RF(do2), EIODO_DO_WF(do2)},
            {"DO_DO3_Variable", EIODO_DO_RF(do3), EIODO_DO_WF(do3)},
			{"DO_DO4_Variable", EIODO_DO_RF(do4), EIODO_DO_WF(do4)},
			{"DO_DO5_Variable", EIODO_DO_RF(do5), EIODO_DO_WF(do5)},
			{"DO_DO6_Variable", EIODO_DO_RF(do6), EIODO_DO_WF(do6)},
			{"DO_DO7_Variable", EIODO_DO_RF(do7), EIODO_DO_WF(do7)}
        };

        // set digital input configuration
        dIConfigVec_ = {
            {"DI_DI0_Variable", EIODO_DI_RF(di0)},
            {"DI_DI1_Variable", EIODO_DI_RF(di1)},
            {"DI_DI2_Variable", EIODO_DI_RF(di2)},
            {"DI_DI3_Variable", EIODO_DI_RF(di3)},
	        {"DI_DI4_Variable", EIODO_DI_RF(di4)},
	        {"DI_DI5_Variable", EIODO_DI_RF(di5)},
	        {"DI_DI6_Variable", EIODO_DI_RF(di6)},
	        {"DI_DI7_Variable", EIODO_DI_RF(di7)}
        };

    	return true;
    }

    bool
	PiXtendEIODOServer::handleShutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();
    	pixtend_.reset();

    	return true;
    }
}
