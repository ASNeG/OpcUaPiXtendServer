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

			// digital inputs
	        {"DI_DI0_Variable", "DI0"},
	        {"DI_DI1_Variable", "DI1"},
	        {"DI_DI2_Variable", "DI2"},
	        {"DI_DI3_Variable", "DI3"},
		    {"DI_DI4_Variable", "DI4"},
		    {"DI_DI5_Variable", "DI5"},
		    {"DI_DI6_Variable", "DI6"},
		    {"DI_DI7_Variable", "DI7"},
    	};

    	return true;
    }

    bool
	PiXtendEIODOServer::handleShutdown(void)
    {
    	return true;
    }
}
