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

#include "OpcUaPiXtendServer/ModuleEIO/PiXtendEIODOUSBInst.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendEIODOUSBInst::PiXtendEIODOUSBInst(const std::string& instanceName)
    : PiXtendEIODO(instanceName)
    {
    }

    PiXtendEIODOUSBInst::~PiXtendEIODOUSBInst(void)
    {
    }

    // Configuration

    bool
    PiXtendEIODOUSBInst::startup(uint32_t moduleAddress)
    {
    	int rc;
    	moduleAddress_ = moduleAddress;

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
    PiXtendEIODOUSBInst::shutdown(void)
    {
    	// close usb device
    	if (ctx_ != nullptr) {
    		modbus_close(ctx_);
    	    modbus_free(ctx_);
    	    ctx_ = NULL;
    	}

    	Log(Info, "close usb device")
    		.parameter("Device", device_);
        return true;
    }

    void
 	PiXtendEIODOUSBInst::handleHardwareAccess(void)
    {
    	int rc;

        // cycle time in <ms>
    	boost::this_thread::sleep(boost::posix_time::milliseconds(delayTime_));

    	// set slave id
    	rc = modbus_set_slave(ctx_, moduleAddress_);
    	if (rc != 0) {
    		Log(Error, "set slave id error")
    			.parameter("ModuleAddress", moduleAddress_)
				.parameter("rc", rc);
    		return;
    	}

    	// write digital output
    	uint8_t bits[8] = {};
    	for (auto idx = 0; idx < 8; idx++) {
    		bits[idx] = outputDataDO_[idx] ? 0x01 : 0x00;
    	}
    	auto numBits = modbus_write_bits(ctx_, 0x00, 8, bits);
    	if (numBits != 8) {
    		Log(Error, "write output bits error")
    			.parameter("ModuleAddress", moduleAddress_)
				.parameter("NumBits", numBits);
    		return;
    	}

    	// read digital outputs
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	numBits = modbus_read_bits(ctx_, 0x00, 8, bits);
        if (numBits != 8) {
        	Log(Error, "read output bits error")
        		.parameter("ModuleAddress", moduleAddress_)
    			.parameter("NumBits", numBits);
        	return;
        }
    	for (auto idx = 0; idx < 8; idx++) {
    		inputDataDO_[idx] = bits[idx] == 0x01 ? true : false;
    	}

    	// read digital inputs
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	numBits = modbus_read_input_bits(ctx_, 0x00, 8, bits);
        if (numBits != 8) {
        	Log(Error, "read input bits error")
        		.parameter("ModuleAddress", moduleAddress_)
    			.parameter("NumBits", numBits);
        	return;
        }
    	for (auto idx = 0; idx < 8; idx++) {
    		inputDataDI_[idx] = bits[idx] == 0x01 ? true : false;
    	}
    }

    // Inputs Digital

    bool
    PiXtendEIODOUSBInst::di0(void)
    {
    	return inputDataDI_[0];
    }

    bool
    PiXtendEIODOUSBInst::di1(void)
    {
    	return inputDataDI_[1];
    }

    bool
    PiXtendEIODOUSBInst::di2(void)
    {
    	return inputDataDI_[2];
    }

    bool
    PiXtendEIODOUSBInst::di3(void)
    {
    	return inputDataDI_[3];
    }

    bool
    PiXtendEIODOUSBInst::di4(void)
    {
    	return inputDataDI_[4];
    }

    bool
    PiXtendEIODOUSBInst::di5(void)
    {
    	return inputDataDI_[5];
    }

    bool
    PiXtendEIODOUSBInst::di6(void)
    {
    	return inputDataDI_[6];
    }

    bool
    PiXtendEIODOUSBInst::di7(void)
    {
    	return inputDataDI_[7];
    }

    // Output Digital

    void
    PiXtendEIODOUSBInst::do0(bool data)
    {
    	outputDataDO_[0] = data;
    }

    bool
    PiXtendEIODOUSBInst::do0(void)
    {
        return inputDataDO_[0];
    }

    void
    PiXtendEIODOUSBInst::do1(bool data)
    {
    	outputDataDO_[1] = data;
    }

    bool
    PiXtendEIODOUSBInst::do1(void)
    {
        return inputDataDO_[1];
    }

    void
    PiXtendEIODOUSBInst::do2(bool data)
    {
    	outputDataDO_[2] = data;
    }

    bool
    PiXtendEIODOUSBInst::do2(void)
    {
    	return inputDataDO_[2];
    }

    void
    PiXtendEIODOUSBInst::do3(bool data)
    {
    	outputDataDO_[3] = data;
    }

    bool
    PiXtendEIODOUSBInst::do3(void)
    {
    	return inputDataDO_[3];
    }

    void
    PiXtendEIODOUSBInst::do4(bool data)
    {
    	outputDataDO_[4] = data;
    }

    bool
    PiXtendEIODOUSBInst::do4(void)
    {
    	return inputDataDO_[4];
    }

    void
    PiXtendEIODOUSBInst::do5(bool data)
    {
    	outputDataDO_[5] = data;
    }

    bool
    PiXtendEIODOUSBInst::do5(void)
    {
    	return inputDataDO_[5];
    }

    void
    PiXtendEIODOUSBInst::do6(bool data)
    {
    	outputDataDO_[6] = data;
    }

    bool
    PiXtendEIODOUSBInst::do6(void)
    {
    	return inputDataDO_[6];
    }

    void
    PiXtendEIODOUSBInst::do7(bool data)
    {
    	outputDataDO_[7] = data;
    }

    bool
    PiXtendEIODOUSBInst::do7(void)
    {
    	return inputDataDO_[7];
    }

}
