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

#include "OpcUaPiXtendServer/PiXtend/PiXtendAnalogValueContext.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendAnalogValueContext::PiXtendAnalogValueContext(void)
    : PiXtendValueContext(ContextType::AnalogValue)
    {
    	dataValueIn(OpcUaDataValue((double)0.0));
    	dataValueOut(OpcUaDataValue((double)0.0));
    }

    PiXtendAnalogValueContext::~PiXtendAnalogValueContext(void)
    {
    }

    PiXtendAnalogValueContext::SPtr
	PiXtendAnalogValueContext::createContext(
     	ReadFunc readFunc,
 		WriteFunc writeFunc
    )
    {
     	auto context = boost::make_shared<PiXtendAnalogValueContext>();
     	context->readFunc(readFunc);
     	context->writeFunc(writeFunc);
     	context->writeAccess(writeFunc == nullptr ? false : true);
     	return context;
    }

    void
	PiXtendAnalogValueContext::dataValueToOutputStruct(void)
    {
    	double value;
    	auto dataValue = dataValueOut();
    	dataValue.getValue(value);
    	writeFunc()(value);
    }

    void
	PiXtendAnalogValueContext::inputStructToDataValue(void)
    {
    	double value = readFunc()();
    	double oldValue;
    	auto oldDataValue = dataValueIn();
    	oldDataValue.getValue(oldValue);

    	OpcUaDataValue dataValue(value);

    	// check if value changed
    	auto diff = oldValue - value;
    	if (diff > precision_ || diff < -precision_) {
    		handleUpdateEvent(dataValue);
    	}

    	// set input value
    	dataValueIn(OpcUaDataValue(value));
    }

    void
	PiXtendAnalogValueContext::readFunc(ReadFunc readFunc)
    {
    	readFunc_ = readFunc;
    }

    PiXtendAnalogValueContext::ReadFunc
	PiXtendAnalogValueContext::readFunc(void)
    {
    	return readFunc_;
    }

    void
	PiXtendAnalogValueContext::writeFunc(WriteFunc writeFunc)
    {
    	writeFunc_ = writeFunc;
    }

    PiXtendAnalogValueContext::WriteFunc
	PiXtendAnalogValueContext::writeFunc(void)
    {
    	return writeFunc_;
    }

}
