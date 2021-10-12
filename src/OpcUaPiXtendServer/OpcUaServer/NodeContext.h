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

#ifndef __OpcUaPiXtendServer_NodeContext_h__
#define __OpcUaPiXtendServer_NodeContext_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaStackCore/Base/BaseClass.h"
#include "OpcUaStackServer/StandardVariableType/ServerVariables.h"
#include "OpcUaPiXtendServer/OpcUaServer/UnitConverterContext.h"

namespace OpcUaPiXtendServer
{

    class NodeContext
	: public OpcUaStackCore::BaseClass
    {
      public:

    	using SPtr = boost::shared_ptr<NodeContext>;

        NodeContext(void);
        virtual ~NodeContext(void);

        void serverVariable(OpcUaStackServer::ServerVariable::SPtr& serverVariable);
        OpcUaStackServer::ServerVariable::SPtr& serverVariable(void);
        void hardwareContext(BaseClass::SPtr& hardwareContext);
        BaseClass::SPtr hardwareContext(void);
        void unitConverterContext(UnitConverterContext::SPtr analogValueConverter);
        UnitConverterContext::SPtr unitConverterContext(void);

      private:
        OpcUaStackServer::ServerVariable::SPtr serverVariable_ = nullptr;
        OpcUaStackCore::BaseClass::SPtr hardwareContext_ = nullptr;
        UnitConverterContext::SPtr unitConverterContext_ = nullptr;
    };

}

#endif
