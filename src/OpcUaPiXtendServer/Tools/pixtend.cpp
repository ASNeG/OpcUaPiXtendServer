
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
   Autor: Samuel Huebl (Samuel@huebl-sgh.de)

   Usage:
   pixtend <Module> <Pin> <Operation> <Optional>

       Module:      [V2L | V2S | DO | AO]
       Pin:         D0, ...
       Operation:   read |
                    write [<D-Value> | A-Value]
       D-Value:     on | off
       A-Value:     double

       Optional:    [MA]
       MA:          ModuleAddress for eIO Digtial/Analog One
 */

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <iostream>
#include <functional>

#include "OpcUaPiXtendServer/Tools/PiXtendToolConfig.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleV2S.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleV2L.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIOAO.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIODO.h"


using namespace OpcUaPiXtendServer;


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//
// Functions: tracing
//
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

void traceResultRead(const std::string& pin, std::string msg)
{
    std::cout << "READ " << pin << ": " << msg << std::endl;
}

void traceResultWrite(std::string& pin, std::string msg)
{
    std::cout << "WRITE " << pin << ": " << msg << std::endl;
}

void traceStatus(std::string msg)
{
    std::cout << "STATUS " << msg << std::endl;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//
// Functions: read pin
//
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

void handleReadResult(std::string& pin, double aValue)
{
    traceResultRead(pin, std::to_string(aValue));
}

void handleReadResult(std::string& pin, bool dValue)
{
    traceResultRead(pin, std::to_string(dValue));
}

bool handlePinRead(PiXtendToolModule::SPtr moduleSPtr,
        std::string& strPin, Pins pin)
{
    if (moduleSPtr == nullptr)
    {
        traceStatus("module is empty!");
        return false;
    }

    PiXtendToolReadStruct result;
    if (!moduleSPtr->readPin(pin, result))
    {
        traceStatus("unknown pin!");
        return false;
    }

    if (result.aValue.first)
    {
        handleReadResult(strPin, result.aValue.second);
    }
    else if (result.dValue.first)
    {
        handleReadResult(strPin, result.dValue.second);
    }
    else
    {
        traceStatus("cannot read/find pin!");
        return false;
    }
    return true;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//
// Functions: write pin
//
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

bool handlePinWrite(PiXtendToolModule::SPtr moduleSPtr,
        std::string& strPin, Pins pin,
        DValue& dValue, AValue& aValue)
{
    if (moduleSPtr == nullptr)
    {
        traceStatus("module is empty!");
        return false;
    }

    if (dValue.first)
    {
        if (!moduleSPtr->writeDigitalPin(pin, dValue))
        {
            traceStatus("unknown pin for dValue!");
            return false;
        }
    }
    else if (aValue.first)
    {
        if (!moduleSPtr->writeAnalogPin(pin, aValue))
        {
            traceStatus("unknown pin for aValue!");
            return false;
        }
    }
    else
    {
        traceStatus("undefined dValue/aValue");
        return false;
    }

    traceResultWrite(strPin, "successfully");
    return true;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//
// Functions: module and operation handling
//
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

bool handleModuleOperation(PiXtendToolModule::SPtr moduleSPtr,
        std::string& strPin, bool isOperationRead,
        DValue& dValue, AValue& aValue)
{
    Pins pin;
    if (!PiXtendToolConfig::mapInputPin(strPin, pin))
    {
        traceStatus("undefined pin!");
        return false;
    }

    if (isOperationRead)
    {
        return handlePinRead(moduleSPtr, strPin, pin);
    }
    else
    {
        return handlePinWrite(moduleSPtr, strPin, pin, dValue, aValue);
    }
}

bool handleModule(std::string& module, ModuleAddress& moduleAddress,
        std::string& strPin, bool isOperationRead,
        DValue& dValue, AValue& aValue)
{
    PiXtendToolModule::SPtr moduleSPtr = nullptr;

    if (module == piXtendModule_V2S)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleV2S>(module);
    }
    else if (module == piXtendModule_V2L)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleV2L>(module);
    }
    else if (module == piXtendModule_EIOAO)
    {
        if (!moduleAddress.first)
        {
            traceStatus("module is an eIO module and requires a moduleAddress!");
            return false;
        }

        moduleSPtr = boost::make_shared<PiXtendToolModuleEIOAO>(module, moduleAddress);
    }
    else if (module == piXtendModule_EIODO)
    {
        if (!moduleAddress.first)
        {
            traceStatus("module is an eIO module and requires a moduleAddress!");
            return false;
        }

        moduleSPtr = boost::make_shared<PiXtendToolModuleEIODO>(module, moduleAddress);
    }
    else
    {
        traceStatus("undefined module");
        return false;
    }

    return handleModuleOperation(moduleSPtr, strPin, isOperationRead, dValue, aValue);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//
// Function: main
//
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

int main(int argc, char** argv)
{
    // set command line options
    boost::program_options::options_description desc{std::string(argv[0])};
    desc.add_options()
        ("help,h", "produce help message")
        ("module,m", boost::program_options::value<std::string>()->required(), "name of the module [V2L | V2S | DO | AO]")
        ("pin,p", boost::program_options::value<std::string>()->required(), "name of the pin [D01 | ... | A01 | ...]")
        ("read,r", boost::program_options::bool_switch()->default_value(false), "operation read")
        ("write,w", boost::program_options::value<std::string>(), "operation write [D-Value [on | off] | A-Value [double]]")
        ("moduleAddress,a", boost::program_options::value<uint32_t>(), "moduleAddress for eIO modules [uInteger]");

    std::string module {""};
    std::string pin {""};
    bool isOperationRead = false;
    AValue aValue; // optional
    DValue dValue; // optional
    ModuleAddress moduleAddress; // optional

    // parse commend line options
    boost::program_options::variables_map vm;
    try
    {
        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc), vm
        );

        if (vm.count("help") || !vm.count("module") || !vm.count("pin"))
        {
            std::cout << desc << std::endl;
            return 1;
        }

        module = vm["module"].as<std::string>();
        boost::algorithm::to_lower(module);

        pin = vm["pin"].as<std::string>();
        boost::algorithm::to_lower(pin);

        isOperationRead = vm["read"].as<bool>();

        if (!vm.count("write") && !isOperationRead)
        {
            traceStatus("undefined operation [read | write]");
            std::cout << desc << std::endl;
            return 1;
        }

        if (vm.count("write") && !isOperationRead)
        {
            std::string writeValue = vm["write"].as<std::string>();
            boost::algorithm::to_lower(writeValue);

            bool parseDValue = false;
            if (PiXtendToolConfig::mapDValue(writeValue, parseDValue))
            {
                // is dValue
                dValue = {true, parseDValue};
            }
            else
            {
                // is aValue
                aValue = {true, boost::lexical_cast<double>(writeValue)};
            }
        }

        if (vm.count("moduleAddress"))
        {
            moduleAddress = { true, vm["moduleAddress"].as<uint32_t>() };
        }

        boost::program_options::notify(vm);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    if (!handleModule(module, moduleAddress, pin, isOperationRead, dValue, aValue))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    return 0;
}
