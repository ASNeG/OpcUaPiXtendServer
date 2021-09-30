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

#ifndef __OpcUaPiXtendServer_PiXtendV2SServer_h__
#define __OpcUaPiXtendServer_PiXtendV2SServer_h__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaStackServer/StandardObjectType/ObjectBase.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"

namespace OpcUaPiXtendServer
{

    class PiXtendV2SServer
    : public OpcUaStackServer::ObjectBase,
	  public boost::enable_shared_from_this<PiXtendV2SServer>
    {
      public:

    	using SPtr = boost::shared_ptr<PiXtendV2SServer>;

        PiXtendV2SServer(void);
        ~PiXtendV2SServer(void);

        bool startup(
        	OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
            const std::string& instanceName,
			const std::string& namespaceName,
			uint16_t namespaceIndex,
			const OpcUaStackCore::OpcUaNodeId& parentNodeId
		);
        bool shutdown(void);

      private:
        OpcUaStackServer::ApplicationServiceIf* applicationServiceIf_ = nullptr;
        std::string namespaceName_ = "";
        uint16_t namespaceIndex_ = 0;
        PiXtendV2S::SPtr pixtend_ = nullptr;
        std::string instanceName_ = "";
        OpcUaStackCore::OpcUaNodeId parentNodeId_;

        bool createObjectInstance(void);
    };

}

#endif
