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

#ifndef __OpcUaPiXtendServer_PiXtendToolModuleV2L_h__
#define __OpcUaPiXtendServer_PiXtendToolModuleV2L_h__

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2L.h"
#include "OpcUaPiXtendServer/Tools/PiXtendToolModule.h"

namespace OpcUaPiXtendServer
{

    class PiXtendToolModuleV2L
    : public PiXtendToolModule
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendToolModuleV2L>;

        PiXtendToolModuleV2L(const std::string& name);
        virtual ~PiXtendToolModuleV2L(void);

        virtual bool readPin(Pins pin, PiXtendToolReadStruct& result) override;

        virtual bool writeAnalogPin(Pins pin, AValue data) override;
        virtual bool writeDigitalPin(Pins pin, DValue data) override;

      private:
        PiXtendV2L::SPtr pixtendSPtr_;
    };

}

#endif
