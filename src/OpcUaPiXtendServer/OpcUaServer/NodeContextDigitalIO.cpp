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

#include "OpcUaPiXtendServer/OpcUaServer/NodeContextDigitalIO.h"

namespace OpcUaPiXtendServer
{

    NodeContextDigitalIO::NodeContextDigitalIO(void)
    : NodeContext(ContextType::DigitalIO)
    {
    	readFunc_.first = false;
    	writeFunc_.first = false;
    }

    NodeContextDigitalIO::~NodeContextDigitalIO(void)
    {
    }

    bool
	NodeContextDigitalIO::existReadFunc(void)
    {
    	return readFunc_.first;
    }

    void
	NodeContextDigitalIO::setReadFunc(NodeContextDigitalIO::ReadFunc readFunc)
    {
    	readFunc_ = {true, readFunc};
    }

    void
	NodeContextDigitalIO::unsetReadFunc(void)
    {
    	readFunc_.first = false;
    }

    NodeContextDigitalIO::ReadFunc
	NodeContextDigitalIO::getReadFunc(void)
    {
    	return readFunc_.second;
    }

    bool
	NodeContextDigitalIO::existWriteFunc(void)
    {
    	return writeFunc_.first;
    }

    void
	NodeContextDigitalIO::setWriteFunc(NodeContextDigitalIO::WriteFunc writeFunc)
    {
    	writeFunc_ = {true, writeFunc};
    }

    void
	NodeContextDigitalIO::unsetWriteFunc(void)
    {
    	writeFunc_.first = false;
    }

    NodeContextDigitalIO::WriteFunc
	NodeContextDigitalIO::getWriteFunc(void)
    {
    	return writeFunc_.second;
    }

}
