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

#include "OpcUaPiXtendServer/PiXtend/PiXtendByteValueContext.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendByteValueContext::PiXtendByteValueContext(void)
    : PiXtendValueContext(ContextType::AnalogValue)
    {
        dataValueIn(OpcUaDataValue(0));
        dataValueOut(OpcUaDataValue(0));
    }

    PiXtendByteValueContext::~PiXtendByteValueContext(void)
    {
    }

    PiXtendByteValueContext::SPtr
    PiXtendByteValueContext::createContext(
         ReadFunc readFunc,
         WriteFunc writeFunc
    )
    {
        auto context = boost::make_shared<PiXtendByteValueContext>();
        context->readFunc(readFunc);
        context->writeFunc(writeFunc);
        context->writeAccess(writeFunc == nullptr ? false : true);
        return context;
    }

    void
    PiXtendByteValueContext::dataValueToOutputStruct(void)
    {
        uint8_t value;
        auto dataValue = dataValueOut();
        dataValue.getValue(value);
        writeFunc()(value);
    }

    void
    PiXtendByteValueContext::inputStructToDataValue(void)
    {
        uint8_t value = readFunc()();
        uint8_t oldValue;
        auto oldDataValue = dataValueIn();
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
    PiXtendByteValueContext::readFunc(ReadFunc readFunc)
    {
        readFunc_ = readFunc;
    }

    PiXtendByteValueContext::ReadFunc
    PiXtendByteValueContext::readFunc(void)
    {
        return readFunc_;
    }

    void
    PiXtendByteValueContext::writeFunc(WriteFunc writeFunc)
    {
        writeFunc_ = writeFunc;
    }

    PiXtendByteValueContext::WriteFunc
    PiXtendByteValueContext::writeFunc(void)
    {
        return writeFunc_;
    }

}
