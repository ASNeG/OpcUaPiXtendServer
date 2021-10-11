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

#include "OpcUaPiXtendServer/PiXtend/UpdateContext.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

	UpdateElement::UpdateElement(void)
	{
	}

	UpdateElement::UpdateElement(UpdateFunc updateFunc, OpcUaStackCore::BaseClass::SPtr& context)
	{
		updateFunc_ = updateFunc;
		context_ = context;
	}

	UpdateElement::~UpdateElement(void)
	{
	}

	void
	UpdateElement::updateFunc(UpdateElement::UpdateFunc updateFunc) {
		updateFunc_ = updateFunc;
	}

	UpdateElement::UpdateFunc
	UpdateElement::updateFunc(void)
	{
		return updateFunc_;
	}

	void
	UpdateElement::context(BaseClass::SPtr& context)
	{
		context_ = context;
	}

	BaseClass::SPtr
	UpdateElement::context(void)
	{
		return context_;
	}


    UpdateContext::UpdateContext(void)
    {
    }

    UpdateContext::~UpdateContext(void)
    {
    }

    bool
	UpdateContext::addContext(
    	OpcUaNodeId& id,
		UpdateElement::UpdateFunc updateFunc,
		OpcUaStackCore::BaseClass::SPtr& context
	)
    {
    	boost::mutex::scoped_lock g(mutex_);

    	// check if element already exist
    	if (updateElementMap_.find(id) != updateElementMap_.end()) {
    		return false;
    	}

    	// add new element to update map
    	auto updateElement = boost::make_shared<UpdateElement>();
    	updateElement->updateFunc(updateFunc);
    	updateElement->context(context);
    	updateElementMap_.insert(std::make_pair(id, updateElement));
    	return true;
    }

    bool
	UpdateContext::delContext(
    	OpcUaNodeId& id
    )
    {
    	boost::mutex::scoped_lock g(mutex_);

    	// check if element exist
    	if (updateElementMap_.find(id) == updateElementMap_.end()) {
    		return false;
    	}

    	updateElementMap_.erase(id);
    	return true;
    }

    void
	UpdateContext::callEvents(
		OpcUaDataValue& dataValue
	)
    {
    	UpdateElement::Vec updateElementVec;

    	// get all update elements
    	mutex_.lock();
    	for (auto updateElementPair : updateElementMap_) {
    		auto updateFunc = updateElementPair.second->updateFunc();
    		auto context = updateElementPair.second->context();
    		auto updateElement = boost::make_shared<UpdateElement>(updateFunc, context);
    		updateElementVec.push_back(updateElement);
    	}
    	mutex_.unlock();

    	// call update functions
    	for (auto updateElement : updateElementVec) {
    		auto updateFunc = updateElement->updateFunc();
    		auto context = updateElement->context();
    		updateFunc(dataValue, context);
    	}
    }

}
