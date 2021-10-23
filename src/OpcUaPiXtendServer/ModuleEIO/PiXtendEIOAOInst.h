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

#ifndef __OpcUaPiXtendServer_PiXtendEIOAOInst_h__
#define __OpcUaPiXtendServer_PiXtendEIOAOInst_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaPiXtendServer/ModuleEIO/DeviceAccess.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAO.h"

namespace OpcUaPiXtendServer
{

    class PiXtendEIOAOInst
    : public PiXtendEIOAO
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendEIOAOInst>;

        PiXtendEIOAOInst(
        	const std::string& instanceName,
			DeviceAccess::SPtr& deviceAccess
		);
        virtual ~PiXtendEIOAOInst(void);

        // Configuration

        virtual bool startup(uint32_t moduleAddress) override;
        virtual bool shutdown(void) override;
        virtual void handleHardwareAccess(void) override;

        // Inputs Analog

        virtual double ai0(void) override;
        virtual double ai1(void) override;
        virtual double ai2(void) override;
        virtual double ai3(void) override;
        virtual double ai4(void) override;
        virtual double ai5(void) override;
        virtual double ai6(void) override;
        virtual double ai7(void) override;

        // Output Digital

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

      protected:
        DeviceAccess::SPtr deviceAccess_;

      private:
        uint32_t moduleAddress_ = 0;
        uint32_t delayTime_ = 100;

        double inputDataAI_[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        double inputDataAO_[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        double outputDataAO_[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    };

}

#endif
