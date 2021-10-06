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

#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleV2L.h"

namespace OpcUaPiXtendServer
{
    PiXtendToolModuleV2L::PiXtendToolModuleV2L(const std::string& name)
    : PiXtendToolModule()
    {
        pixtendSPtr_ = PiXtendModulesFactory::createPiXtendV2L(name);

        if (pixtendSPtr_ != nullptr)
        {
            pixtendSPtr_->startup();

            // read input data
            pixtendSPtr_->handleHardwareAccess();
        }
    }

    PiXtendToolModuleV2L::~PiXtendToolModuleV2L(void)
    {
        if (pixtendSPtr_ != nullptr)
        {
            // write output data
            pixtendSPtr_->handleHardwareAccess();

            pixtendSPtr_->shutdown();
            pixtendSPtr_.reset();
        }
    }

    bool
    PiXtendToolModuleV2L::readPin(Pins pin, PiXtendToolReadStruct& result)
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

            case Pins::Pin_AO0:
                result.aValue = {true, pixtendSPtr_->ao0()};
                break;
            case Pins::Pin_AO1:
                result.aValue = {true, pixtendSPtr_->ao1()};
                break;

            case Pins::Pin_DI0:
                result.dValue = {true, pixtendSPtr_->di0()};
                break;
            case Pins::Pin_DI1:
                result.dValue = {true, pixtendSPtr_->di1()};
                break;
            case Pins::Pin_DI2:
                result.dValue = {true, pixtendSPtr_->di2()};
                break;
            case Pins::Pin_DI3:
                result.dValue = {true, pixtendSPtr_->di3()};
                break;
            case Pins::Pin_DI4:
                result.dValue = {true, pixtendSPtr_->di4()};
                break;
            case Pins::Pin_DI5:
                result.dValue = {true, pixtendSPtr_->di5()};
                break;
            case Pins::Pin_DI6:
                result.dValue = {true, pixtendSPtr_->di6()};
                break;
            case Pins::Pin_DI7:
                result.dValue = {true, pixtendSPtr_->di7()};
                break;
            case Pins::Pin_DI8:
                result.dValue = {true, pixtendSPtr_->di8()};
                break;
            case Pins::Pin_DI9:
                result.dValue = {true, pixtendSPtr_->di9()};
                break;
            case Pins::Pin_DI10:
                result.dValue = {true, pixtendSPtr_->di10()};
                break;
            case Pins::Pin_DI11:
                result.dValue = {true, pixtendSPtr_->di11()};
                break;
            case Pins::Pin_DI12:
                result.dValue = {true, pixtendSPtr_->di12()};
                break;
            case Pins::Pin_DI13:
                result.dValue = {true, pixtendSPtr_->di13()};
                break;
            case Pins::Pin_DI14:
                result.dValue = {true, pixtendSPtr_->di14()};
                break;
            case Pins::Pin_DI15:
                result.dValue = {true, pixtendSPtr_->di15()};
                break;

            case Pins::Pin_DO0:
                result.dValue = {true, pixtendSPtr_->do0()};
                break;
            case Pins::Pin_DO1:
                result.dValue = {true, pixtendSPtr_->do1()};
                break;
            case Pins::Pin_DO2:
                result.dValue = {true, pixtendSPtr_->do2()};
                break;
            case Pins::Pin_DO3:
                result.dValue = {true, pixtendSPtr_->do3()};
                break;
            case Pins::Pin_DO4:
                result.dValue = {true, pixtendSPtr_->do4()};
                break;
            case Pins::Pin_DO5:
                result.dValue = {true, pixtendSPtr_->do5()};
                break;
            case Pins::Pin_DO6:
                result.dValue = {true, pixtendSPtr_->do6()};
                break;
            case Pins::Pin_DO7:
                result.dValue = {true, pixtendSPtr_->do7()};
                break;
            case Pins::Pin_DO8:
                result.dValue = {true, pixtendSPtr_->do8()};
                break;
            case Pins::Pin_DO9:
                result.dValue = {true, pixtendSPtr_->do9()};
                break;
            case Pins::Pin_DO10:
                result.dValue = {true, pixtendSPtr_->do10()};
                break;
            case Pins::Pin_DO11:
                result.dValue = {true, pixtendSPtr_->do11()};
                break;

            case Pins::Pin_Relay0:
                result.dValue = {true, pixtendSPtr_->relay0()};
                break;
            case Pins::Pin_Relay1:
                result.dValue = {true, pixtendSPtr_->relay1()};
                break;
            case Pins::Pin_Relay2:
                result.dValue = {true, pixtendSPtr_->relay2()};
                break;
            case Pins::Pin_Relay3:
                result.dValue = {true, pixtendSPtr_->relay3()};
                break;

            case Pins::Pin_GPIO0:
                result.dValue = {true, pixtendSPtr_->gpio0()};
                break;
            case Pins::Pin_GPIO1:
                result.dValue = {true, pixtendSPtr_->gpio1()};
                break;
            case Pins::Pin_GPIO2:
                result.dValue = {true, pixtendSPtr_->gpio2()};
                break;
            case Pins::Pin_GPIO3:
                result.dValue = {true, pixtendSPtr_->gpio3()};
                break;

            default:
                return false;
        }
        return true;
    }

    bool
    PiXtendToolModuleV2L::writeAnalogPin(Pins pin, AValue data)
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

            default:
                return false;
        }
        return true;
    }

    bool
    PiXtendToolModuleV2L::writeDigitalPin(Pins pin, DValue data)
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
            case Pins::Pin_DO0:
                 pixtendSPtr_->do0(data.second);
                 break;
             case Pins::Pin_DO1:
                 pixtendSPtr_->do1(data.second);
                 break;
             case Pins::Pin_DO2:
                 pixtendSPtr_->do2(data.second);
                 break;
             case Pins::Pin_DO3:
                 pixtendSPtr_->do3(data.second);
                 break;
             case Pins::Pin_DO4:
                 pixtendSPtr_->do4(data.second);
                 break;
             case Pins::Pin_DO5:
                 pixtendSPtr_->do5(data.second);
                 break;
             case Pins::Pin_DO6:
                 pixtendSPtr_->do6(data.second);
                 break;
             case Pins::Pin_DO7:
                 pixtendSPtr_->do7(data.second);
                 break;
             case Pins::Pin_DO8:
                 pixtendSPtr_->do8(data.second);
                 break;
             case Pins::Pin_DO9:
                 pixtendSPtr_->do9(data.second);
                 break;
             case Pins::Pin_DO10:
                 pixtendSPtr_->do10(data.second);
                 break;
             case Pins::Pin_DO11:
                 pixtendSPtr_->do11(data.second);
                 break;

             case Pins::Pin_Relay0:
                 pixtendSPtr_->relay0(data.second);
                 break;
             case Pins::Pin_Relay1:
                 pixtendSPtr_->relay1(data.second);
                 break;
             case Pins::Pin_Relay2:
                 pixtendSPtr_->relay2(data.second);
                 break;
             case Pins::Pin_Relay3:
                 pixtendSPtr_->relay3(data.second);
                 break;

             case Pins::Pin_GPIO0:
                 pixtendSPtr_->gpio0(data.second);
                 break;
             case Pins::Pin_GPIO1:
                 pixtendSPtr_->gpio1(data.second);
                 break;
             case Pins::Pin_GPIO2:
                 pixtendSPtr_->gpio2(data.second);
                 break;
             case Pins::Pin_GPIO3:
                 pixtendSPtr_->gpio3(data.second);
                 break;

            default:
                return false;
        }

        return true;
    }
}
