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

#include "OpcUaPiXtendServer/OpcUaServer/NodeContext.h"

using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    NodeContext::NodeContext(ContextType contextType)
    : contextType_(contextType)
    {
    }

    NodeContext::~NodeContext(void)
    {
    }

    ContextType
	NodeContext::contextType(void)
    {
    	return contextType_;
    }

    void
	NodeContext::serverVariable(ServerVariable::SPtr& serverVariable)
    {
    	serverVariable_ = serverVariable;
    }

    ServerVariable::SPtr&
	NodeContext::serverVariable(void)
    {
    	return serverVariable_;
    }

    void
	NodeContext::hardwareContext(BaseClass::SPtr& hardwareContext)
    {
    	hardwareContext_ = hardwareContext;
    }

    BaseClass::SPtr
	NodeContext::hardwareContext(void)
    {
    	return hardwareContext_;
    }

}
