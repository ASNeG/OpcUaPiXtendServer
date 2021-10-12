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

#ifndef __OpcUaPiXtendServer_PiXtendServerControllerCfg_h__
#define __OpcUaPiXtendServer_PiXtendServerControllerCfg_h__

#include <boost/shared_ptr.hpp>
#include <unordered_map>
#include "OpcUaStackCore/Base/Config.h"

namespace OpcUaPiXtendServer
{

    enum class ServerModule : uint8_t {
        Unknown,
        V2L,
        V2S,
        DO,
        AO
    };

    static const std::unordered_map<std::string, ServerModule> MapType2ServerModule =
    {
        { "v2s", ServerModule::V2S },
        { "v2l", ServerModule::V2L },
        { "ao", ServerModule::AO },
        { "do", ServerModule::DO }
    };

    class UnitConversionConfig
    {
      public:
        using SPtr = boost::shared_ptr<UnitConversionConfig>;
        using Map = std::unordered_map<std::string /*NodeName*/, UnitConversionConfig::SPtr>;

        UnitConversionConfig(void);
        ~UnitConversionConfig(void);

        bool parse(OpcUaStackCore::Config* config);

        std::string nodeName(void);

        double a(void);
        double b(void);
        double c(void);
        double d(void);

      private:
        std::string nodeName_ {""};

        double a_ {0.0};
        double b_ {0.0};
        double c_ {0.0};
        double d_ {0.0};
    };

    class PiXtendServerControllerCfgModule
    {
      public:
        PiXtendServerControllerCfgModule(void);
        ~PiXtendServerControllerCfgModule(void);

        bool parse(OpcUaStackCore::Config* config);

        std::string moduleName(void);
        ServerModule moduleType(void);
        uint32_t moduleAddress(void);

        UnitConversionConfig::Map unitConversionConfigMap(void);

      private:
        std::string moduleName_ {""};
        ServerModule moduleType_ {ServerModule::Unknown};
        uint32_t moduleAddress_ {0};

        UnitConversionConfig::Map unitConversionConfigMap_;
    };

    class PiXtendServerControllerCfg
    {
      public:

        using SPtr = boost::shared_ptr<PiXtendServerControllerCfg>;

        PiXtendServerControllerCfg(void);
        ~PiXtendServerControllerCfg(void);

        bool parse(OpcUaStackCore::Config* config);

        std::vector<PiXtendServerControllerCfgModule>& configModules(void);

      private:
        std::vector<PiXtendServerControllerCfgModule> configModules_;
    };

}

#endif
