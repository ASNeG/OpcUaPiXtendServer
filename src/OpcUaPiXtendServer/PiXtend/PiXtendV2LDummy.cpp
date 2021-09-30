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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2LDummy.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2LDummy::PiXtendV2LDummy(void)
    : PiXtendV2L()
    {
    }

    PiXtendV2LDummy::~PiXtendV2LDummy(void)
    {
    }

    // Configuration

    bool
    PiXtendV2LDummy::startup(void)
    {
        return true;
    }

    bool
    PiXtendV2LDummy::shutdown(void)
    {
        return true;
    }

    // Inputs Analog

    double
    PiXtendV2LDummy::ai0(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI0);
    }

    double
    PiXtendV2LDummy::ai1(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI1);
    }

    double
    PiXtendV2LDummy::ai2(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI2);
    }

    double
    PiXtendV2LDummy::ai3(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI3);
    }

    double
    PiXtendV2LDummy::ai4(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI4);
    }

    double
    PiXtendV2LDummy::ai5(void)
    {
        return getAnalogPin(PinsV2L::Pin_AI5);
    }

    // Output Analog

    void
    PiXtendV2LDummy::ao0(double data)
    {
        setAnalogPin(PinsV2L::Pin_AO0, data);
    }

    double
    PiXtendV2LDummy::ao0(void)
    {
        return getAnalogPin(PinsV2L::Pin_AO0);
    }

    void
    PiXtendV2LDummy::ao1(double data)
    {
        setAnalogPin(PinsV2L::Pin_AO1, data);
    }

    double
    PiXtendV2LDummy::ao1(void)
    {
        return getAnalogPin(PinsV2L::Pin_AO1);
    }

    // Inputs Digital

    bool
    PiXtendV2LDummy::di0(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI0);
    }

    bool
    PiXtendV2LDummy::di1(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI1);
    }

    bool
    PiXtendV2LDummy::di2(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI2);
    }

    bool
    PiXtendV2LDummy::di3(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI3);
    }

    bool
    PiXtendV2LDummy::di4(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI4);
    }

    bool
    PiXtendV2LDummy::di5(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI5);
    }

    bool
    PiXtendV2LDummy::di6(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI6);
    }

    bool
    PiXtendV2LDummy::di7(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI7);
    }

    bool
    PiXtendV2LDummy::di8(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI8);
    }

    bool
    PiXtendV2LDummy::di9(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI9);
    }

    bool
    PiXtendV2LDummy::di10(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI10);
    }

    bool
    PiXtendV2LDummy::di11(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI11);
    }

    bool
    PiXtendV2LDummy::di12(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI12);
    }

    bool
    PiXtendV2LDummy::di13(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI13);
    }

    bool
    PiXtendV2LDummy::di14(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI14);
    }

    bool
    PiXtendV2LDummy::di15(void)
    {
        return getDigitalPin(PinsV2L::Pin_DI15);
    }

    // Output Digital

    void
    PiXtendV2LDummy::do0(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO0, data);
    }

    bool
    PiXtendV2LDummy::do0(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO0);
    }

    void
    PiXtendV2LDummy::do1(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO1, data);
    }

    bool
    PiXtendV2LDummy::do1(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO1);
    }

    void
    PiXtendV2LDummy::do2(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO2, data);
    }

    bool
    PiXtendV2LDummy::do2(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO2);
    }

    void
    PiXtendV2LDummy::do3(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO3, data);
    }

    bool
    PiXtendV2LDummy::do3(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO3);
    }

    void
    PiXtendV2LDummy::do4(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO4, data);
    }

    bool
    PiXtendV2LDummy::do4(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO4);
    }

    void
    PiXtendV2LDummy::do5(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO5, data);
    }

    bool
    PiXtendV2LDummy::do5(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO5);
    }

    void
    PiXtendV2LDummy::do6(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO6, data);
    }

    bool
    PiXtendV2LDummy::do6(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO6);
    }

    void
    PiXtendV2LDummy::do7(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO7, data);
    }

    bool
    PiXtendV2LDummy::do7(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO7);
    }

    void
    PiXtendV2LDummy::do8(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO8, data);
    }

    bool
    PiXtendV2LDummy::do8(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO8);
    }

    void
    PiXtendV2LDummy::do9(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO9, data);
    }

    bool
    PiXtendV2LDummy::do9(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO9);
    }

    void
    PiXtendV2LDummy::do10(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO10, data);
    }

    bool
    PiXtendV2LDummy::do10(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO10);
    }

    void
    PiXtendV2LDummy::do11(bool data)
    {
        setDigitalPin(PinsV2L::Pin_DO11, data);
    }

    bool
    PiXtendV2LDummy::do11(void)
    {
        return getDigitalPin(PinsV2L::Pin_DO11);
    }

    // Relay

    void
    PiXtendV2LDummy::relay0(bool data)
    {
        setDigitalPin(PinsV2L::Pin_Relay0, data);
    }

    bool
    PiXtendV2LDummy::relay0(void)
    {
        return getDigitalPin(PinsV2L::Pin_Relay0);
    }

    void
    PiXtendV2LDummy::relay1(bool data)
    {
        setDigitalPin(PinsV2L::Pin_Relay1, data);
    }

    bool
    PiXtendV2LDummy::relay1(void)
    {
        return getDigitalPin(PinsV2L::Pin_Relay1);
    }

    void
    PiXtendV2LDummy::relay2(bool data)
    {
        setDigitalPin(PinsV2L::Pin_Relay2, data);
    }

    bool
    PiXtendV2LDummy::relay2(void)
    {
        return getDigitalPin(PinsV2L::Pin_Relay2);
    }

    void
    PiXtendV2LDummy::relay3(bool data)
    {
        setDigitalPin(PinsV2L::Pin_Relay3, data);
    }

    bool
    PiXtendV2LDummy::relay3(void)
    {
        return getDigitalPin(PinsV2L::Pin_Relay3);
    }

    // Input/Output General Purpose

    void
    PiXtendV2LDummy::gpio0(bool data)
    {
        setDigitalPin(PinsV2L::Pin_GPIO0, data);
    }

    bool
    PiXtendV2LDummy::gpio0(void)
    {
        return getDigitalPin(PinsV2L::Pin_GPIO0);
    }

    void
    PiXtendV2LDummy::gpio1(bool data)
    {
        setDigitalPin(PinsV2L::Pin_GPIO1, data);
    }

    bool
    PiXtendV2LDummy::gpio1(void)
    {
        return getDigitalPin(PinsV2L::Pin_GPIO1);
    }

    void
    PiXtendV2LDummy::gpio2(bool data)
    {
        setDigitalPin(PinsV2L::Pin_GPIO2, data);
    }

    bool
    PiXtendV2LDummy::gpio2(void)
    {
        return getDigitalPin(PinsV2L::Pin_GPIO2);
    }

    void
    PiXtendV2LDummy::gpio3(bool data)
    {
        setDigitalPin(PinsV2L::Pin_GPIO3, data);
    }

    bool
    PiXtendV2LDummy::gpio3(void)
    {
        return getDigitalPin(PinsV2L::Pin_GPIO3);
    }

    // Helper functions

    void
    PiXtendV2LDummy::setAnalogPin(PinsV2L pin, double data)
    {
        flashAnalogPins_[pin] = data;
    }

    double
    PiXtendV2LDummy::getAnalogPin(PinsV2L pin)
    {
        auto data = flashAnalogPins_.find(pin);
        if (data != flashAnalogPins_.end())
        {
            return data->second;
        }
        return defaultAnalog_;
    }

    void
    PiXtendV2LDummy::setDigitalPin(PinsV2L pin, bool data)
    {
        flashDigitalPins_[pin] = data;
    }

    double
    PiXtendV2LDummy::getDigitalPin(PinsV2L pin)
    {
        auto data = flashDigitalPins_.find(pin);
        if (data != flashDigitalPins_.end())
        {
            return data->second;
        }
        return defaultDigital_;
    }

}
