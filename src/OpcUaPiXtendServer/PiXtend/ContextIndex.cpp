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

#include "OpcUaPiXtendServer/PiXtend/ContextIndex.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    ContextIndex::ContextIndex(void)
    {
    }

    ContextIndex::~ContextIndex(void)
    {
    }

    bool
	ContextIndex::registerContext(
        const std::string& contextName,
    	BaseClass::SPtr& context
	)
    {
    	if (existContext(contextName)) {
    		return false;
    	}

    	contextMap_.insert(std::make_pair(contextName, context));
    	return true;
    }

    bool
	ContextIndex::deregisterContext(
    	const std::string& contextName
    )
    {
    	if (!existContext(contextName)) {
    		return false;
    	}

    	contextMap_.erase(contextName);
    	return true;
    }

    bool
	ContextIndex::existContext(
    	const std::string& contextName
    )
    {
    	if (contextMap_.find(contextName) == contextMap_.end()) {
    		return false;
    	}
    	else {
    		return true;
    	}
    }

    BaseClass::SPtr
	ContextIndex::getContext(
    	const std::string& contextName
    )
    {
    	auto it = contextMap_.find(contextName);
    	if (it == contextMap_.end()) {
    		return nullptr;
    	}
    	else {
    		return it->second;
    	}
    }

}
