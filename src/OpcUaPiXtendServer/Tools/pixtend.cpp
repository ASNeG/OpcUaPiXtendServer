
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
   pixtend <Module> <Pin> <Operation>

       Module:      [V2L | V2S | DO | AO]
       Pin:         D0, ...
       Operation:   read |
                    write [<D-Value> | A-Value]
       D-Value:     on | off
       A-Value:     double

 */

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <iostream>
#include <functional>

#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolConfig.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleV2S.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleV2L.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIOAO.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIODO.h"

using namespace OpcUaPiXtendServer;

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

void readPin(std::string& pin, double aValue)
{
    traceResultRead(pin, std::to_string(aValue));
}

void readPin(std::string& pin, bool dValue)
{
    traceResultRead(pin, std::to_string(dValue));
}

bool handleModule(PiXtendToolModule::SPtr moduleSPtr,
        std::string& strPin, std::string& operation,
        DValue& dValue, AValue& aValue)
{
    if (moduleSPtr == nullptr)
    {
        traceStatus("module is empty!");
        return false;
    }

    Pins pin;
    if (!PiXtendToolConfig::mapInputPin(strPin, pin))
    {
        traceStatus("undefined pin!");
        return false;
    }

    if (operation == operationRead)
    {
        PiXtendToolReadStruct result;
        if (!moduleSPtr->readPin(pin, result))
        {
            traceStatus("unknown pin!");
            return false;
        }

        if (result.aValue.first)
        {
            readPin(strPin, result.aValue.second);
        }
        else if (result.dValue.first)
        {
            readPin(strPin, result.dValue.second);
        }
        else
        {
            traceStatus("cannot read/find pin!");
            return false;
        }
        return true;
    }
    else if (operation == operationWrite)
    {
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

    traceStatus("undefined operation");
    return false;
}

int main(int argc, char** argv)
{
    // set command line options
    boost::program_options::options_description desc{std::string(argv[0])};
    desc.add_options()
        ("help,h", "produce help message")
        ("module,m", boost::program_options::value<std::string>()->required(), "name of the module [V2L | V2S | DO | AO]")
        ("pin,p", boost::program_options::value<std::string>()->required(), "name of the pin [D01 | ... | A01 | ...]")
        ("operation,o", boost::program_options::value<std::string>()->required(), "[read | write [D-Value | A-Value]]")
        ("d-value,d", boost::program_options::value<std::string>(), "D-Value [on | off]")
        ("a-value,a", boost::program_options::value<double>(), "A-Value [double]");

    std::string module {""};
    std::string pin {""};
    std::string operation {""};
    AValue aValue;
    DValue dValue;

    // parse commend line options
    boost::program_options::variables_map vm;
    try
    {
        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc), vm
        );

        if (vm.count("help") || !vm.count("module") ||
            !vm.count("pin") || !vm.count("operation"))
        {
            std::cout << desc << std::endl;
            return 1;
        }

        module = vm["module"].as<std::string>();
        pin = vm["pin"].as<std::string>();
        operation = vm["operation"].as<std::string>();

        boost::algorithm::to_lower(module);
        boost::algorithm::to_lower(pin);
        boost::algorithm::to_lower(operation);

        if (operation == operationWrite)
        {
            if (vm.count("d-value"))
            {
                std::string strDValue = vm["d-value"].as<std::string>();
                boost::algorithm::to_lower(strDValue);

                bool parseDValue;
                if (!PiXtendToolConfig::mapDValue(strDValue, parseDValue))
                {
                    traceStatus("undefined DValue!");
                    std::cout << desc << std::endl;
                    return 1;
                }

                dValue = { true, parseDValue };
            }
            else if (vm.count("a-value"))
            {
                aValue = { true, vm["a-value"].as<double>() };
            }
            else
            {
                std::cout << desc << std::endl;
                return 1;
            }
        }

        boost::program_options::notify(vm);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    PiXtendToolModule::SPtr moduleSPtr = nullptr;
    if (module == piXtendModule_V2S)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleV2S>();
    }
    else if (module == piXtendModule_V2L)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleV2L>();
    }
    else if (module == piXtendModule_EIOAO)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleEIOAO>();
    }
    else if (module == piXtendModule_EIODO)
    {
        moduleSPtr = boost::make_shared<PiXtendToolModuleEIODO>();
    }
    else
    {
        traceStatus("undefined module");
        std::cout << desc << std::endl;
        return 1;
    }

    if (!handleModule(moduleSPtr, pin, operation, dValue, aValue))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    return 0;
}
