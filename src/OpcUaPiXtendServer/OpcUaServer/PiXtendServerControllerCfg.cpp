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
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendServerControllerCfg.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    // ##################################################################
    //
    // UnitConversionConfig class
    //
    // ##################################################################

    UnitConversionConfig::UnitConversionConfig(void)
    {
    }

    UnitConversionConfig::~UnitConversionConfig(void)
    {
    }

    bool
    UnitConversionConfig::parse(OpcUaStackCore::Config* config)
    {
        if (config == nullptr) {
            Log(Error, "parse UnitConversionConfig error - config is empty");
            return false;
        }

        auto cfgNodeName = config->getChild("Node");
        if (!cfgNodeName) {
            Log(Error, "UnitConversionConfig cannot get cfgNodeName in controller configuration");
            return false;
        }
        nodeName_ = cfgNodeName->getValue();
        nodeName_ += "_Variable"; // add sufix

        if (!config->existChild("A") || !config->existChild("B") ||
            !config->existChild("C") || !config->existChild("D")) {
            Log(Error, "UnitConversionConfig unitConverter information are incomplete in controller configuration");
            return false;
        }

        bool rc = true;
        rc = rc && config->getConfigParameter("A", a_);
        rc = rc && config->getConfigParameter("B", b_);
        rc = rc && config->getConfigParameter("C", c_);
        rc = rc && config->getConfigParameter("D", d_);

        if (!rc) {
            Log(Error, "UnitConversionConfig unitConverter cannot handle configuration parameter")
                    .parameter("Node", nodeName_)
                    .parameter("A", a_).parameter("B", b_)
                    .parameter("C", c_).parameter("D", d_);
            return false;
        }

        Log(Debug, "new UnitConversionConfig")
                .parameter("Node", nodeName_)
                .parameter("A", a_).parameter("B", b_)
                .parameter("C", c_).parameter("D", d_);

        return true;
    }

    std::string
    UnitConversionConfig::nodeName(void)
    {
        return nodeName_;
    }

    double
    UnitConversionConfig::a(void)
    {
        return a_;
    }

    double
    UnitConversionConfig::b(void)
    {
        return b_;
    }

    double
    UnitConversionConfig::c(void)
    {
        return c_;
    }

    double
    UnitConversionConfig::d(void)
    {
        return d_;
    }

    // ##################################################################
    //
    // PiXtendServerControllerCfgModule class
    //
    // ##################################################################

    PiXtendServerControllerCfgModule::PiXtendServerControllerCfgModule()
    {

    }

    PiXtendServerControllerCfgModule::~PiXtendServerControllerCfgModule()
    {

    }

    bool
    PiXtendServerControllerCfgModule::parse(Config* config)
    {
        if (config == nullptr) {
            Log(Error, "parse PiXtendServerControllerCfgModule error - config is empty");
            return false;
        }

        auto cfgName = config->getChild("Name");
        if (!cfgName) {
            Log(Error, "PiXtendServerControllerCfgModule cannot get cfgName in controller configuration");
            return false;
        }
        moduleName_ = cfgName->getValue();

        if (config->existChild("<xmlattr>.Enable")) {
            config->getConfigParameter("<xmlattr>.Enable", enable_);
        }
        if (!enable_) {
            return true;
        }

        auto cfgType = config->getChild("Type");
        if (!cfgType) {
            Log(Error, "PiXtendServerControllerCfgModule cannot get cfgType in controller configuration");
            return false;
        }
        std::string strModuleType = cfgType->getValue();
        boost::algorithm::to_lower(strModuleType);
        auto findModuleType = MapType2ServerModule.find(strModuleType);
        if (findModuleType == MapType2ServerModule.end()) {
            Log(Error, "PiXtendServerControllerCfgModule undefined cfgType in controller configuration")
                    .parameter("Name", moduleName());
            return false;
        }
        moduleType_ = findModuleType->second;

        if (config->existChild("Address")) {
            config->getConfigParameter("Address", moduleAddress_);
        }

        std::vector<Config> configVec;
        config->getChilds("UnitConv", configVec);
        unitConversionConfigMap_.reserve(configVec.size());
        for (Config cfgNode : configVec) {
            UnitConversionConfig::SPtr unitConv = boost::make_shared<UnitConversionConfig>();
            if (!unitConv->parse(&cfgNode)) {
                Log(Error, "parse CtrlNodes in controller configuration error");
                return false;
            }
            unitConversionConfigMap_.insert(std::make_pair(unitConv->nodeName(), unitConv));
        }

        Log(Debug, "new Module")
                .parameter("Name", moduleName_)
                .parameter("Type", strModuleType)
                .parameter("Address", moduleAddress_);

        return true;
    }

    bool
    PiXtendServerControllerCfgModule::enable(void)
    {
        return enable_;
    }

    std::string
    PiXtendServerControllerCfgModule::moduleName(void)
    {
        return moduleName_;
    }

    ServerModule
    PiXtendServerControllerCfgModule::moduleType(void)
    {
        return moduleType_;
    }

    uint32_t
    PiXtendServerControllerCfgModule::moduleAddress(void)
    {
        return moduleAddress_;
    }

    UnitConversionConfig::Map
    PiXtendServerControllerCfgModule::unitConversionConfigMap(void)
    {
        return unitConversionConfigMap_;
    }

    // ##################################################################
    //
    // PiXtendServerControllerCfg class
    //
    // ##################################################################

    PiXtendServerControllerCfg::PiXtendServerControllerCfg()
    {

    }

    PiXtendServerControllerCfg::~PiXtendServerControllerCfg()
    {

    }

    bool
    PiXtendServerControllerCfg::parse(Config* config)
    {
        if (config == nullptr) {
            Log(Error, "parse cfg error - config is empty");
            return false;
        }

        // get CtrlModules element
        boost::optional<Config> childCtrlModules = config->getChild("Modules");
        if (!childCtrlModules) {
            Log(Error, "parameter CtrlModules missing in controller configuration");
            return false;
        }

        std::vector<Config> configVec;
        childCtrlModules->getChilds("Module", configVec);
        for (Config cfgModule : configVec) {
        	// parse module configuration
            PiXtendServerControllerCfgModule module;
            if (!module.parse(&cfgModule)) {
                Log(Error, "parse CtrlModules in controller configuration error");
                return false;
            }
            if (module.enable()) {
                configModules_.push_back(module);
            } else {
                Log(Debug, "module is not enabled")
                        .parameter("Name", module.moduleName());
            }
        }

        return true;
    }

    std::vector<PiXtendServerControllerCfgModule>&
    PiXtendServerControllerCfg::configModules(void)
    {
        return configModules_;
    }

}
