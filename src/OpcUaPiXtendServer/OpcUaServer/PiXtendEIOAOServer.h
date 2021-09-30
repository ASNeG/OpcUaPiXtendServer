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

#ifndef __OpcUaPiXtendServer_PiXtendEIOAOServer_h__
#define __OpcUaPiXtendServer_PiXtendEIOAOServer_h__

#include <boost/shared_ptr.hpp>

#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"

namespace OpcUaPiXtendServer
{

    class PiXtendEIOAOServer
    {
      public:

    	using SPtr = boost::shared_ptr<PiXtendEIOAOServer>;

        PiXtendEIOAOServer(void);
        ~PiXtendEIOAOServer(void);

        bool startup(
            const std::string& instanceName,
			const OpcUaStackCore::OpcUaNodeId& parentNodeId
		);
        bool shutdown(void);

      private:
        PiXtendEIOAO::SPtr pixtend_ = nullptr;
    };

}

#endif
