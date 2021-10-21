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

#include "OpcUaPiXtendServer/Factory/PiXtendModulesFactory.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIOAO.h"

namespace OpcUaPiXtendServer
{
    PiXtendToolModuleEIOAO::PiXtendToolModuleEIOAO(const std::string& name, ModuleAddress moduleAddress)
    : PiXtendToolModule()
    {
        pixtendSPtr_ = PiXtendModulesFactory::createPiXtendEIOAO(name);

        if (pixtendSPtr_ != nullptr && moduleAddress.first)
        {
            pixtendSPtr_->startup(moduleAddress.second);
        }
    }

    PiXtendToolModuleEIOAO::~PiXtendToolModuleEIOAO(void)
    {
        if (pixtendSPtr_ != nullptr)
        {
            pixtendSPtr_->shutdown();
            pixtendSPtr_.reset();
        }
    }

    bool
    PiXtendToolModuleEIOAO::readPin(Pins pin, PiXtendToolReadStruct& result)
    {
        if (pixtendSPtr_ == nullptr)
        {
            return false;
        }

        switch (pin)
        {
            case Pins::Pin_AI0:
                result.aValue = {true, pixtendSPtr_->ai0()};
                break;
            case Pins::Pin_AI1:
                result.aValue = {true, pixtendSPtr_->ai1()};
                break;
            case Pins::Pin_AI2:
                result.aValue = {true, pixtendSPtr_->ai2()};
                break;
            case Pins::Pin_AI3:
                result.aValue = {true, pixtendSPtr_->ai3()};
                break;
            case Pins::Pin_AI4:
                result.aValue = {true, pixtendSPtr_->ai4()};
                break;
            case Pins::Pin_AI5:
                result.aValue = {true, pixtendSPtr_->ai5()};
                break;
            case Pins::Pin_AI6:
                result.aValue = {true, pixtendSPtr_->ai6()};
                break;
            case Pins::Pin_AI7:
                result.aValue = {true, pixtendSPtr_->ai7()};
                break;

            case Pins::Pin_AO0:
                result.aValue = {true, pixtendSPtr_->ao0()};
                break;
            case Pins::Pin_AO1:
                result.aValue = {true, pixtendSPtr_->ao1()};
                break;
            case Pins::Pin_AO2:
                result.aValue = {true, pixtendSPtr_->ao2()};
                break;
            case Pins::Pin_AO3:
                result.aValue = {true, pixtendSPtr_->ao3()};
                break;
            case Pins::Pin_AO4:
                result.aValue = {true, pixtendSPtr_->ao4()};
                break;
            case Pins::Pin_AO5:
                result.aValue = {true, pixtendSPtr_->ao5()};
                break;

            default:
                return false;
        }
        return true;
    }

    bool
    PiXtendToolModuleEIOAO::writeAnalogPin(Pins pin, AValue data)
    {
        if (pixtendSPtr_ == nullptr)
        {
            return false;
        }

        if (!data.first)
        {
            // data is undefined
            return false;
        }

        switch (pin)
        {
            case Pins::Pin_AO0:
                pixtendSPtr_->ao0(data.second);
                break;
            case Pins::Pin_AO1:
                pixtendSPtr_->ao1(data.second);
                break;
            case Pins::Pin_AO2:
                 pixtendSPtr_->ao2(data.second);
                 break;
            case Pins::Pin_AO3:
                 pixtendSPtr_->ao3(data.second);
                 break;
            case Pins::Pin_AO4:
                 pixtendSPtr_->ao4(data.second);
                 break;
            case Pins::Pin_AO5:
                 pixtendSPtr_->ao5(data.second);
                 break;

            default:
                return false;
        }
        return true;
    }

    bool
    PiXtendToolModuleEIOAO::writeDigitalPin(Pins pin, DValue data)
    {
        // only analog pins available
        return false;
    }
}
