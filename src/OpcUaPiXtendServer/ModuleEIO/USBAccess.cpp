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

#include <OpcUaPiXtendServer/ModuleEIO/USBAccess.h>
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    USBAccess::USBAccess(void)
    : DeviceAccess(DeviceAccessType::USB)
    {
    }

    USBAccess::~USBAccess(void)
    {
    }

    void
	USBAccess::device(const std::string& device)
    {
    	device_ = device;
    	device_ = device;
    }

    void
	USBAccess::baud(int baud)
    {
    	baud_ = baud;
    }

    void
	USBAccess::parity(char parity)
    {
    	parity_ = parity;
    }

    void
	USBAccess::dataBit(int dataBit)
    {
    	dataBit_ = dataBit;
    }

    void
	USBAccess::stopBit(int stopBit)
    {
    	stopBit_ = stopBit;
    }

    bool
	USBAccess::open(void)
    {
    	int rc;

       	Log(Info, "open usb device")
        	.parameter("Device", device_);

    	// open usb device
    	ctx_ = modbus_new_rtu(device_.c_str(), baud_, parity_, dataBit_, stopBit_);
    	if (ctx_ == nullptr) {
    		Log(Error, "cannot create usb modbus device")
    			.parameter("Device", device_)
				.parameter("Baud", baud_)
				.parameter("Parity", parity_)
				.parameter("DataBit", dataBit_)
				.parameter("StopBit", stopBit_);
    		return false;
    	}

    	// set debug mode
    	//modbus_set_debug(ctx_, TRUE);

    	rc = modbus_connect(ctx_);
    	if (rc != 0) {
    		Log(Error, "cannot open usb modbus device")
    			.parameter("Device", device_)
				.parameter("Baud", baud_)
				.parameter("Parity", parity_)
				.parameter("DataBit", dataBit_)
				.parameter("StopBit", stopBit_);
    		return false;
    	}

        return true;
    }

    bool
	USBAccess::close(void)
    {
    	if (ctx_ != nullptr) {
    		modbus_close(ctx_);
    	    modbus_free(ctx_);
    	    ctx_ = NULL;
    	}

    	Log(Info, "close usb device")
    		.parameter("Device", device_);
        return true;
    }

    bool
	USBAccess::setSlave(uint32_t deviceAddress)
    {
    	int rc;

    	deviceAddress_ = deviceAddress;

    	// set slave id
    	rc = modbus_set_slave(ctx_, deviceAddress_);
    	if (rc != 0) {
    		Log(Error, "set slave id error")
				.parameter("Device", device_)
    			.parameter("DeviceAddress", deviceAddress_)
				.parameter("rc", rc);
    		return false;
    	}

    	return true;
    }

    bool
	USBAccess::writeDigitalOut(uint8_t numberPins, bool* pins)
    {
       	// write digital output
        uint8_t bits[numberPins] = {};
        for (auto idx = 0; idx < numberPins; idx++) {
        	bits[idx] = pins[idx] ? 0x01 : 0x00;
        }
        auto numBits = modbus_write_bits(ctx_, 0x00, numberPins, bits);
        if (numBits != numberPins) {
        	Log(Error, "write output bits error")
				.parameter("Device", device_)
        		.parameter("DeviceAddress", deviceAddress_)
    			.parameter("NumBits", numberPins);
        	return false;
        }

    	return true;
    }

    bool
	USBAccess::readDigitalOut(uint8_t numberPins, bool* pins)
    {
    	uint8_t bits[numberPins] = {};

       	auto numBits = modbus_read_bits(ctx_, 0x00, numberPins, bits);
        if (numBits != numberPins) {
        	Log(Error, "read output bits error")
				.parameter("Device", device_)
        		.parameter("DeviceAddress", deviceAddress_)
    			.parameter("NumBits", numberPins);
        	return false;
        }
    	for (auto idx = 0; idx < 8; idx++) {
    		pins[idx] = bits[idx] == 0x01 ? true : false;
    	}

    	return true;
    }

    bool
	USBAccess::readDigitalIn(uint8_t numberPins, bool* pins)
    {
    	uint8_t bits[numberPins] = {};

       	auto numBits = modbus_read_input_bits(ctx_, 0x00, numberPins, bits);
        if (numBits != numberPins) {
        	Log(Error, "read input bits error")
				.parameter("Device", device_)
        		.parameter("DeviceAddress", deviceAddress_)
    			.parameter("NumBits", numberPins);
        	return false;
        }
    	for (auto idx = 0; idx < 8; idx++) {
    		pins[idx] = bits[idx] == 0x01 ? true : false;
    	}

    	return true;
    }

    bool
	USBAccess::writeAnalogOut(uint8_t numberPins, uint16_t* pins)
    {
       	// write analog output
        auto numBits = modbus_write_registers(ctx_, 0x00, numberPins, pins);
        if (numBits != numberPins) {
        	Log(Error, "write output registers error")
				.parameter("Device", device_)
        		.parameter("DeviceAddress", deviceAddress_)
    			.parameter("NumBits", numberPins);
        	return false;
        }

    	return true;
    }

    bool
	USBAccess::readAnalogOut(uint8_t numberPins, uint16_t* pins)
    {
        auto numBits = modbus_read_registers(ctx_, 0x00, numberPins, pins);
        if (numBits != numberPins) {
            Log(Error, "read output registers error")
    			.parameter("Device", device_)
            	.parameter("DeviceAddress", deviceAddress_)
        		.parameter("NumBits", numberPins);
            return false;
        }

        return true;
    }

    bool
	USBAccess::readAnalogIn(uint8_t numberPins, uint16_t* pins)
    {
       	auto numBits = modbus_read_input_registers(ctx_, 0x00, numberPins, pins);
        if (numBits != numberPins) {
        	Log(Error, "read input registers error")
				.parameter("Device", device_)
        		.parameter("DeviceAddress", deviceAddress_)
    			.parameter("NumBits", numberPins);
        	return false;
        }

    	return true;
    }

}
