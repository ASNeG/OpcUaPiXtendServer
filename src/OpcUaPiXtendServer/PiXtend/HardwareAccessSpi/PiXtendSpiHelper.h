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

#ifndef __OpcUaPiXtendServer_PiXtendSpiHelper_h__
#define __OpcUaPiXtendServer_PiXtendSpiHelper_h__

#include <stdint.h>

namespace OpcUaPiXtendServer
{

    class PiXtendSpiHelper
    {
      public:
        PiXtendSpiHelper(void);
        virtual ~PiXtendSpiHelper(void);

        void changeBit(uint8_t& valueToModify, uint8_t bit, uint8_t position);
        bool bit2Bool(uint8_t value, uint8_t position);

        double analog2Percent(uint16_t value);
        uint16_t percent2Analog(double value);
    };

}

#endif
