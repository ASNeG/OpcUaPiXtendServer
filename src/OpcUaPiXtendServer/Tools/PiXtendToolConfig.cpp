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
        if (strPin == "ai0") pin = Pins::Pin_AI0;
        else if (strPin == "ai1") pin = Pins::Pin_AI1;
        else if (strPin == "ai2") pin = Pins::Pin_AI2;
        else if (strPin == "ai3") pin = Pins::Pin_AI3;
        else if (strPin == "ai4") pin = Pins::Pin_AI4;
        else if (strPin == "ai5") pin = Pins::Pin_AI5;

        else if (strPin == "ao0") pin = Pins::Pin_AO0;
        else if (strPin == "ao1") pin = Pins::Pin_AO1;
        else if (strPin == "ao2") pin = Pins::Pin_AO2;
        else if (strPin == "ao3") pin = Pins::Pin_AO3;
        else if (strPin == "ao4") pin = Pins::Pin_AO4;
        else if (strPin == "ao5") pin = Pins::Pin_AO5;

        else if (strPin == "di0") pin = Pins::Pin_DI0;
        else if (strPin == "di1") pin = Pins::Pin_DI1;
        else if (strPin == "di2") pin = Pins::Pin_DI2;
        else if (strPin == "di3") pin = Pins::Pin_DI3;
        else if (strPin == "di4") pin = Pins::Pin_DI4;
        else if (strPin == "di5") pin = Pins::Pin_DI5;
        else if (strPin == "di6") pin = Pins::Pin_DI6;
        else if (strPin == "di7") pin = Pins::Pin_DI7;
        else if (strPin == "di8") pin = Pins::Pin_DI8;
        else if (strPin == "di9") pin = Pins::Pin_DI9;
        else if (strPin == "di10") pin = Pins::Pin_DI10;
        else if (strPin == "di11") pin = Pins::Pin_DI11;
        else if (strPin == "di12") pin = Pins::Pin_DI12;
        else if (strPin == "di13") pin = Pins::Pin_DI13;
        else if (strPin == "di14") pin = Pins::Pin_DI14;
        else if (strPin == "di15") pin = Pins::Pin_DI15;

        else if (strPin == "do0") pin = Pins::Pin_DO0;
        else if (strPin == "do1") pin = Pins::Pin_DO1;
        else if (strPin == "do2") pin = Pins::Pin_DO2;
        else if (strPin == "do3") pin = Pins::Pin_DO3;
        else if (strPin == "do4") pin = Pins::Pin_DO4;
        else if (strPin == "do5") pin = Pins::Pin_DO5;
        else if (strPin == "do6") pin = Pins::Pin_DO6;
        else if (strPin == "do7") pin = Pins::Pin_DO7;
        else if (strPin == "do8") pin = Pins::Pin_DO8;
        else if (strPin == "do9") pin = Pins::Pin_DO9;
        else if (strPin == "do10") pin = Pins::Pin_DO10;
        else if (strPin == "do11") pin = Pins::Pin_DO11;

        else if (strPin == "relay0") pin = Pins::Pin_Relay0;
        else if (strPin == "relay1") pin = Pins::Pin_Relay1;
        else if (strPin == "relay2") pin = Pins::Pin_Relay2;
        else if (strPin == "relay3") pin = Pins::Pin_Relay3;

        else if (strPin == "gpio0") pin = Pins::Pin_GPIO0;
        else if (strPin == "gpio1") pin = Pins::Pin_GPIO1;
        else if (strPin == "gpio2") pin = Pins::Pin_GPIO2;
        else if (strPin == "gpio3") pin = Pins::Pin_GPIO3;

        else
        {
            pin = Pins::Pin_Undefined;
            return false;
        }
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
