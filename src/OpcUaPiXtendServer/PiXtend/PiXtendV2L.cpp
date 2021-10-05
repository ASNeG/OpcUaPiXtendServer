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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2L.h"

#define V2L_AI(PIN_NAME) PIXTEND_BASE_AI(PiXtendV2L, PIN_NAME)
#define V2L_AO(PIN_NAME) PIXTEND_BASE_AO(PiXtendV2L, PIN_NAME)
#define V2L_DI(PIN_NAME) PIXTEND_BASE_DI(PiXtendV2L, PIN_NAME)
#define V2L_DO(PIN_NAME) PIXTEND_BASE_DO(PiXtendV2L, PIN_NAME)


namespace OpcUaPiXtendServer
{

    PiXtendV2L::PiXtendV2L(const std::string& instanceName)
    : PiXtendBase(instanceName)
    {
    }

    PiXtendV2L::~PiXtendV2L(void)
    {
    }

    void
 	PiXtendV2L::handleRegisterContext(void)
    {
        registerContext({
     		// analog inputs
     		{ "AI0", V2L_AI(ai0)},
			{ "AI1", V2L_AI(ai1)},
     		{ "AI2", V2L_AI(ai2)},
     		{ "AI3", V2L_AI(ai3)},
     		{ "AI4", V2L_AI(ai4)},
     		{ "AI5", V2L_AI(ai5)},

     		// analog outputs
     		{ "AO0", V2L_AO(ao0)},
			{ "AO1", V2L_AO(ao1)},

			// digital inpits
			{ "DI0", V2L_DI(di0)},
			{ "DI1", V2L_DI(di1)},
			{ "DI2", V2L_DI(di2)},
			{ "DI3", V2L_DI(di3)},
			{ "DI4", V2L_DI(di4)},
			{ "DI5", V2L_DI(di5)},
			{ "DI6", V2L_DI(di6)},
			{ "DI7", V2L_DI(di7)},
			{ "DI8", V2L_DI(di8)},
			{ "DI9", V2L_DI(di9)},
			{ "DI10", V2L_DI(di10)},
			{ "DI11", V2L_DI(di11)},
			{ "DI12", V2L_DI(di12)},
			{ "DI13", V2L_DI(di13)},
			{ "DI14", V2L_DI(di14)},
			{ "DI15", V2L_DI(di15)},

			// digital outputs
			{ "DO0", V2L_DO(do0)},
			{ "DO1", V2L_DO(do1)},
			{ "DO2", V2L_DO(do2)},
			{ "DO3", V2L_DO(do3)},
			{ "DO4", V2L_DO(do4)},
			{ "DO5", V2L_DO(do5)},
			{ "DO6", V2L_DO(do6)},
			{ "DO7", V2L_DO(do7)},
			{ "DO8", V2L_DO(do8)},
			{ "DO9", V2L_DO(do9)},
			{ "DO10", V2L_DO(do10)},
			{ "DO11", V2L_DO(do11)},

			{ "RELAY0", V2L_DO(relay0)},
			{ "RELAY1", V2L_DO(relay1)},
			{ "RELAY2", V2L_DO(relay2)},
			{ "RELAY3", V2L_DO(relay3)},
     	});
     }

}
