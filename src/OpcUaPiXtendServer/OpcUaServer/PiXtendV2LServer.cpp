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
    : PiXtendBaseServer("PiXtendV2L", "http://ASNeG.de/PiXtend/", 1003)
    {
    }

    PiXtendV2LServer::~PiXtendV2LServer(void)
    {
    }

    bool
	PiXtendV2LServer::handleStartup(void)
    {
    	nodePinConfigVec_ = {

    		// digital outputs
    		{"DO_DO0_Variable", "DO0"},
			{"DO_DO1_Variable", "DO1"},
			{"DO_DO2_Variable", "DO2"},
			{"DO_DO3_Variable", "DO3"},
		    {"DO_DO4_Variable", "DO4"},
			{"DO_DO5_Variable", "DO5"},
			{"DO_DO6_Variable", "DO6"},
			{"DO_DO7_Variable", "DO7"},
			{"DO_DO8_Variable", "DO8"},
			{"DO_DO9_Variable", "DO9"},
			{"DO_DO10_Variable", "DO10"},
			{"DO_DO11_Variable", "DO11"},
			{"RELAY_RELAY0_Variable", "RELAY0"},
			{"RELAY_RELAY1_Variable", "RELAY1"},
			{"RELAY_RELAY2_Variable", "RELAY2"},
			{"RELAY_RELAY3_Variable", "RELAY3"},

			// digital inputs
	        {"DI_DI0_Variable", "DI0"},
	        {"DI_DI1_Variable", "DI1"},
	        {"DI_DI2_Variable", "DI2"},
	        {"DI_DI3_Variable", "DI3"},
		    {"DI_DI4_Variable", "DI4"},
		    {"DI_DI5_Variable", "DI5"},
		    {"DI_DI6_Variable", "DI6"},
		    {"DI_DI7_Variable", "DI7"},
	        {"DI_DI8_Variable", "DI8"},
		    {"DI_DI9_Variable", "DI9"},
		    {"DI_DI10_Variable", "DI10"},
			{"DI_DI11_Variable", "DI11"},
			{"DI_DI12_Variable", "DI12"},
			{"DI_DI13_Variable", "DI13"},
			{"DI_DI14_Variable", "DI14"},
			{"DI_DI15_Variable", "DI15"},

			// analog outputs
            {"AO_AO0_Variable", "AO0"},
            {"AO_AO1_Variable", "AO1"},

			// analog inputs
	        {"AI_AI0_Variable", "AI0"},
	        {"AI_AI1_Variable", "AI1"},
	        {"AI_AI2_Variable", "AI2"},
			{"AI_AI3_Variable", "AI3"},
			{"AI_AI4_Variable", "AI4"},
			{"AI_AI5_Variable", "AI5"}
    	};

    	return true;
    }

    bool
	PiXtendV2LServer::handleShutdown(void)
    {
    	return true;
    }

}
