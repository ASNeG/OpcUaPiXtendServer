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

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAODummy.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIOAODummy::PiXtendEIOAODummy(void)
    {
    }

    PiXtendEIOAODummy::~PiXtendEIOAODummy(void)
    {
    }

    // Inputs Analog

    double
    PiXtendEIOAODummy::ai0(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI0);
    }

    double
    PiXtendEIOAODummy::ai1(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI1);
    }

    double
    PiXtendEIOAODummy::ai2(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI2);
    }

    double
    PiXtendEIOAODummy::ai3(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI3);
    }

    double
    PiXtendEIOAODummy::ai4(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI4);
    }

    double
    PiXtendEIOAODummy::ai5(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI5);
    }

    double
    PiXtendEIOAODummy::ai6(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI6);
    }

    double
    PiXtendEIOAODummy::ai7(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AI7);
    }

    // Output Analog

    void
    PiXtendEIOAODummy::ao0(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO0, data);
    }

    double
    PiXtendEIOAODummy::ao0(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO0);
    }

    void
    PiXtendEIOAODummy::ao1(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO1, data);
    }

    double
    PiXtendEIOAODummy::ao1(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO1);
    }

    void
    PiXtendEIOAODummy::ao2(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO2, data);
    }

    double
    PiXtendEIOAODummy::ao2(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO2);
    }

    void
    PiXtendEIOAODummy::ao3(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO3, data);
    }

    double
    PiXtendEIOAODummy::ao3(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO3);
    }

    void
    PiXtendEIOAODummy::ao4(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO4, data);
    }

    double
    PiXtendEIOAODummy::ao4(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO4);
    }

    void
    PiXtendEIOAODummy::ao5(double data)
    {
        setAnalogPin(PinsEIOAO::Pin_AO5, data);
    }

    double
    PiXtendEIOAODummy::ao5(void)
    {
        return getAnalogPin(PinsEIOAO::Pin_AO5);
    }

    // Helper functions

    void
    PiXtendEIOAODummy::setAnalogPin(PinsEIOAO pin, double data)
    {
        flashAnalogPins_[pin] = data;
    }

    double
    PiXtendEIOAODummy::getAnalogPin(PinsEIOAO pin)
    {
        FlashAnalogPins::const_iterator data = flashAnalogPins_.find(pin);
        if (data != flashAnalogPins_.end())
        {
            return data->second;
        }
        return defaultAnalog_;
    }

}
