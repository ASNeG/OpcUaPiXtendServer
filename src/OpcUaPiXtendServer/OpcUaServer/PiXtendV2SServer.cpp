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

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;



namespace OpcUaPiXtendServer
{

    PiXtendV2SServer::PiXtendV2SServer(void)
    : PiXtendBaseServer("PiXtendV2S", 1002)
    {
    	ServerVariable::SPtr serverVariable;

    	// register digital input variables
    	serverVariable = boost::make_shared<ServerVariable>("DI_DI0_Variable");
    	serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI1_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI2_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI3_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI4_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI5_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI6_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("DI_DI7_Variable");
		serverVariables().registerServerVariable(serverVariable);

		// register analog input variables
		serverVariable = boost::make_shared<ServerVariable>("AI_AI0_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("AI_AI1_Variable");
		serverVariables().registerServerVariable(serverVariable);

		// register analog output variables
		serverVariable = boost::make_shared<ServerVariable>("AO_AO0_Variable");
		serverVariables().registerServerVariable(serverVariable);
		serverVariable = boost::make_shared<ServerVariable>("AO_AO1_Variable");
		serverVariables().registerServerVariable(serverVariable);
    }

    PiXtendV2SServer::~PiXtendV2SServer(void)
    {
    }

    bool
	PiXtendV2SServer::handleStartup(void)
    {
    	// get pixtend v2s access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendV2S();

    	// create node context for digital output pins
    	createNodeContext({
    		{"DO_DO0_Variable", V2S_DO_RF(do0), V2S_DO_WF(do0)},
    		{"DO_DO1_Variable", V2S_DO_RF(do1), V2S_DO_WF(do1)},
    		{"DO_DO2_Variable", V2S_DO_RF(do2), V2S_DO_WF(do2)},
    		{"DO_DO3_Variable", V2S_DO_RF(do3), V2S_DO_WF(do3)},
			{"RELAY_RELAY0_Variable", V2S_DO_RF(relay0), V2S_DO_WF(relay0)},
			{"RELAY_RELAY1_Variable", V2S_DO_RF(relay1), V2S_DO_WF(relay1)},
			{"RELAY_RELAY2_Variable", V2S_DO_RF(relay2), V2S_DO_WF(relay2)},
			{"RELAY_RELAY3_Variable", V2S_DO_RF(relay3), V2S_DO_WF(relay3)}
    	});

    	// startup pixtend interface
    	pixtend_->startup();

    	// create object instance in information model
    	if (!createObjectInstance()) {
    		return false;
    	}


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
