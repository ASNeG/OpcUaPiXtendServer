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
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendServerControllerCfg.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendServerControllerCfgModule::PiXtendServerControllerCfgModule()
    {

    }

    PiXtendServerControllerCfgModule::~PiXtendServerControllerCfgModule()
    {

    }

    bool
    PiXtendServerControllerCfgModule::parse(Config* config)
    {
        if (config == nullptr)
        {
            Log(Error, "parse PiXtendServerControllerCfgModule error - config is empty");
            return false;
        }

        auto cfgName = config->getChild("Name");
        if (!cfgName)
        {
            Log(Error, "PiXtendServerControllerCfgModule cannot get cfgName in controller configuration");
            return false;
        }
        moduleName_ = cfgName->getValue();

        auto cfgType = config->getChild("Type");
        if (!cfgType)
        {
            Log(Error, "PiXtendServerControllerCfgModule cannot get cfgType in controller configuration");
            return false;
        }
        std::string strModuleType = cfgType->getValue();
        boost::algorithm::to_lower(strModuleType);
        auto findModuleType = MapType2ServerModule.find(strModuleType);
        if (findModuleType == MapType2ServerModule.end())
        {
            Log(Error, "PiXtendServerControllerCfgModule undefined cfgType in controller configuration")
                    .parameter("Name", moduleName());
            return false;
        }
        moduleType_ = findModuleType->second;


        if (config->existChild("Address"))
        {
            config->getConfigParameter("Address", moduleAddress_);
        }

        return true;
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
        configModules_.reserve(configVec.size());
        for (Config cfgModule : configVec) {
        	// check if module configuration is enabled
    		auto enable = cfgModule.getValue("<xmlattr>.Enable", "ON");
    		boost::to_upper(enable);
    		if (enable != "ON") continue;

        	// parse module configuration
            PiXtendServerControllerCfgModule module;
            if (!module.parse(&cfgModule)) {
                Log(Error, "parse CtrlModules in controller configuration error");
                return false;
            }
            configModules_.push_back(module);
        }

        return true;
    }

    std::vector<PiXtendServerControllerCfgModule>&
    PiXtendServerControllerCfg::configModules(void)
    {
        return configModules_;
    }

}
