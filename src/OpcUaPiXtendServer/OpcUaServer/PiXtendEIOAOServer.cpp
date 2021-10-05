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

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIOAOServer.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIOAOServer::PiXtendEIOAOServer(uint32_t moduleAddress)
    : PiXtendBaseServer("PiXtendEIOAO", 1005)
    , moduleAddress_(moduleAddress)
    {
    }

    PiXtendEIOAOServer::~PiXtendEIOAOServer(void)
    {
    }

    bool
	PiXtendEIOAOServer::handleStartup(void)
    {
    	nodePinConfigVec_ = {

			// analog outputs
            {"AO_AO0_Variable", "AO0"},
            {"AO_AO1_Variable", "AO1"},
			{"AO_AO2_Variable", "AO2"},
			{"AO_AO3_Variable", "AO3"},
			{"AO_AO4_Variable", "AO4"},
			{"AO_AO5_Variable", "AO5"},

			// analog inputs
	        {"AI_AI0_Variable", "AI0"},
	        {"AI_AI1_Variable", "AI1"},
	        {"AI_AI2_Variable", "AI2"},
			{"AI_AI3_Variable", "AI3"},
			{"AI_AI4_Variable", "AI4"},
			{"AI_AI5_Variable", "AI5"},
			{"AI_AI6_Variable", "AI6"},
			{"AI_AI7_Variable", "AI7"},
    	};

    	return true;
    }

    bool
	PiXtendEIOAOServer::handleShutdown(void)
    {
    }

}
