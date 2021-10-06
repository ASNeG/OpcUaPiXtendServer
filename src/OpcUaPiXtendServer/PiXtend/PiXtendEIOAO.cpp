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

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAO.h"

#define EIOAO_AI(PIN_NAME) PIXTEND_BASE_AI(PiXtendEIOAO, PIN_NAME)
#define EIOAO_AO(PIN_NAME) PIXTEND_BASE_AO(PiXtendEIOAO, PIN_NAME)

namespace OpcUaPiXtendServer
{

    PiXtendEIOAO::PiXtendEIOAO(const std::string& instanceName)
    : PiXtendBase(instanceName)
    {
    }

    PiXtendEIOAO::~PiXtendEIOAO(void)
    {
    }

    void
 	PiXtendEIOAO::handleRegisterContext(void)
     {
     	registerContext({
        		// digital inputs
     		{ "AI0", EIOAO_AI(ai0)},
     		{ "AI1", EIOAO_AI(ai1)},
     		{ "AI2", EIOAO_AI(ai2)},
     		{ "AI3", EIOAO_AI(ai3)},
     		{ "AI4", EIOAO_AI(ai4)},
     		{ "AI5", EIOAO_AI(ai5)},
     		{ "AI6", EIOAO_AI(ai6)},
     		{ "AI7", EIOAO_AI(ai7)},

         	// digital outputs
     		{ "AO0", EIOAO_AO(ao0)},
     		{ "AO1", EIOAO_AO(ao1)},
     		{ "AO2", EIOAO_AO(ao2)},
     		{ "AO3", EIOAO_AO(ao3)},
 			{ "AO4", EIOAO_AO(ao4)},
 			{ "AO5", EIOAO_AO(ao5)},
     	});
     }

}
