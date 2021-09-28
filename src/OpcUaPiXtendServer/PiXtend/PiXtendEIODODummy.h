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

#ifndef __OpcUaPiXtendServer_PiXtendEIODODummy_h__
#define __OpcUaPiXtendServer_PiXtendEIODODummy_h__

#include <unordered_map>

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODO.h"

namespace OpcUaPiXtendServer
{

    class PiXtendEIODODummy
    : public PiXtendEIODO
    {
      public:
        PiXtendEIODODummy(void);
        ~PiXtendEIODODummy(void);

        // Inputs Digital

        virtual bool di0(void) override;
        virtual bool di1(void) override;
        virtual bool di2(void) override;
        virtual bool di3(void) override;
        virtual bool di4(void) override;
        virtual bool di5(void) override;
        virtual bool di6(void) override;
        virtual bool di7(void) override;

        // Output Digital

        virtual void do0(bool data) override;
        virtual bool do0(void) override;
        virtual void do1(bool data) override;
        virtual bool do1(void) override;
        virtual void do2(bool data) override;
        virtual bool do2(void) override;
        virtual void do3(bool data) override;
        virtual bool do3(void) override;
        virtual void do4(bool data) override;
        virtual bool do4(void) override;
        virtual void do5(bool data) override;
        virtual bool do5(void) override;
        virtual void do6(bool data) override;
        virtual bool do6(void) override;
        virtual void do7(bool data) override;
        virtual bool do7(void) override;

      private:

        const bool defaultDigital_ = false;

        enum PinsEIODO: uint32_t
        {
            Pin_Undefined,
            Pin_DI0,
            Pin_DI1,
            Pin_DI2,
            Pin_DI3,
            Pin_DI4,
            Pin_DI5,
            Pin_DI6,
            Pin_DI7,
            Pin_DO0,
            Pin_DO1,
            Pin_DO2,
            Pin_DO3,
            Pin_DO4,
            Pin_DO5,
            Pin_DO6,
            Pin_DO7,
        };

        typedef std::unordered_map<PinsEIODO, bool> FlashDigitalPins;
        FlashDigitalPins flashDigitalPins_;

        void setDigitalPin(PinsEIODO pin, bool data);
        double getDigitalPin(PinsEIODO pin);
    };

}

#endif
