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

#ifndef __OpcUaPiXtendServer_ContextIndex_h__
#define __OpcUaPiXtendServer_ContextIndex_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaStackCore/Base/BaseClass.h"

namespace OpcUaPiXtendServer
{

    class ContextIndex
    {
      public:
    	using SPtr = boost::shared_ptr<ContextIndex>;
    	using ContextMap = std::map<std::string, OpcUaStackCore::BaseClass::SPtr>;

        ContextIndex(void);
        virtual ~ContextIndex(void);

        bool registerContext(
            const std::string& contextName,
        	OpcUaStackCore::BaseClass::SPtr& context
		);
        bool deregisterContext(
        	const std::string& contextName
        );
        bool existContext(
        	const std::string& contextName
        );
        OpcUaStackCore::BaseClass::SPtr getContext(
        	const std::string& contextName
        );

      private:
        ContextMap contextMap_;
    };

}

#endif
