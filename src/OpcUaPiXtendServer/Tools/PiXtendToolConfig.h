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
#include <unordered_map>

namespace OpcUaPiXtendServer
{

    using DValue = std::pair<bool /*exists*/, bool /*value*/>;
    using AValue = std::pair<bool /*exists*/, double /*value*/>;
    using ModuleAddress = std::pair<bool /*exists*/, uint32_t /*value*/>;

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

    const std::unordered_map<std::string, Pins> mapString2Pin = {
            {"ai0", Pins::Pin_AI0},
            {"ai1", Pins::Pin_AI1},
            {"ai2", Pins::Pin_AI2},
            {"ai3", Pins::Pin_AI3},
            {"ai4", Pins::Pin_AI4},
            {"ai5", Pins::Pin_AI5},

            {"ao0", Pins::Pin_AO0},
            {"ao1", Pins::Pin_AO1},
            {"ao2", Pins::Pin_AO2},
            {"ao3", Pins::Pin_AO3},
            {"ao4", Pins::Pin_AO4},
            {"ao5", Pins::Pin_AO5},

            {"di0", Pins::Pin_DI0},
            {"di1", Pins::Pin_DI1},
            {"di2", Pins::Pin_DI2},
            {"di3", Pins::Pin_DI3},
            {"di4", Pins::Pin_DI4},
            {"di5", Pins::Pin_DI5},
            {"di6", Pins::Pin_DI6},
            {"di7", Pins::Pin_DI7},
            {"di8", Pins::Pin_DI8},
            {"di9", Pins::Pin_DI9},
            {"di10", Pins::Pin_DI10},
            {"di11", Pins::Pin_DI11},
            {"di12", Pins::Pin_DI12},
            {"di13", Pins::Pin_DI13},
            {"di14", Pins::Pin_DI14},
            {"di15", Pins::Pin_DI15},

            {"do0", Pins::Pin_DO0},
            {"do1", Pins::Pin_DO1},
            {"do2", Pins::Pin_DO2},
            {"do3", Pins::Pin_DO3},
            {"do4", Pins::Pin_DO4},
            {"do5", Pins::Pin_DO5},
            {"do6", Pins::Pin_DO6},
            {"do7", Pins::Pin_DO7},
            {"do8", Pins::Pin_DO8},
            {"do9", Pins::Pin_DO9},
            {"do10", Pins::Pin_DO10},
            {"do11", Pins::Pin_DO11},

            {"relay0", Pins::Pin_Relay0},
            {"relay1", Pins::Pin_Relay1},
            {"relay2", Pins::Pin_Relay2},
            {"relay3", Pins::Pin_Relay3},

            {"gpio0", Pins::Pin_GPIO0},
            {"gpio1", Pins::Pin_GPIO1},
            {"gpio2", Pins::Pin_GPIO2},
            {"gpio3", Pins::Pin_GPIO3}
    };

    class PiXtendToolConfig
    {
      public:
        PiXtendToolConfig(void) = default;
        virtual ~PiXtendToolConfig(void) = default;

        static bool mapInputPin(std::string& strPin, Pins& pin);
        static bool mapDValue(std::string& strDValue, bool dValue);

      private:

    };

}

#endif
