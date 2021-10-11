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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"

#define V2S_AI(PIN_NAME) PIXTEND_BASE_AI(PiXtendV2S, PIN_NAME)
#define V2S_AO(PIN_NAME) PIXTEND_BASE_AO(PiXtendV2S, PIN_NAME)
#define V2S_DI(PIN_NAME) PIXTEND_BASE_DI(PiXtendV2S, PIN_NAME)
#define V2S_DO(PIN_NAME) PIXTEND_BASE_DO(PiXtendV2S, PIN_NAME)

namespace OpcUaPiXtendServer
{

    PiXtendV2S::PiXtendV2S(const std::string& instanceName)
    : PiXtendBase(instanceName)
    {
    }

    PiXtendV2S::~PiXtendV2S(void)
    {
    }

    void
	PiXtendV2S::handleRegisterContext(void)
    {
    	registerContext({
    		// analog inputs
    		{ "AI0", V2S_AI(ai0)},
			{ "AI1", V2S_AI(ai1)},

    		// analog outputs
            { "AO0", V2S_AO(ao0)},
            { "AO1", V2S_AO(ao1)},

    		// digital inputs
			{ "DI0", V2S_DI(di0)},
			{ "DI1", V2S_DI(di1)},
			{ "DI2", V2S_DI(di2)},
			{ "DI3", V2S_DI(di3)},
			{ "DI4", V2S_DI(di4)},
			{ "DI5", V2S_DI(di5)},
			{ "DI6", V2S_DI(di6)},
			{ "DI7", V2S_DI(di7)},

    		// digital outputs
			{ "DO0", V2S_DO(do0)},
			{ "DO1", V2S_DO(do1)},
			{ "DO2", V2S_DO(do2)},
			{ "DO3", V2S_DO(do3)},
			{ "RELAY0", V2S_DO(relay0)},
			{ "RELAY1", V2S_DO(relay1)},
			{ "RELAY2", V2S_DO(relay2)},
			{ "RELAY3", V2S_DO(relay3)}
    	});
    }
}
