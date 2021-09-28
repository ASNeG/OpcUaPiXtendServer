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

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODODummy.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIODODummy::PiXtendEIODODummy(void)
    {
    }

    PiXtendEIODODummy::~PiXtendEIODODummy(void)
    {
    }

    // Inputs Digital

    bool
    PiXtendEIODODummy::di0(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI0);
    }

    bool
    PiXtendEIODODummy::di1(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI1);
    }

    bool
    PiXtendEIODODummy::di2(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI2);
    }

    bool
    PiXtendEIODODummy::di3(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI3);
    }

    bool
    PiXtendEIODODummy::di4(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI4);
    }

    bool
    PiXtendEIODODummy::di5(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI5);
    }

    bool
    PiXtendEIODODummy::di6(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI6);
    }

    bool
    PiXtendEIODODummy::di7(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DI7);
    }

    // Output Digital

    void
    PiXtendEIODODummy::do0(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO0, data);
    }

    bool
    PiXtendEIODODummy::do0(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO0);
    }

    void
    PiXtendEIODODummy::do1(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO1, data);
    }

    bool
    PiXtendEIODODummy::do1(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO1);
    }

    void
    PiXtendEIODODummy::do2(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO2, data);
    }

    bool
    PiXtendEIODODummy::do2(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO2);
    }

    void
    PiXtendEIODODummy::do3(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO3, data);
    }

    bool
    PiXtendEIODODummy::do3(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO3);
    }

    void
    PiXtendEIODODummy::do4(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO4, data);
    }

    bool
    PiXtendEIODODummy::do4(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO4);
    }

    void
    PiXtendEIODODummy::do5(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO5, data);
    }

    bool
    PiXtendEIODODummy::do5(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO5);
    }

    void
    PiXtendEIODODummy::do6(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO6, data);
    }

    bool
    PiXtendEIODODummy::do6(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO6);
    }

    void
    PiXtendEIODODummy::do7(bool data)
    {
        setDigitalPin(PinsEIODO::Pin_DO7, data);
    }

    bool
    PiXtendEIODODummy::do7(void)
    {
        return getDigitalPin(PinsEIODO::Pin_DO7);
    }

    // Helper functions

    void
    PiXtendEIODODummy::setDigitalPin(PinsEIODO pin, bool data)
    {
        flashDigitalPins_[pin] = data;
    }

    double
    PiXtendEIODODummy::getDigitalPin(PinsEIODO pin)
    {
        FlashDigitalPins::const_iterator data = flashDigitalPins_.find(pin);
        if (data != flashDigitalPins_.end())
        {
            return data->second;
        }
        return defaultDigital_;
    }

}
