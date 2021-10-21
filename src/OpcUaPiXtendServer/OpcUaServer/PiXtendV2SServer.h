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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendBaseServer.h"

namespace OpcUaPiXtendServer
{

    class PiXtendV2SServer
    : public PiXtendBaseServer
    {
      public:

    	using SPtr = boost::shared_ptr<PiXtendV2SServer>;

        PiXtendV2SServer(void);
        virtual ~PiXtendV2SServer(void);

        virtual bool handleStartup(void) override;
        virtual bool handleShutdown(void) override;

      private:
        PiXtendV2S::SPtr pixtend_ = nullptr;
    };

}

#endif
