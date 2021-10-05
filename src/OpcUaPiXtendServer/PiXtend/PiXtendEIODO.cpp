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

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODO.h"

#define EIODO_DI(PIN_NAME) PIXTEND_BASE_DI(PiXtendEIODO, PIN_NAME)
#define EIODO_DO(PIN_NAME) PIXTEND_BASE_DO(PiXtendEIODO, PIN_NAME)

namespace OpcUaPiXtendServer
{

    PiXtendEIODO::PiXtendEIODO(const std::string& instanceName)
    : PiXtendBase(instanceName)
    {
    }

    PiXtendEIODO::~PiXtendEIODO(void)
    {
    }

    void
	PiXtendEIODO::handleRegisterContext(void)
    {
    	registerContext({
       		// digital inputs
    		{ "DI0", EIODO_DI(di0)},
    		{ "DI1", EIODO_DI(di1)},
    		{ "DI2", EIODO_DI(di2)},
    		{ "DI3", EIODO_DI(di3)},
    		{ "DI4", EIODO_DI(di4)},
    		{ "DI5", EIODO_DI(di5)},
    		{ "DI6", EIODO_DI(di6)},
    		{ "DI7", EIODO_DI(di7)},

        	// digital outputs
    		{ "DO0", EIODO_DO(do0)},
    		{ "DO1", EIODO_DO(do1)},
    		{ "DO2", EIODO_DO(do2)},
    		{ "DO3", EIODO_DO(do3)},
			{ "DO4", EIODO_DO(do4)},
			{ "DO5", EIODO_DO(do5)},
			{ "DO6", EIODO_DO(do6)},
			{ "DO7", EIODO_DO(do7)},
    	});
    }
}
