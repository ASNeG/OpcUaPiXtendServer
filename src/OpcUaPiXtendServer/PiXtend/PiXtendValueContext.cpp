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
	PiXtendValueContext::dataValue(OpcUaDataValue& dataValue)
    {
    	outputDataValue_ = dataValue;
    }

    OpcUaStackCore::OpcUaDataValue
	PiXtendValueContext::dataValue(void)
    {
    	OpcUaDataValue dataValue;

    	dataValue = inputDataValue_;

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

}
