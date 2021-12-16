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

#ifndef __ObjectServer_ObjectsCfg_h__
#define __ObjectServer_ObjectsCfg_h__

#include <boost/shared_ptr.hpp>
#include <unordered_map>

#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"

#include "OpcUaPiXtendServer/Library/PiXtendServerCfg.h"

namespace OpcUaPiXtendServer
{

    class NodeMapCfg
    {
      public:
        using SPtr = boost::shared_ptr<NodeMapCfg>;
        using Vec = std::vector<NodeMapCfg::SPtr>;

        NodeMapCfg(void);
        ~NodeMapCfg(void);

        bool parse(OpcUaStackCore::Config* config);

        std::string& nodeName(void);
        std::string& pinName(void);
        std::string& pinInstanceName(void);
        OpcUaStackCore::OpcUaVariant::SPtr value(void);

      private:
        std::string nodeName_ {""};
        std::string pinName_ {""};
        std::string pinInstanceName_ {""};
        OpcUaStackCore::OpcUaVariant::SPtr value_;
    };

    class ObjectCfg
    {
      public:
        using SPtr = boost::shared_ptr<ObjectCfg>;
        using Vec = std::vector<ObjectCfg::SPtr>;

        ObjectCfg(void);
        ~ObjectCfg(void);

        bool parse(OpcUaStackCore::Config* config);

        bool enable(void);
        std::string& name(void);
        std::string& namespaceName(void);
        uint32_t type(void);
        std::string& folderObject(void);
        NodeMapCfg::Vec& nodeMapCfgs(void);
        UnitConversionConfig::Map& unitConversionConfigMap(void);

      private:
        bool enable_ {true};
        std::string name_ {""};
        std::string namespaceName_ {""};
        std::string folderObject_ {""};
        uint32_t type_ {0};
        NodeMapCfg::Vec nodeMapCfgs_;
        UnitConversionConfig::Map unitConversionConfigMap_;
    };


    class ObjectsCfg
    {
      public:
        using SPtr = boost::shared_ptr<ObjectsCfg>;

        ObjectsCfg(void);
        ~ObjectsCfg(void);

        bool parse(OpcUaStackCore::Config* config);

        ObjectCfg::Vec& configObjectCfgs(void);

      private:
        ObjectCfg::Vec configObjectCfgs_;
    };

}

#endif
