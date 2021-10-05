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
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2LServer.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    PiXtendV2LServer::PiXtendV2LServer(void)
    : PiXtendBaseServer("PiXtendV2L", 1003)
    {
    }

    PiXtendV2LServer::~PiXtendV2LServer(void)
    {
    }

    bool
	PiXtendV2LServer::handleStartup(void)
    {
    	// get pixtend v2l access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendV2L(instanceName_);

       	// startup pixtend interface
        pixtend_->startup();

        // set digital output configuration
        dOConfigVec_ = {
            {"DO_DO0_Variable", V2L_DO_RF(do0), V2L_DO_WF(do0)},
            {"DO_DO1_Variable", V2L_DO_RF(do1), V2L_DO_WF(do1)},
            {"DO_DO2_Variable", V2L_DO_RF(do2), V2L_DO_WF(do2)},
            {"DO_DO3_Variable", V2L_DO_RF(do3), V2L_DO_WF(do3)},
			{"DO_DO4_Variable", V2L_DO_RF(do4), V2L_DO_WF(do4)},
			{"DO_DO5_Variable", V2L_DO_RF(do5), V2L_DO_WF(do5)},
			{"DO_DO6_Variable", V2L_DO_RF(do6), V2L_DO_WF(do6)},
			{"DO_DO7_Variable", V2L_DO_RF(do7), V2L_DO_WF(do7)},
			{"DO_DO8_Variable", V2L_DO_RF(do8), V2L_DO_WF(do8)},
			{"DO_DO9_Variable", V2L_DO_RF(do9), V2L_DO_WF(do9)},
			{"DO_DO10_Variable", V2L_DO_RF(do10), V2L_DO_WF(do10)},
			{"DO_DO11_Variable", V2L_DO_RF(do11), V2L_DO_WF(do11)},
            {"RELAY_RELAY0_Variable", V2L_DO_RF(relay0), V2L_DO_WF(relay0)},
            {"RELAY_RELAY1_Variable", V2L_DO_RF(relay1), V2L_DO_WF(relay1)},
            {"RELAY_RELAY2_Variable", V2L_DO_RF(relay2), V2L_DO_WF(relay2)},
            {"RELAY_RELAY3_Variable", V2L_DO_RF(relay3), V2L_DO_WF(relay3)}
        };

        // set digital input configuration
        dIConfigVec_ = {
            {"DI_DI0_Variable", V2L_DI_RF(di0)},
            {"DI_DI1_Variable", V2L_DI_RF(di1)},
            {"DI_DI2_Variable", V2L_DI_RF(di2)},
            {"DI_DI3_Variable", V2L_DI_RF(di3)},
	        {"DI_DI4_Variable", V2L_DI_RF(di4)},
	        {"DI_DI5_Variable", V2L_DI_RF(di5)},
	        {"DI_DI6_Variable", V2L_DI_RF(di6)},
	        {"DI_DI7_Variable", V2L_DI_RF(di7)},
            {"DI_DI8_Variable", V2L_DI_RF(di8)},
			{"DI_DI9_Variable", V2L_DI_RF(di9)},
			{"DI_DI10_Variable", V2L_DI_RF(di10)},
			{"DI_DI11_Variable", V2L_DI_RF(di11)},
			{"DI_DI12_Variable", V2L_DI_RF(di12)},
			{"DI_DI13_Variable", V2L_DI_RF(di13)},
			{"DI_DI14_Variable", V2L_DI_RF(di14)},
			{"DI_DI15_Variable", V2L_DI_RF(di15)}
        };

        // set analog output configuration
        aOConfigVec_ = {
            {"AO_AO0_Variable", V2L_AO_RF(ao0), V2L_AO_WF(ao0)},
            {"AO_AO1_Variable", V2L_AO_RF(ao1), V2L_AO_WF(ao1)}
        };

        // set analog input configuration
        aIConfigVec_ = {
            {"AI_AI0_Variable", V2L_AI_RF(ai0)},
            {"AI_AI1_Variable", V2L_AI_RF(ai1)},
            {"AI_AI2_Variable", V2L_AI_RF(ai2)},
			{"AI_AI3_Variable", V2L_AI_RF(ai3)},
			{"AI_AI4_Variable", V2L_AI_RF(ai4)},
			{"AI_AI5_Variable", V2L_AI_RF(ai5)}
        };

    	return true;
    }

    bool
	PiXtendV2LServer::handleShutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();
    	pixtend_.reset();

    	return true;
    }

}
