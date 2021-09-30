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

#include "OpcUaPiXtendServer/Tools/PiXtendToolConfig.h"

namespace OpcUaPiXtendServer
{

    bool
    PiXtendToolConfig::mapInputPin(std::string& strPin, Pins& pin)
    {
        auto findPin = mapString2Pin.find(strPin);

        if (findPin == mapString2Pin.end())
        {
            pin = Pins::Pin_Undefined;
            return false;
        }

        pin = findPin->second;
        return true;
    }

    bool
    PiXtendToolConfig::mapDValue(std::string& strDValue, bool dValue)
    {
        if (strDValue == operationDValueOn)
        {
            dValue = true;
            return true;
        }
        else if (strDValue == operationDValueOff)
        {
            dValue = false;
            return true;
        }
        return false;
    }

}
