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

#ifndef __OpcUaPiXtendServer_PiXtendValueContext_h__
#define __OpcUaPiXtendServer_PiXtendValueContext_h__

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "OpcUaStackCore/Base/BaseClass.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"
#include "OpcUaPiXtendServer/PiXtend/UpdateContext.h"

namespace OpcUaPiXtendServer
{

    class PiXtendValueContext
	: public OpcUaStackCore::BaseClass
    {
      public:
    	using UpdateFunc = std::function<void (OpcUaStackCore::BaseClass::SPtr&, OpcUaStackCore::OpcUaDataValue& dataValue)>;
    	using SPtr = boost::shared_ptr<PiXtendValueContext>;
    	using Vec = std::vector<SPtr>;

    	enum class ContextType {
    		DigitalValue,
    		AnalogValue
    	};

        PiXtendValueContext(PiXtendValueContext::ContextType contextType);
        virtual ~PiXtendValueContext(void);

        PiXtendValueContext::ContextType contextType(void);

        void dataValueIn(const OpcUaStackCore::OpcUaDataValue& dataValue);
        void dataValueOut(const OpcUaStackCore::OpcUaDataValue& dataValue);
        OpcUaStackCore::OpcUaDataValue dataValueIn(void);
        OpcUaStackCore::OpcUaDataValue dataValueOut(void);
        bool writeAccess(void);
        void writeAccess(bool writeAccess);
        bool addMonitoredItem(
        	OpcUaStackCore::OpcUaNodeId& id,
    		UpdateElement::UpdateFunc updateFunc,
    		OpcUaStackCore::BaseClass::SPtr& context
    	);
        bool delMonitoredItem(
        	OpcUaStackCore::OpcUaNodeId& id
        );
        void handleUpdateEvent(OpcUaStackCore::OpcUaDataValue& dataValue);

        virtual void dataValueToOutputStruct(void) = 0;
        virtual void inputStructToDataValue(void) = 0;

      private:
        ContextType contextType_;
        bool writeAccess_ = true;

        boost::mutex valueMutex_;
        OpcUaStackCore::OpcUaDataValue inputDataValue_;
        OpcUaStackCore::OpcUaDataValue outputDataValue_;
        UpdateContext updateContext_;
    };

}

#endif
