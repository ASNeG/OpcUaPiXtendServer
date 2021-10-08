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

#ifndef __OpcUaPiXtendServer_UpdateContext_h__
#define __OpcUaPiXtendServer_UpdateContext_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaStackCore/Base/BaseClass.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"

namespace OpcUaPiXtendServer
{

	class UpdateElement
	{
	  public:
		using SPtr = boost::shared_ptr<UpdateElement>;
		using UpdateFunc = std::function<void (const OpcUaStackCore::OpcUaDataValue& dataValue, const OpcUaStackCore::BaseClass::SPtr& context)>;
		using Map = std::map<OpcUaStackCore::OpcUaNodeId, UpdateElement::SPtr>;

		UpdateElement(void);
		~UpdateElement(void);

		void updateFunc(UpdateFunc updateFunc);
		UpdateFunc updateFunc(void);
		void context(OpcUaStackCore::BaseClass::SPtr& context);
		OpcUaStackCore::BaseClass::SPtr context(void);

	  private:
		UpdateFunc updateFunc_;
		OpcUaStackCore::BaseClass::SPtr context_;

	};


    class UpdateContext
    {
      public:
    	using SPtr = boost::shared_ptr<UpdateContext>;

        UpdateContext(void);
        virtual ~UpdateContext(void);

        bool addContext(
        	OpcUaStackCore::OpcUaNodeId& id,
			UpdateElement::UpdateFunc updateFunc,
			OpcUaStackCore::BaseClass::SPtr& context
		);
        bool delContext(
        	OpcUaStackCore::OpcUaNodeId& id
        );
        void callEvents(
        	OpcUaStackCore::OpcUaDataValue& dataValue
		);

      private:
        UpdateElement::Map updateElementMap_;
    };

}

#endif
