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

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2SServer.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2SServer::PiXtendV2SServer(void)
    : PiXtendBaseServer("PiXtendV2S", 1002)
    {
    }

    PiXtendV2SServer::~PiXtendV2SServer(void)
    {
    }

    bool
	PiXtendV2SServer::handleStartup(void)
    {
    	// get pixtend v2s access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendV2S();

       	// startup pixtend interface
        pixtend_->startup();

        // set digital output configuration
        dOConfigVec_ = {
            {"DO_DO0_Variable", V2S_DO_RF(do0), V2S_DO_WF(do0)},
            {"DO_DO1_Variable", V2S_DO_RF(do1), V2S_DO_WF(do1)},
            {"DO_DO2_Variable", V2S_DO_RF(do2), V2S_DO_WF(do2)},
            {"DO_DO3_Variable", V2S_DO_RF(do3), V2S_DO_WF(do3)},
            {"RELAY_RELAY0_Variable", V2S_DO_RF(relay0), V2S_DO_WF(relay0)},
            {"RELAY_RELAY1_Variable", V2S_DO_RF(relay1), V2S_DO_WF(relay1)},
            {"RELAY_RELAY2_Variable", V2S_DO_RF(relay2), V2S_DO_WF(relay2)},
            {"RELAY_RELAY3_Variable", V2S_DO_RF(relay3), V2S_DO_WF(relay3)}
        };

        // set digital input configuration
        dIConfigVec_ = {
            {"DI_DI0_Variable", V2S_DI_RF(di0)},
            {"DI_DI1_Variable", V2S_DI_RF(di1)},
            {"DI_DI2_Variable", V2S_DI_RF(di2)},
            {"DI_DI3_Variable", V2S_DI_RF(di3)},
	        {"DI_DI4_Variable", V2S_DI_RF(di4)},
	        {"DI_DI5_Variable", V2S_DI_RF(di5)},
	        {"DI_DI6_Variable", V2S_DI_RF(di6)},
	        {"DI_DI7_Variable", V2S_DI_RF(di7)}
        };

        // set analog output configuration
        aOConfigVec_ = {
            {"AO_AO0_Variable", V2S_AO_RF(ao0), V2S_AO_WF(ao0)},
            {"AO_AO1_Variable", V2S_AO_RF(ao1), V2S_AO_WF(ao1)}
        };

        // set analog input configuration
        aIConfigVec_ = {
            {"AI_AI0_Variable", V2S_AI_RF(ai0)},
            {"AI_AI1_Variable", V2S_AI_RF(ai1)}
        };

    	return true;
    }

    bool
	PiXtendV2SServer::handleShutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();
    	pixtend_.reset();

    	return true;
    }
}
