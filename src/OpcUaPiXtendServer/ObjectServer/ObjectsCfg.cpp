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

#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/ObjectServer/ObjectsCfg.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    // #################################################################
    //
    // NodeMapCfg class
    //
    // #################################################################

    NodeMapCfg::NodeMapCfg(void)
    {
    }

    NodeMapCfg::~NodeMapCfg(void)
    {
    }

    bool
    NodeMapCfg::parse(OpcUaStackCore::Config* config)
    {
        if (config == nullptr) {
            Log(Error, "ObjectCfg parse error - config is empty");
            return false;
        }

        auto cfgNode = config->getChild("Node");
        if (!cfgNode) {
            Log(Error, "NodeMapCfg parser cannot find cfgNode");
            return false;
        }
        nodeName_ = cfgNode->getValue();
        nodeName_ += "_Variable"; // add sufix

        if (config->exist("Pin")) {
            auto cfgPin = config->getChild("Pin");
            if (!cfgPin) {
                Log(Error, "NodeMapCfg parser cannot find cfgPin")
                        .parameter("Node", nodeName_);;
                return false;
            }
            std::string pin = cfgPin->getValue();
            std::vector<std::string> splitString;
            boost::split(splitString, pin, boost::is_any_of("."));
            if (splitString.size() == 1) {
                pinName_ = splitString.at(0);
            } else {
                pinInstanceName_ = splitString.at(0);
                pinName_ = splitString.at(1);
            }
        } else if (config->exist("Value")) {
            auto cfgValue = config->getChild("Value");
            if (!cfgValue) {
                Log(Error, "NodeMapCfg parser cannot find cfgValue")
                        .parameter("Node", nodeName_);
                return false;
            }
            value_ = boost::make_shared<OpcUaVariant>();
            if (!value_->fromString(cfgValue->getValue())) {
                Log(Error, "NodeMapCfg parser cannot convert cfgValue")
                        .parameter("Node", nodeName_);
                return false;
            }
        } else {
            Log(Error, "NodeMapCfg needs Pin or Value parameter!")
                    .parameter("Node", nodeName_);
            return false;
        }

        Log(Debug, "new NodeMap")
                .parameter("NodeName", nodeName_)
                .parameter("PinInstanceName", pinInstanceName_)
                .parameter("PinName", pinName_)
                .parameter("Value", value_);

        return true;
    }

    std::string&
    NodeMapCfg::nodeName(void)
    {
        return nodeName_;
    }

    std::string&
    NodeMapCfg::pinName(void)
    {
        return pinName_;
    }

    std::string&
    NodeMapCfg::pinInstanceName(void)
    {
        return pinInstanceName_;
    }

    OpcUaVariant::SPtr
    NodeMapCfg::value(void)
    {
        return value_;
    }

    // #################################################################
    //
    // ObjectCfg class
    //
    // #################################################################

    ObjectCfg::ObjectCfg(void)
    {
    }

    ObjectCfg::~ObjectCfg(void)
    {
    }

    bool
    ObjectCfg::parse(OpcUaStackCore::Config* config)
    {
        if (config == nullptr) {
            Log(Error, "ObjectCfg parse error - config is empty");
            return false;
        }

        auto cfgName = config->getChild("<xmlattr>.Name");
        if (!cfgName) {
            Log(Error, "ObjectCfg parser cannot find cfgName");
            return false;
        }
        name_ = cfgName->getValue();

        auto cfgNamespaceName = config->getChild("<xmlattr>.Namespace");
        if (!cfgNamespaceName) {
            Log(Error, "ObjectCfg parser cannot find cfgNamespaceName");
            return false;
        }
        namespaceName_ = cfgNamespaceName->getValue();

        if (!config->existChild("<xmlattr>.Type")) {
            Log(Error, "ObjectCfg parser cannot find cfgType");
            return false;
        }
        config->getConfigParameter("<xmlattr>.Type", type_);

        if (config->existChild("<xmlattr>.Enable")) {
            config->getConfigParameter("<xmlattr>.Enable", enable_);
        }
        if (!enable_) {
            return true;
        }

        auto cfgFolderObj = config->getChild("FolderObject");
        if (!cfgFolderObj) {
            Log(Error, "ObjectCfg parser cannot find cfgFolderObj");
            return false;
        }
        folderObject_ = cfgFolderObj->getValue();

        // NodeMapCfgs
        std::vector<Config> configNodeMapCfgs;
        config->getChilds("NodeMap", configNodeMapCfgs);
        nodeMapCfgs_.reserve(configNodeMapCfgs.size());
        for (Config cfgPin : configNodeMapCfgs) {
            // parse NodeMapCfg configuration
            NodeMapCfg::SPtr nodeMapCfgSPtr = boost::make_shared<NodeMapCfg>();
            if (!nodeMapCfgSPtr->parse(&cfgPin)) {
                Log(Error, "cfg found error in NodeMapCfg configuration");
                return false;
            }
            nodeMapCfgs_.push_back(nodeMapCfgSPtr);
        }

        // UnitConv
        std::vector<Config> configUnitConversionConfigs;
        config->getChilds("UnitConv", configUnitConversionConfigs);
        unitConversionConfigMap_.reserve(configUnitConversionConfigs.size());
        for (Config cfgNode : configUnitConversionConfigs) {
            UnitConversionConfig::SPtr unitConv = boost::make_shared<UnitConversionConfig>();
            if (!unitConv->parse(&cfgNode)) {
                Log(Error, "parse CtrlNodes in controller configuration error");
                return false;
            }
            unitConversionConfigMap_.insert(std::make_pair(unitConv->nodeName(), unitConv));
        }

        Log(Debug, "new ObjectCfg")
                .parameter("Name", name_)
                .parameter("Namespace", namespaceName_)
                .parameter("Type", type_)
                .parameter("FolderObject", cfgFolderObj->getValue())
                .parameter("NodeMapCfgs", nodeMapCfgs_.size())
                .parameter("UnitConv", unitConversionConfigMap_.size());

        return true;
    }

    bool
    ObjectCfg::enable(void)
    {
        return enable_;
    }

    std::string&
    ObjectCfg::name(void)
    {
        return name_;
    }

    std::string&
    ObjectCfg::namespaceName(void)
    {
        return namespaceName_;
    }

    std::string&
    ObjectCfg::folderObject(void)
    {
        return folderObject_;
    }

    uint32_t
    ObjectCfg::type(void)
    {
        return type_;
    }

    NodeMapCfg::Vec&
    ObjectCfg::nodeMapCfgs(void)
    {
        return nodeMapCfgs_;
    }

    UnitConversionConfig::Map&
    ObjectCfg::unitConversionConfigMap(void)
    {
        return unitConversionConfigMap_;
    }

    // #################################################################
    //
    // ObjectsCfg class
    //
    // #################################################################

    ObjectsCfg::ObjectsCfg(void)
    {
    }

    ObjectsCfg::~ObjectsCfg(void)
    {
    }

    bool
    ObjectsCfg::parse(Config* config)
    {
        boost::optional<Config> objectsCfg = config->getChild("Objects");
        if (!objectsCfg) {
            // Objects parameter are optional
            Log(Info, "optional parameter 'Objects' missing in controller configuration");
            return true;
        }

        std::vector<Config> configVec;
        objectsCfg->getChilds("Object", configVec);
        for (Config cfgObject : configVec) {
            ObjectCfg::SPtr objectCfgSPtr = boost::make_shared<ObjectCfg>();
            if (!objectCfgSPtr->parse(&cfgObject)) {
                Log(Error, "cfg found error in ObjectCfg configuration");
                return false;
            }
            if (objectCfgSPtr->enable()) {
                configObjectCfgs_.push_back(objectCfgSPtr);
            } else {
                Log(Debug, "objectCfg is not enabled")
                        .parameter("Name", objectCfgSPtr->name());
            }
        }

        return true;
    }

    ObjectCfg::Vec&
    ObjectsCfg::configObjectCfgs(void)
    {
        return configObjectCfgs_;
    }

}
