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

#ifndef __OpcUaPiXtendServer_PiXtendEIODOUSBInst_h__
#define __OpcUaPiXtendServer_PiXtendEIODOUSBInst_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaPiXtendServer/ModuleEIO/DeviceAccess.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODO.h"

namespace OpcUaPiXtendServer
{

    class PiXtendEIODOUSBInst
    : public PiXtendEIODO
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendEIODOUSBInst>;

        PiXtendEIODOUSBInst(
        	const std::string& instanceName,
			DeviceAccess::SPtr& deviceAccess
		);
        virtual ~PiXtendEIODOUSBInst(void);

        // Configuration

        virtual bool startup(uint32_t moduleAddress) override;
        virtual bool shutdown(void) override;
        virtual void handleHardwareAccess(void) override;

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
        DeviceAccess::SPtr deviceAccess_;

        std::string device_ = "/dev/ttyUSB0";
        int baud_ = 19200;
        char parity_ = 'E';
        int dataBit_ = 8;
        int stopBit_ = 1;
        modbus_t *ctx_ = nullptr;
        uint32_t moduleAddress_ = 0;

        uint32_t delayTime_ = 100;

        bool inputDataDI_[8] = { true, true, true, true, true, true, true, true };
        bool inputDataDO_[8] = { true, true, true, true, true, true, true, true };
        bool outputDataDO_[8] = { true, true, true, true, true, true, true, true };
    };

}

#endif
