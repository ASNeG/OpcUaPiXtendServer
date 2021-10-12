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

#include "OpcUaPiXtendServer/OpcUaServer/UnitConverterContext.h"

namespace OpcUaPiXtendServer
{

    UnitConverterContext::UnitConverterContext(double a, double b, double c, double d)
    : a_(a)
    , b_(b)
    , c_(c)
    , d_(d)
    {
    }

    UnitConverterContext::~UnitConverterContext(void)
    {
    }

    bool
    UnitConverterContext::input(double nodeValue, double& percent)
    {
        // Formula: Y = (A + BX) / (C + DX)
        // Y: Percent from PIN
        // X: Node variable

        percent = (a_ + b_ * nodeValue) / (c_ + d_ * nodeValue);
        return true;
    }

    bool
    UnitConverterContext::output(double percent, double& nodeValue)
    {
        // Formula: X = (CY - A) / (B - DY)
        // Y: Percent from PIN
        // X: Node variable

        nodeValue = ((-a_) + c_ * percent) / (b_ - d_ * percent);
        return true;
    }

}
