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
#include <OpcUaPiXtendServer/Library/PiXtendServerCfg.h>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// USBCfg
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	USBCfg::USBCfg(void)
	{
	}

	USBCfg::~USBCfg(void)
	{
	}

	bool
	USBCfg::parse(Config* config)
	{
		// check parameter
        if (config == nullptr) {
            Log(Error, "parse UnitConversionConfig error - config is empty");
            return false;
        }

        // parse USB element (optional)
        auto usbChild = config->getChild("USB");
        if (!usbChild) {
            return true;
        }

        // parse device element
        auto deviceElement = usbChild->getValue("<xmlattr>.Device");
        if (!deviceElement) {
            Log(Error, "Device attribute not exist in USB element");
            return false;
        }
        device_ = *deviceElement;

        // parse baud element
        if (!usbChild->getConfigParameter("<xmlattr>.Baud", baud_)) {
            Log(Error, "Baud attribute not exist in USB element");
            return false;
        }

        // parse patity
        auto parityElement = usbChild->getValue("<xmlattr>.Parity");
        if (!parityElement) {
            Log(Error, "Parity attribute not exist in USB element");
            return false;
        }
        if (*parityElement == "N") { // None
        	parity_ = 'N';
        }
        else if (*parityElement == "E") { // Even
        	parity_ = 'E';
        }
        else if (*parityElement == "O") { // Odd
        	parity_ = 'O';
        }
        else {
            Log(Error, "Parity attribute invalid USB element")
            	.parameter("Parity", *parityElement);
             return false;
        }

        // parse data bit element
        if (!usbChild->getConfigParameter("<xmlattr>.DataBit", dataBit_)) {
            Log(Error, "DataBit attribute not exist in USB element");
            return false;
        }

        // parse stop bit element
        if (!usbChild->getConfigParameter("<xmlattr>.StopBit", stopBit_)) {
            Log(Error, "StopBit attribute not exist in USB element");
            return false;
        }

		return true;
	}


	std::string
	USBCfg::device(void)
	{
		return device_;
	}

	uint32_t
	USBCfg::baud(void)
	{
		return baud_;
	}

	char
	USBCfg::parity(void)
	{
		return parity_;
	}

	uint8_t
	USBCfg::dataBit()
	{
		return dataBit_;
	}

	uint8_t
	USBCfg::stopBit()
	{
		return stopBit_;
	}

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
    UnitConversionConfig::parse(Config* config)
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
    // PiXtendServerCfgModule class
    //
    // ##################################################################

    PiXtendServerCfgModule::PiXtendServerCfgModule()
    {

    }

    PiXtendServerCfgModule::~PiXtendServerCfgModule()
    {

    }

    bool
    PiXtendServerCfgModule::parse(Config* config)
    {
        if (config == nullptr) {
            Log(Error, "parse PiXtendServerCfgModule error - config is empty");
            return false;
        }

        // parse modul name
        auto moduleName = config->getValue("Name");
        if (!moduleName) {
            Log(Error, "Name element not exist in module configuration");
            return false;
        }
        moduleName_ = *moduleName;

        // parse enable flag (optional)
        config->getConfigParameter("<xmlattr>.Enable", enable_, "0");
        if (!enable_) {
            return true;
        }

        // parse module type
        auto moduleType = config->getValue("Type");
        if (!moduleType) {
            Log(Error, "Type element not exist in module configuration")
            	.parameter("ModuleName", moduleName_);
            return false;
        }
        std::string moduleTypeStr = boost::algorithm::to_lower_copy(*moduleType);
        auto findModuleType = MapType2ServerModule.find(moduleTypeStr);
        if (findModuleType == MapType2ServerModule.end()) {
            Log(Error, "Type element invalid in module configuration")
                    .parameter("ModuleName", moduleName_)
					.parameter("ModuleType", *moduleType);
            return false;
        }
        moduleType_ = findModuleType->second;

        // parse module address (optional)
        config->getConfigParameter("Address", moduleAddress_, "0");

        // parse module unit conversions
        std::vector<Config> configVec;
        config->getChilds("UnitConv", configVec);
        unitConversionConfigMap_.reserve(configVec.size());
        for (Config cfgNode : configVec) {
            UnitConversionConfig::SPtr unitConv = boost::make_shared<UnitConversionConfig>();
            if (!unitConv->parse(&cfgNode)) {
                Log(Error, "UnitConv element invalid in module configuration")
                    .parameter("ModuleName", moduleName_);
                return false;
            }
            unitConversionConfigMap_.insert(std::make_pair(unitConv->nodeName(), unitConv));
        }

        // parse USB information (optional)
        auto usbCfg = boost::make_shared<USBCfg>();
        if (!usbCfg->parse(config)) {
            Log(Error, "USB element invalid in module configuration")
				.parameter("ModuleName", moduleName_);
            return false;
        }
        if (!usbCfg->device().empty()) {
        	usbCfg_ = usbCfg;
        }

        return true;
    }

    bool
    PiXtendServerCfgModule::enable(void)
    {
        return enable_;
    }

    std::string
    PiXtendServerCfgModule::moduleName(void)
    {
        return moduleName_;
    }

    ServerModule
    PiXtendServerCfgModule::moduleType(void)
    {
        return moduleType_;
    }

    uint32_t
    PiXtendServerCfgModule::moduleAddress(void)
    {
        return moduleAddress_;
    }

    USBCfg::SPtr
	PiXtendServerCfgModule::usbCfg(void)
    {
    	return usbCfg_;
    }

    UnitConversionConfig::Map
    PiXtendServerCfgModule::unitConversionConfigMap(void)
    {
        return unitConversionConfigMap_;
    }

    // ##################################################################
    //
    // PiXtendServerCfg class
    //
    // ##################################################################

    PiXtendServerCfg::PiXtendServerCfg()
    {

    }

    PiXtendServerCfg::~PiXtendServerCfg()
    {

    }

    bool
    PiXtendServerCfg::parse(Config* config)
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
            PiXtendServerCfgModule module;
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

    std::vector<PiXtendServerCfgModule>&
    PiXtendServerCfg::configModules(void)
    {
        return configModules_;
    }

}
