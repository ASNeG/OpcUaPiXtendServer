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

#ifndef __OpcUaPiXtendServer_USBAccess_h__
#define __OpcUaPiXtendServer_USBAccess_h__

#include "modbus/modbus.h"

#include <boost/shared_ptr.hpp>

namespace OpcUaPiXtendServer
{

    class USBAccess
    {
      public:
        using SPtr = boost::shared_ptr<USBAccess>;

        USBAccess(void);
        virtual ~USBAccess(void);

        void device(const std::string& device);
        void baud(int baud);
        void parity(char parity);
        void dataBit(int dataBit);
        void stopBit(int stopBit);

        bool open(void);
        bool close(void);

        bool setSlave(uint32_t deviceAddress);

        bool writeDititalOut(uint8_t numberPins, bool* pins);
        bool readDigitalOut(uint8_t numberPins, bool* pins);
        bool readDigitalIn(uint8_t numberPins, bool* pins);

      private:
        std::string device_ = "/dev/ttyUSB0";
        int baud_ = 19200;
        char parity_ = 'E';
        int dataBit_ = 8;
        int stopBit_ = 1;
        modbus_t *ctx_ = nullptr;

        uint32_t deviceAddress_ = 0;
    };

}

#endif
