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

#ifndef __OpcUaPiXtendServer_PiXtendModulesFactory_h__
#define __OpcUaPiXtendServer_PiXtendModulesFactory_h__

#include <boost/shared_ptr.hpp>
#include <string>
#include <functional>

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendV2L.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODO.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAO.h"

namespace OpcUaPiXtendServer
{

    class PiXtendModulesFactory
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendModulesFactory>;

        PiXtendModulesFactory(void);
        virtual ~PiXtendModulesFactory(void);

        static PiXtendV2S::SPtr createPiXtendV2S(const std::string& instanceName);
        static PiXtendV2L::SPtr createPiXtendV2L(const std::string& instanceName);
        static PiXtendEIOAO::SPtr createPiXtendEIOAO(const std::string& instanceName);
        static PiXtendEIODO::SPtr createPiXtendEIODO(
        	const std::string& type,
			const std::string& instanceName
		);
    };

}

#endif
