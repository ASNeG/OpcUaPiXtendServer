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

#include "OpcUaPiXtendServer/PiXtend/PiXtendSpiHelper.h"

namespace OpcUaPiXtendServer
{

    PiXtendSpiHelper::PiXtendSpiHelper(void)
    {
    }

    PiXtendSpiHelper::~PiXtendSpiHelper(void)
    {
    }

    void
    PiXtendSpiHelper::changeBit(uint8_t& valueToModify, uint8_t bit, uint8_t position)
    {
        uint8_t mask = 1 << position;
        valueToModify = ((valueToModify & ~mask) | (bit << position));
    }

    bool
    PiXtendSpiHelper::bit2Bool(uint8_t value, uint8_t position)
    {
        if ((value & (1 << position)) == 0)
        {
            return false; // bit is not set
        }
        return true;
    }

    double
    PiXtendSpiHelper::analog2Percent(uint16_t value)
    {
        // Wertebereich 0 - 1023
        // Umlegung auf 0 - 1

        if (value > 1023)
        {
            return 1.0;
        }
        else if (value == 0)
        {
            return 0.0;
        }
        else
        {
            return static_cast<double>(value) / 1023;
        }
    }

    uint16_t
    PiXtendSpiHelper::percent2Analog(double value)
    {
        // Wertebereich 0 - 1
        // Umlegung auf 0 - 1023

        if (value > 1.0)
        {
            return 1023;
        }
        else if (value == 0)
        {
            return 0;
        }
        else
        {
            return static_cast<uint16_t>(value * 1023);
        }
    }

}
