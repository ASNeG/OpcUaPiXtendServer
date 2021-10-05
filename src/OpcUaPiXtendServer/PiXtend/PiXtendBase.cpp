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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendBase.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendBase::PiXtendBase(const std::string& instanceName)
    : instanceName_(instanceName)
    {
    }

    PiXtendBase::~PiXtendBase(void)
    {
    }

    void
	PiXtendBase::loop(void)
    {
    }

    void
	PiXtendBase::contextIndex(ContextIndex::SPtr& contextIndex)
    {
    	contextIndex_ = contextIndex;
    	handleRegisterContext();
    }

    std::string
	PiXtendBase::instanceName(void)
    {
    	return instanceName_;
    }

    ContextIndex::SPtr
	PiXtendBase::contextIndex(void)
    {
    	return contextIndex_;
    }

    bool
	PiXtendBase::registerContext(
    	const std::string& contextName,
		PiXtendValueContext::SPtr& piXtendValueContext
    )
    {
    	// check if context already exist
    	if (contextIndex_->existContext(contextName)) {
    		Log(Error, "context already exist in context index")
    			.parameter("ContextName", contextName);
    		return false;
    	}

    	// add new context to context index
    	BaseClass::SPtr context = piXtendValueContext;
    	contextIndex_->registerContext(contextName, context);
    	return true;
    }

    bool
	PiXtendBase::registerContext(const CfgElementVec& cfgElementVec)
    {
    	for (auto cfgElement : cfgElementVec) {
    		auto name = instanceName_ + "." + cfgElement.first;
    		auto rc = registerContext(name, cfgElement.second);
    		if (!rc) return false;
    	}
    	return true;
    }

}
