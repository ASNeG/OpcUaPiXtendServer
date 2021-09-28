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

#ifndef __OpcUaPiXtendServer_PiXtendEIOAODummy_h__
#define __OpcUaPiXtendServer_PiXtendEIOAODummy_h__

#include <unordered_map>

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAO.h"

namespace OpcUaPiXtendServer
{

    class PiXtendEIOAODummy
    : public PiXtendEIOAO
    {
      public:
        PiXtendEIOAODummy(void);
        ~PiXtendEIOAODummy(void);

        // Inputs Analog

        virtual double ai0(void) override;
        virtual double ai1(void) override;
        virtual double ai2(void) override;
        virtual double ai3(void) override;
        virtual double ai4(void) override;
        virtual double ai5(void) override;
        virtual double ai6(void) override;
        virtual double ai7(void) override;

        // Output Analog

        virtual void ao0(double data) override;
        virtual double ao0(void) override;
        virtual void ao1(double data) override;
        virtual double ao1(void) override;
        virtual void ao2(double data) override;
        virtual double ao2(void) override;
        virtual void ao3(double data) override;
        virtual double ao3(void) override;
        virtual void ao4(double data) override;
        virtual double ao4(void) override;
        virtual void ao5(double data) override;
        virtual double ao5(void) override;

      private:

        const double defaultAnalog_ = 0.0;

        enum PinsEIOAO: uint32_t
        {
            Pin_Undefined,
            Pin_AI0,
            Pin_AI1,
            Pin_AI2,
            Pin_AI3,
            Pin_AI4,
            Pin_AI5,
            Pin_AI6,
            Pin_AI7,
            Pin_AO0,
            Pin_AO1,
            Pin_AO2,
            Pin_AO3,
            Pin_AO4,
            Pin_AO5
        };

        typedef std::unordered_map<PinsEIOAO, double> FlashAnalogPins;
        FlashAnalogPins flashAnalogPins_;

        void setAnalogPin(PinsEIOAO pin, double data);
        double getAnalogPin(PinsEIOAO pin);
    };

}

#endif
