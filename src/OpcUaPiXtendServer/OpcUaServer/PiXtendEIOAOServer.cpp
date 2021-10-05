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
    	// get pixtend v2s access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendEIOAO(instanceName_);

       	// startup pixtend interface
        pixtend_->startup(moduleAddress_);

        // set analog output configuration
        aOConfigVec_ = {
            {"AO_AO0_Variable", EIOAO_AO_RF(ao0), EIOAO_AO_WF(ao0)},
            {"AO_AO1_Variable", EIOAO_AO_RF(ao1), EIOAO_AO_WF(ao1)},
			{"AO_AO2_Variable", EIOAO_AO_RF(ao2), EIOAO_AO_WF(ao2)},
			{"AO_AO3_Variable", EIOAO_AO_RF(ao3), EIOAO_AO_WF(ao3)},
			{"AO_AO4_Variable", EIOAO_AO_RF(ao4), EIOAO_AO_WF(ao4)},
			{"AO_AO5_Variable", EIOAO_AO_RF(ao5), EIOAO_AO_WF(ao5)}
        };

        // set analog input configuration
        aIConfigVec_ = {
            {"AI_AI0_Variable", EIOAO_AI_RF(ai0)},
            {"AI_AI1_Variable", EIOAO_AI_RF(ai1)},
			{"AI_AI2_Variable", EIOAO_AI_RF(ai2)},
			{"AI_AI3_Variable", EIOAO_AI_RF(ai3)},
			{"AI_AI4_Variable", EIOAO_AI_RF(ai4)},
			{"AI_AI5_Variable", EIOAO_AI_RF(ai5)},
			{"AI_AI6_Variable", EIOAO_AI_RF(ai6)},
			{"AI_AI7_Variable", EIOAO_AI_RF(ai7)}
        };
    	return true;
    }

    bool
	PiXtendEIOAOServer::handleShutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();
    	pixtend_.reset();

    	return true;
    }

}
