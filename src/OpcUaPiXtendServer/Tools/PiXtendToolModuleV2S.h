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

#ifndef __OpcUaPiXtendServer_PiXtendToolModuleV2S_h__
#define __OpcUaPiXtendServer_PiXtendToolModuleV2S_h__

#include "OpcUaPiXtendServer/Tools/PiXtendToolModule.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendModulesFactory.h"

namespace OpcUaPiXtendServer
{

    class PiXtendToolModuleV2S
    : public PiXtendToolModule
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendToolModuleV2S>;

        PiXtendToolModuleV2S(void);
        virtual ~PiXtendToolModuleV2S(void);

        virtual bool readPin(Pins pin, PiXtendToolReadStruct& result) override;

        virtual bool writeAnalogPin(Pins pin, AValue data) override;
        virtual bool writeDigitalPin(Pins pin, DValue data) override;

      private:
        PiXtendV2S::SPtr pixtendSPtr_;
    };

}

#endif
