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

#include "OpcUaPiXtendServer/PiXtend/PiXtendDigitalValueContext.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendDigitalValueContext::PiXtendDigitalValueContext(void)
    : PiXtendValueContext(ContextType::DigitalValue)
    {
    	dataValueIn(OpcUaDataValue((bool)false));
    	dataValueOut(OpcUaDataValue((bool)false));
    }

    PiXtendDigitalValueContext::~PiXtendDigitalValueContext(void)
    {
    }

    PiXtendDigitalValueContext::SPtr
	PiXtendDigitalValueContext::createContext(
    	ReadFunc readFunc,
		WriteFunc writeFunc,
		RegisterUpdateFunc registerUpdateFunc,
		DeregisterUpdateFunc deregisterUpdateFunc
    )
    {
    	auto context = boost::make_shared<PiXtendDigitalValueContext>();
    	context->readFunc(readFunc);
    	context->writeFunc(writeFunc);
    	context->registerUpdateFunc(registerUpdateFunc);
    	context->deregisterUpdateFunc(deregisterUpdateFunc);
    	context->writeAccess(writeFunc == nullptr ? false : true);
    	return context;
    }

    void
	PiXtendDigitalValueContext::dataValueToOutputStruct(void)
    {
    	bool value;
    	auto dataValue = dataValueOut();
    	dataValue.getValue(value);
    	writeFunc()(value);
    }

    void
	PiXtendDigitalValueContext::inputStructToDataValue(void)
    {
    	bool value = readFunc()();
    	bool oldValue;
    	auto oldDataValue = dataValueOut();
    	oldDataValue.getValue(oldValue);

    	OpcUaDataValue dataValue(value);

    	// check if value changed
    	if (value != oldValue) {
    		handleUpdateEvent(dataValue);
    	}

    	// set input value
    	dataValueIn(OpcUaDataValue(value));
    }

    void
	PiXtendDigitalValueContext::readFunc(ReadFunc readFunc)
    {
    	readFunc_ = readFunc;
    }

    PiXtendDigitalValueContext::ReadFunc
	PiXtendDigitalValueContext::readFunc(void)
    {
    	return readFunc_;
    }

    void
	PiXtendDigitalValueContext::writeFunc(WriteFunc writeFunc)
    {
    	writeFunc_ = writeFunc;
    }

    PiXtendDigitalValueContext::WriteFunc
	PiXtendDigitalValueContext::writeFunc(void)
    {
    	return writeFunc_;
    }

    void
	PiXtendDigitalValueContext::registerUpdateFunc(RegisterUpdateFunc registerUpdateFunc)
    {
    	registerUpdateFunc_ = registerUpdateFunc;
    }

    PiXtendDigitalValueContext::RegisterUpdateFunc
	PiXtendDigitalValueContext::registerUpdateFunc(void)
    {
    	return registerUpdateFunc_;
    }

    void
	PiXtendDigitalValueContext::deregisterUpdateFunc(DeregisterUpdateFunc deregisterUpdateFunc)
    {
    	deregisterUpdateFunc_ = deregisterUpdateFunc;
    }

    PiXtendDigitalValueContext::DeregisterUpdateFunc
	PiXtendDigitalValueContext::deregisterUpdateFunc(void)
    {
    	return deregisterUpdateFunc_;
    }

}
