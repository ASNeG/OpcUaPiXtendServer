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

#include <boost/make_shared.hpp>

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/ModuleEIO/DeviceAccessManager.h"
#include "OpcUaPiXtendServer/ModuleEIO/USBAccess.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    DeviceAccessManager::DeviceAccessManager(void)
    {
    }

    DeviceAccessManager::~DeviceAccessManager(void)
    {
    }

    DeviceAccess::SPtr
	DeviceAccessManager::createDeviceAccess(
     	const std::string& device,
     	uint32_t baud,
     	char parity,
     	uint8_t dataBit,
		uint8_t stopBit
	)
    {
    	// find device in device access map
    	auto it = deviceAccessMap_.find(device);
    	if (it != deviceAccessMap_.end()) {
    		// device already exist
    		auto deviceAccess = it->second;
    		deviceAccess->reference()++;
    		return deviceAccess;
    	}

    	// device access not exist - we create a new device access
    	auto deviceAccess = boost::make_shared<USBAccess>();
    	deviceAccess->device(device);
    	deviceAccess->baud(baud);
    	deviceAccess->parity(parity);
    	deviceAccess->dataBit(dataBit);
    	deviceAccess->stopBit(stopBit);

    	// open device
    	if (!deviceAccess->open()) {
    		Log(Error, "usb device open error")
    			.parameter("DeviceName", device);
    		return nullptr;
    	}

    	// add device to device map
    	deviceAccess->reference()++;
    	deviceAccessMap_.insert(std::make_pair(device, deviceAccess));
    	return deviceAccess;
    }

    void
	DeviceAccessManager::deleteDeviceAccess(void)
    {
    	for (auto it : deviceAccessMap_) {
    		auto deviceAccess = it.second;
    		deviceAccess->close();
    	}
    	deviceAccessMap_.clear();
    }

    void
	DeviceAccessManager::deleteDeviceAccess(
    	const std::string& device
    )
    {
    	// find device in device access map
    	auto it = deviceAccessMap_.find(device);
    	if (it == deviceAccessMap_.end()) {
    		// device not exist
    		return;
    	}
    	auto deviceAccess = it->second;

    	// check reference counter
    	deviceAccess->reference()--;
    	if (deviceAccess->reference() != 0) {
    		return;
    	}

    	// close device access
    	deviceAccess->close();

    	// delete device access
    	deviceAccessMap_.erase(it);
    }

}
