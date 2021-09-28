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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2SDummy.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2SDummy::PiXtendV2SDummy(void)
    {
    }

    PiXtendV2SDummy::~PiXtendV2SDummy(void)
    {
    }

    // Inputs Analog

    double
    PiXtendV2SDummy::ai0(void)
    {
        return getAnalogPin(PinsV2S::Pin_AI0);
    }

    double
    PiXtendV2SDummy::ai1(void)
    {
        return getAnalogPin(PinsV2S::Pin_AI1);
    }

    // Output Analog

    void
    PiXtendV2SDummy::ao0(double data)
    {
        setAnalogPin(PinsV2S::Pin_AO0, data);
    }

    double
    PiXtendV2SDummy::ao0(void)
    {
        return getAnalogPin(PinsV2S::Pin_AO0);
    }

    void
    PiXtendV2SDummy::ao1(double data)
    {
        setAnalogPin(PinsV2S::Pin_AO1, data);
    }

    double
    PiXtendV2SDummy::ao1(void)
    {
        return getAnalogPin(PinsV2S::Pin_AO1);
    }

    // Inputs Digital

    bool
    PiXtendV2SDummy::di0(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI0);
    }

    bool
    PiXtendV2SDummy::di1(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI1);
    }

    bool
    PiXtendV2SDummy::di2(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI2);
    }

    bool
    PiXtendV2SDummy::di3(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI3);
    }

    bool
    PiXtendV2SDummy::di4(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI4);
    }

    bool
    PiXtendV2SDummy::di5(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI5);
    }

    bool
    PiXtendV2SDummy::di6(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI6);
    }

    bool
    PiXtendV2SDummy::di7(void)
    {
        return getDigitalPin(PinsV2S::Pin_DI7);
    }

    // Output Digital

    void
    PiXtendV2SDummy::do0(bool data)
    {
        setDigitalPin(PinsV2S::Pin_DO0, data);
    }

    bool
    PiXtendV2SDummy::do0(void)
    {
        return getDigitalPin(PinsV2S::Pin_DO0);
    }

    void
    PiXtendV2SDummy::do1(bool data)
    {
        setDigitalPin(PinsV2S::Pin_DO1, data);
    }

    bool
    PiXtendV2SDummy::do1(void)
    {
        return getDigitalPin(PinsV2S::Pin_DO1);
    }

    void
    PiXtendV2SDummy::do2(bool data)
    {
        setDigitalPin(PinsV2S::Pin_DO2, data);
    }

    bool
    PiXtendV2SDummy::do2(void)
    {
        return getDigitalPin(PinsV2S::Pin_DO2);
    }

    void
    PiXtendV2SDummy::do3(bool data)
    {
        setDigitalPin(PinsV2S::Pin_DO3, data);
    }

    bool
    PiXtendV2SDummy::do3(void)
    {
        return getDigitalPin(PinsV2S::Pin_DO3);
    }

    // Relay

    void
    PiXtendV2SDummy::relay0(bool data)
    {
        setDigitalPin(PinsV2S::Pin_Relay0, data);
    }

    bool
    PiXtendV2SDummy::relay0(void)
    {
        return getDigitalPin(PinsV2S::Pin_Relay0);
    }

    void
    PiXtendV2SDummy::relay1(bool data)
    {
        setDigitalPin(PinsV2S::Pin_Relay1, data);
    }

    bool
    PiXtendV2SDummy::relay1(void)
    {
        return getDigitalPin(PinsV2S::Pin_Relay1);
    }

    void
    PiXtendV2SDummy::relay2(bool data)
    {
        setDigitalPin(PinsV2S::Pin_Relay2, data);
    }

    bool
    PiXtendV2SDummy::relay2(void)
    {
        return getDigitalPin(PinsV2S::Pin_Relay2);
    }

    void
    PiXtendV2SDummy::relay3(bool data)
    {
        setDigitalPin(PinsV2S::Pin_Relay3, data);
    }

    bool
    PiXtendV2SDummy::relay3(void)
    {
        return getDigitalPin(PinsV2S::Pin_Relay3);
    }

    // Input/Output General Purpose

    void
    PiXtendV2SDummy::gpio0(bool data)
    {
        setDigitalPin(PinsV2S::Pin_GPIO0, data);
    }

    bool
    PiXtendV2SDummy::gpio0(void)
    {
        return getDigitalPin(PinsV2S::Pin_GPIO0);
    }

    void
    PiXtendV2SDummy::gpio1(bool data)
    {
        setDigitalPin(PinsV2S::Pin_GPIO1, data);
    }

    bool
    PiXtendV2SDummy::gpio1(void)
    {
        return getDigitalPin(PinsV2S::Pin_GPIO1);
    }

    void
    PiXtendV2SDummy::gpio2(bool data)
    {
        setDigitalPin(PinsV2S::Pin_GPIO2, data);
    }

    bool
    PiXtendV2SDummy::gpio2(void)
    {
        return getDigitalPin(PinsV2S::Pin_GPIO2);
    }

    void
    PiXtendV2SDummy::gpio3(bool data)
    {
        setDigitalPin(PinsV2S::Pin_GPIO3, data);
    }

    bool
    PiXtendV2SDummy::gpio3(void)
    {
        return getDigitalPin(PinsV2S::Pin_GPIO3);
    }

    // Helper functions

    void
    PiXtendV2SDummy::setAnalogPin(PinsV2S pin, double data)
    {
        flashAnalogPins_[pin] = data;
    }

    double
    PiXtendV2SDummy::getAnalogPin(PinsV2S pin)
    {
        FlashAnalogPins::const_iterator data = flashAnalogPins_.find(pin);
        if (data != flashAnalogPins_.end())
        {
            return data->second;
        }
        return defaultAnalog_;
    }

    void
    PiXtendV2SDummy::setDigitalPin(PinsV2S pin, bool data)
    {
        flashDigitalPins_[pin] = data;
    }

    double
    PiXtendV2SDummy::getDigitalPin(PinsV2S pin)
    {
        FlashDigitalPins::const_iterator data = flashDigitalPins_.find(pin);
        if (data != flashDigitalPins_.end())
        {
            return data->second;
        }
        return defaultDigital_;
    }

}
