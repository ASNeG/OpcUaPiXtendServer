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

#include <boost/make_shared.hpp>

#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"

namespace OpcUaPiXtendServer
{

    PiXtendModulesFactory::PiXtendModulesFactory(void)
    {
    }

    PiXtendModulesFactory::~PiXtendModulesFactory(void)
    {
    }

    PiXtendV2S::SPtr
    PiXtendModulesFactory::createPiXtendV2S(const std::string& instanceName)
    {
#ifdef OPCUAPIXTENDSERVER_MODUL_V2S_DUMMY
        return boost::make_shared<PiXtendV2SDummy>(instanceName);
#else
        return boost::make_shared<PiXtendV2SInst>(instanceName);
#endif
    }

    PiXtendV2L::SPtr
    PiXtendModulesFactory::createPiXtendV2L(const std::string& instanceName)
    {
#ifdef OPCUAPIXTENDSERVER_MODUL_V2L_DUMMY
        return boost::make_shared<PiXtendV2LDummy>(instanceName);
#else
        return boost::make_shared<PiXtendV2LInst>(instanceName);
#endif
    }

    PiXtendEIOAO::SPtr
    PiXtendModulesFactory::createPiXtendEIOAO(const std::string& instanceName)
    {
#ifdef OPCUAPIXTENDSERVER_MODUL_EIOAO_DUMMY
        return boost::make_shared<PiXtendEIOAODummy>(instanceName);
#else
        return boost::make_shared<PiXtendEIOAOInst>(instanceName);
#endif
    }

    PiXtendEIODO::SPtr
    PiXtendModulesFactory::createPiXtendEIODO(const std::string& instanceName)
    {
#ifdef OPCUAPIXTENDSERVER_MODUL_EIODO_DUMMY
        return boost::make_shared<PiXtendEIODODummy>(instanceName);
#else
        return boost::make_shared<PiXtendEIODOInst>(instanceName);
#endif
    }

}
