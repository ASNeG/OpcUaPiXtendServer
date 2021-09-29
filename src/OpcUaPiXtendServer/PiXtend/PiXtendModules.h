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

#ifndef __OpcUaPiXtendServer_PiXtendModules_h__
#define __OpcUaPiXtendServer_PiXtendModules_h__

#include <string>
#include <functional>
#include <memory>

#ifdef OPCUAPIXTENDSERVER_MODUL_V2S_DUMMY
    #include "OpcUaPiXtendServer/PiXtend/PiXtendV2SDummy.h"
#else
    #include "OpcUaPiXtendServer/PiXtend/PiXtendV2SInst.h"
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_V2L_DUMMY
    #include "OpcUaPiXtendServer/PiXtend/PiXtendV2LDummy.h"
#else
    #include "OpcUaPiXtendServer/PiXtend/PiXtendV2LInst.h"
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_EIOAO_DUMMY
    #include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAODummy.h"
#else
    #include "OpcUaPiXtendServer/PiXtend/PiXtendEIOAOInst.h"
#endif

#ifdef OPCUAPIXTENDSERVER_MODUL_EIODO_DUMMY
    #include "OpcUaPiXtendServer/PiXtend/PiXtendEIODODummy.h"
#else
    #include "OpcUaPiXtendServer/PiXtend/PiXtendEIODOInst.h"
#endif


namespace OpcUaPiXtendServer
{

    class PiXtendModules
    {
      public:
        PiXtendModules(void);
        virtual ~PiXtendModules(void);

        std::shared_ptr<PiXtendV2S> getPiXtendV2S(void);
        std::shared_ptr<PiXtendV2L> getPiXtendV2L(void);
        std::shared_ptr<PiXtendEIOAO> getPiXtendV2EIOAO(void);
        std::shared_ptr<PiXtendEIODO> getPiXtendV2EIODO(void);

      private:
        std::shared_ptr<PiXtendV2S> pixtendV2SSPtr_;
        std::shared_ptr<PiXtendV2L> pixtendV2LSPtr_;
        std::shared_ptr<PiXtendEIOAO> pixtendEIOAOSPtr_;
        std::shared_ptr<PiXtendEIODO> pixtendEIODOSPtr_;
    };

}

#endif
