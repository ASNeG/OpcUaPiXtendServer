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

#include "OpcUaPiXtendServer/PiXtend/PiXtendModules.h"

namespace OpcUaPiXtendServer
{

    PiXtendModules::PiXtendModules(void)
    {
#ifdef OPCUAPIXTENDSERVER_MODUL_V2S_DUMMY
        pixtendV2SSPtr_ = std::make_shared<PiXtendV2SDummy>();
#else
        pixtendV2SSPtr_ = std::make_shared<PiXtendV2SInst>();
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_V2L_DUMMY
        pixtendV2LSPtr_ = std::make_shared<PiXtendV2LDummy>();
#else
        pixtendV2LSPtr_ = std::make_shared<PiXtendV2LInst>();
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_EIOAO_DUMMY
        pixtendEIOAOSPtr_ = std::make_shared<PiXtendEIOAODummy>();
#else
        pixtendEIOAOSPtr_ = std::make_shared<PiXtendEIOAOInst>();
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_EIODO_DUMMY
        pixtendEIODOSPtr_ = std::make_shared<PiXtendEIODODummy>();
#else
        pixtendEIODOSPtr_ = std::make_shared<PiXtendEIODOInst>();
#endif
    }

    PiXtendModules::~PiXtendModules(void)
    {
    }

    std::shared_ptr<PiXtendV2S>
    PiXtendModules::getPiXtendV2S(void)
    {
        return pixtendV2SSPtr_;
    }

    std::shared_ptr<PiXtendV2L>
    PiXtendModules::getPiXtendV2L(void)
    {
        return pixtendV2LSPtr_;
    }

    std::shared_ptr<PiXtendEIOAO>
    PiXtendModules::getPiXtendV2EIOAO(void)
    {
        return pixtendEIOAOSPtr_;
    }

    std::shared_ptr<PiXtendEIODO>
    PiXtendModules::getPiXtendV2EIODO(void)
    {
        return pixtendEIODOSPtr_;
    }

}
