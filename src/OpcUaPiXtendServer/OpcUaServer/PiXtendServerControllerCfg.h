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

    class PiXtendServerControllerCfgNode
    {
      public:
        using Vec = std::vector<PiXtendServerControllerCfgNode>;

        PiXtendServerControllerCfgNode(void);
        ~PiXtendServerControllerCfgNode(void);

        bool parse(OpcUaStackCore::Config* config);

        std::string nodeName(void);
        std::string pinName(void);

        bool unitConverterExists(void);
        double unitConverterA(void);
        double unitConverterB(void);
        double unitConverterC(void);
        double unitConverterD(void);

      private:
        std::string nodeName_ {""};
        std::string pinName_ {""};

        bool unitConverterExists_ {false};
        double unitConverterA_ {0.0};
        double unitConverterB_ {0.0};
        double unitConverterC_ {0.0};
        double unitConverterD_ {0.0};
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

        PiXtendServerControllerCfgNode::Vec nodes(void);

      private:
        std::string moduleName_ {""};
        ServerModule moduleType_ {ServerModule::Unknown};
        uint32_t moduleAddress_ {0};

        PiXtendServerControllerCfgNode::Vec nodes_;
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
