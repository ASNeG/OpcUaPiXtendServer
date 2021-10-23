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

#include "OpcUaPiXtendServer/ModuleEIO/PiXtendEIOAOInst.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendEIOAOInst::PiXtendEIOAOInst(
    	const std::string& instanceName,
		DeviceAccess::SPtr& deviceAccess
	)
    : PiXtendEIOAO(instanceName)
    , deviceAccess_(deviceAccess)
    {
    }

    PiXtendEIOAOInst::~PiXtendEIOAOInst(void)
    {
    }

    // Configuration

    bool
    PiXtendEIOAOInst::startup(uint32_t moduleAddress)
    {
    	int rc;
    	moduleAddress_ = moduleAddress;
        return true;
    }

    bool
    PiXtendEIOAOInst::shutdown(void)
    {
        return true;
    }

    void
 	PiXtendEIOAOInst::handleHardwareAccess(void)
    {
    	int rc;

        // cycle time in <ms>
    	boost::this_thread::sleep(boost::posix_time::milliseconds(delayTime_));

    	// set slave id
    	if (!deviceAccess_->setSlave(moduleAddress_)) {
    		Log(Error, "set slave error")
    			.parameter("Type", "EIOAO")
				.parameter("InstanceName", instanceName());
    		return;
    	}

    	// write analog output
    	uint16_t outputDataAO[6];
    	for (uint8_t idx = 0; idx < 6; idx++) {
    		outputDataAO[idx] = percent2Analog(outputDataAO_[idx], 12);
    	}
    	if (!deviceAccess_->writeAnalogOut(6, outputDataAO)) {
       		Log(Error, "write analog output error")
        		.parameter("Type", "EIOAO")
    			.parameter("InstanceName", instanceName());
        	return;
    	}

    	// read analog outputs
    	uint16_t inputDataAO[6];
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	if (!deviceAccess_->readAnalogOut(6, inputDataAO)) {
           	Log(Error, "read analog output error")
            	.parameter("Type", "EIOAO")
        		.parameter("InstanceName", instanceName());
            return;
        }
    	for (uint8_t idx = 0; idx < 6; idx++) {
    		inputDataAO_[idx] = analog2Percent(inputDataAO[idx], 12);
    	}

    	// read analog inputs
    	uint16_t inputDataAI[8];
    	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
       	if (!deviceAccess_->readAnalogIn(8, inputDataAI)) {
           	Log(Error, "read analog input error")
            	.parameter("Type", "EIOAO")
        		.parameter("InstanceName", instanceName());
            return;
        }
    	for (uint8_t idx = 0; idx < 8; idx++) {
    		inputDataAI_[idx] = analog2Percent(inputDataAI[idx]);
    	}

    }

    // Inputs Digital

    double
	PiXtendEIOAOInst::ai0(void)
    {
    	return inputDataAI_[0];
    }

    double
	PiXtendEIOAOInst::ai1(void)
    {
    	return inputDataAI_[1];
    }

    double
	PiXtendEIOAOInst::ai2(void)
    {
    	return inputDataAI_[2];
    }

    double
	PiXtendEIOAOInst::ai3(void)
    {
    	return inputDataAI_[3];
    }

    double
	PiXtendEIOAOInst::ai4(void)
    {
    	return inputDataAI_[4];
    }

    double
	PiXtendEIOAOInst::ai5(void)
    {
    	return inputDataAI_[5];
    }

    double
	PiXtendEIOAOInst::ai6(void)
    {
    	return inputDataAI_[6];
    }

    double
	PiXtendEIOAOInst::ai7(void)
    {
    	return inputDataAI_[7];
    }


    // Output Digital

    void
	PiXtendEIOAOInst::ao0(double data)
    {
    	outputDataAO_[0] = data;
    }

    double
	PiXtendEIOAOInst::ao0(void)
    {
    	return inputDataAO_[0];
    }

    void
	PiXtendEIOAOInst::ao1(double data)
    {
    	outputDataAO_[1] = data;
    }

    double
	PiXtendEIOAOInst::ao1(void)
    {
    	return inputDataAO_[1];
    }

    void
	PiXtendEIOAOInst::ao2(double data)
    {
    	outputDataAO_[2] = data;
    }

    double
	PiXtendEIOAOInst::ao2(void)
    {
    	return inputDataAO_[2];
    }

    void
	PiXtendEIOAOInst::ao3(double data)
    {
    	outputDataAO_[3] = data;
    }

    double
	PiXtendEIOAOInst::ao3(void)
    {
    	return inputDataAO_[3];
    }

    void
	PiXtendEIOAOInst::ao4(double data)
    {
    	outputDataAO_[4] = data;
    }

    double
	PiXtendEIOAOInst::ao4(void)
    {
    	return inputDataAO_[4];
    }

    void
	PiXtendEIOAOInst::ao5(double data)
    {
    	outputDataAO_[5] = data;
    }

    double
	PiXtendEIOAOInst::ao5(void)
    {
    	return inputDataAO_[5];
    }

}
