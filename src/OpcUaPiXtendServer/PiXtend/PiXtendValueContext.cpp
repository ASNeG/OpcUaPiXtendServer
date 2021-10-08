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

#include "OpcUaPiXtendServer/PiXtend/PiXtendValueContext.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendValueContext::PiXtendValueContext(PiXtendValueContext::ContextType contextType)
    : BaseClass()
    , contextType_(contextType)
    {
    }

    PiXtendValueContext::~PiXtendValueContext(void)
    {
    }

    PiXtendValueContext::ContextType
	PiXtendValueContext::contextType(void)
    {
    	return contextType_;
    }

    void
	PiXtendValueContext::dataValueIn(const OpcUaDataValue& dataValue)
    {
    	// set data value
    	valueMutex_.lock();
    	inputDataValue_ = dataValue;
    	valueMutex_.unlock();
    }

    void
	PiXtendValueContext::dataValueOut(const OpcUaDataValue& dataValue)
    {
    	// set data value
    	valueMutex_.lock();
    	outputDataValue_ = dataValue;
    	valueMutex_.unlock();
    }

    OpcUaStackCore::OpcUaDataValue
	PiXtendValueContext::dataValueIn(void)
    {
    	OpcUaDataValue dataValue;

    	// get data value
    	valueMutex_.lock();
    	dataValue = inputDataValue_;
    	valueMutex_.unlock();

    	return dataValue;
    }

    OpcUaStackCore::OpcUaDataValue
	PiXtendValueContext::dataValueOut(void)
    {
    	OpcUaDataValue dataValue;

    	// get data value
    	valueMutex_.lock();
    	dataValue = outputDataValue_;
    	valueMutex_.unlock();

    	return dataValue;
    }

    bool
	PiXtendValueContext::writeAccess(void)
    {
    	return writeAccess_;
    }

    void
	PiXtendValueContext::writeAccess(bool writeAccess)
    {
    	writeAccess_ = writeAccess;
    }

    bool
	PiXtendValueContext::addMonitoredItem(
    	OpcUaNodeId& id,
		UpdateElement::UpdateFunc updateFunc,
		OpcUaStackCore::BaseClass::SPtr& context
	)
    {
    	return updateContext_.addContext(
    		id, updateFunc, context
    	);
    }

    void
	PiXtendValueContext::handleUpdateEvent(OpcUaStackCore::OpcUaDataValue& dataValue)
    {
    	updateContext_.callEvents(dataValue);
    }

    bool
	PiXtendValueContext::delMonitoredItem(
    	OpcUaNodeId& id
    )
    {
    	return updateContext_.delContext(id);;
    }

}
