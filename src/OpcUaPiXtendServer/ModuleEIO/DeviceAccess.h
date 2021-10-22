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

#ifndef __OpcUaPiXtendServer_DeviceAccess_h__
#define __OpcUaPiXtendServer_DeviceAccess_h__

#include "modbus/modbus.h"

#include <boost/shared_ptr.hpp>

namespace OpcUaPiXtendServer
{

	enum class DeviceAccessType {
		USB,
		RS485
	};

    class DeviceAccess
    {
      public:
        using SPtr = boost::shared_ptr<DeviceAccess>;

        DeviceAccess(DeviceAccessType deviceAccessType) {
        	deviceAccessType_ = deviceAccessType;
        }
        virtual ~DeviceAccess(void) {}

        virtual bool open(void) = 0;
        virtual bool close(void) = 0;

        virtual bool setSlave(uint32_t deviceAddress) = 0;

        virtual bool writeDititalOut(uint8_t numberPins, bool* pins) = 0;
        virtual bool readDigitalOut(uint8_t numberPins, bool* pins) = 0;
        virtual bool readDigitalIn(uint8_t numberPins, bool* pins) = 0;

        DeviceAccessType deviceAccessType(void) {
        	return deviceAccessType_;
        }

      private:
        DeviceAccessType deviceAccessType_;
    };

}

#endif
