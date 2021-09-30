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

#include "OpcUaPiXtendServer/Tools/PiXtendToolModuleEIODO.h"

namespace OpcUaPiXtendServer
{
    PiXtendToolModuleEIODO::PiXtendToolModuleEIODO(ModuleAddress moduleAddress)
    : PiXtendToolModule()
    {
        pixtendSPtr_ = PiXtendModulesFactory::createPiXtendEIODO();

        if (pixtendSPtr_ != nullptr && moduleAddress.first)
        {
            pixtendSPtr_->startup(moduleAddress.second);
        }
    }

    PiXtendToolModuleEIODO::~PiXtendToolModuleEIODO(void)
    {
        if (pixtendSPtr_ != nullptr)
        {
            pixtendSPtr_->shutdown();
            pixtendSPtr_.reset();
        }
    }

    bool
    PiXtendToolModuleEIODO::readPin(Pins pin, PiXtendToolReadStruct& result)
    {
        if (pixtendSPtr_ == nullptr)
        {
            return false;
        }

        switch (pin)
        {
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

            default:
                return false;
        }
        return true;
    }

    bool
    PiXtendToolModuleEIODO::writeAnalogPin(Pins pin, AValue data)
    {
        // only digital pins available
        return true;
    }

    bool
    PiXtendToolModuleEIODO::writeDigitalPin(Pins pin, DValue data)
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

            default:
                return false;
        }
        return true;
    }
}
