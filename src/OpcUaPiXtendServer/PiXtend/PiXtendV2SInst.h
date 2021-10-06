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

#ifndef __OpcUaPiXtendServer_PiXtendV2SInst_h__
#define __OpcUaPiXtendServer_PiXtendV2SInst_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendSpiHelper.h"

namespace OpcUaPiXtendServer
{

    class PiXtendV2SInst
    : public PiXtendV2S
    {
      public:
    	using SPtr = boost::shared_ptr<PiXtendV2SInst>;

        PiXtendV2SInst(const std::string& instanceName);
        virtual ~PiXtendV2SInst(void);

        // Configuration

        virtual bool startup(void) override;
        virtual bool shutdown(void) override;
        virtual void handleHardwareAccess(void) override;

        // Inputs Analog

        virtual double ai0(void) override;
        virtual double ai1(void) override;

        // Output Analog

        virtual void ao0(double data) override;
        virtual double ao0(void) override;
        virtual void ao1(double data) override;
        virtual double ao1(void) override;

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

        // Relay

        virtual void relay0(bool data) override;
        virtual bool relay0(void) override;
        virtual void relay1(bool data) override;
        virtual bool relay1(void) override;
        virtual void relay2(bool data) override;
        virtual bool relay2(void) override;
        virtual void relay3(bool data) override;
        virtual bool relay3(void) override;

        // Input/Output General Purpose

        virtual void gpio0(bool data) override;
        virtual bool gpio0(void) override;
        virtual void gpio1(bool data) override;
        virtual bool gpio1(void) override;
        virtual void gpio2(bool data) override;
        virtual bool gpio2(void) override;
        virtual void gpio3(bool data) override;
        virtual bool gpio3(void) override;

      private:
        PiXtendSpiHelper spiHelper_;

        using PiXtendSpiInputData = pixtInV2S;
        using PiXtendSpiOutputData = pixtOutV2S;
        using PiXtendSpiOutputDataDac = pixtOutDAC;

        PiXtendSpiInputData spiInputData_;
        PiXtendSpiOutputData spiOutputData_;
        PiXtendSpiOutputDataDac spiOutputDataDac_;

        void resetSpiInputData(PiXtendSpiInputData& spiInputData);
        void resetSpiOutputData(PiXtendSpiOutputData& spiOutputData);
        void resetSpiOutputDataDac(PiXtendSpiOutputDataDac& spiOutputDataDac);
    };

}

#endif
