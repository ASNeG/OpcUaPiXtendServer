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

#ifndef __OpcUaPiXtendServer_PiXtendToolConfig_h__
#define __OpcUaPiXtendServer_PiXtendToolConfig_h__

#include <string>

namespace OpcUaPiXtendServer
{

    using DValue = std::pair<bool /*exists*/, bool /*value*/>;
    using AValue = std::pair<bool /*exists*/, double /*value*/>;

    struct PiXtendToolReadStruct
    {
        AValue aValue;
        DValue dValue;
    };

    const std::string piXtendModule_V2S   {"v2s"};
    const std::string piXtendModule_V2L   {"v2l"};
    const std::string piXtendModule_EIOAO {"ao"};
    const std::string piXtendModule_EIODO {"do"};

    const std::string operationRead       {"read"};
    const std::string operationWrite      {"write"};
    const std::string operationDValueOn   {"on"};
    const std::string operationDValueOff  {"off"};

    enum Pins : uint16_t
    {
        Pin_Undefined,

        Pin_AI0,Pin_AI1,Pin_AI2,Pin_AI3,Pin_AI4,Pin_AI5,Pin_AI6,Pin_AI7,

        Pin_AO0,Pin_AO1,Pin_AO2,Pin_AO3,Pin_AO4,Pin_AO5,

        Pin_DI0,Pin_DI1,Pin_DI2,Pin_DI3,Pin_DI4,Pin_DI5,
        Pin_DI6,Pin_DI7,Pin_DI8,Pin_DI9,Pin_DI10,Pin_DI11,
        Pin_DI12,Pin_DI13,Pin_DI14,Pin_DI15,

        Pin_DO0,Pin_DO1,Pin_DO2,Pin_DO3,Pin_DO4,Pin_DO5,
        Pin_DO6,Pin_DO7,Pin_DO8,Pin_DO9,Pin_DO10,Pin_DO11,

        Pin_Relay0,Pin_Relay1,Pin_Relay2,Pin_Relay3,

        Pin_GPIO0,Pin_GPIO1,Pin_GPIO2,Pin_GPIO3
    };



    class PiXtendToolConfig
    {
      public:
        PiXtendToolConfig(void) = default;
        virtual ~PiXtendToolConfig(void) = default;

        static bool mapInputPin(std::string& strPin, Pins& pin);
        static bool mapDValue(std::string& strDValue, bool dValue);
    };

}

#endif
