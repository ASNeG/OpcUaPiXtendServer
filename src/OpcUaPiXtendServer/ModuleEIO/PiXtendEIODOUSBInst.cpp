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

    PiXtendEIODOUSBInst::PiXtendEIODOUSBInst(
    	const std::string& instanceName,
		DeviceAccess::SPtr& deviceAccess
	)
    : PiXtendEIODO(instanceName)
    , deviceAccess_(deviceAccess)
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

    	// open access device
    	if (!deviceAccess_->open()) {
    		Log(Error, "open device error")
    			.parameter("Type", "EIODO")
				.parameter("InstanceName", instanceName());
    		return false;
    	}

        return true;
    }

    bool
    PiXtendEIODOUSBInst::shutdown(void)
    {
    	// close access device
    	// open access device
    	deviceAccess_->close();

        return true;
    }

    void
 	PiXtendEIODOUSBInst::handleHardwareAccess(void)
    {
    	int rc;

        // cycle time in <ms>
    	boost::this_thread::sleep(boost::posix_time::milliseconds(delayTime_));

    	// set slave id
    	if (!deviceAccess_->setSlave(moduleAddress_)) {
    		Log(Error, "set slave error")
    			.parameter("Type", "EIODO")
				.parameter("InstanceName", instanceName());
    		return;
    	}

    	// write digital output
    	if (!deviceAccess_->writeDigitalOut(8, outputDataDO_)) {
       		Log(Error, "write digital output error")
        		.parameter("Type", "EIODO")
    			.parameter("InstanceName", instanceName());
        	return;
    	}

    	// read digital outputs
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	if (!deviceAccess_->readDigitalOut(8, inputDataDO_)) {
           	Log(Error, "read digital output error")
            	.parameter("Type", "EIODO")
        		.parameter("InstanceName", instanceName());
            return;
        }

    	// read digital inputs
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	if (!deviceAccess_->readDigitalIn(8, inputDataDI_)) {
           	Log(Error, "read digital input error")
            	.parameter("Type", "EIODO")
        		.parameter("InstanceName", instanceName());
            return;
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
