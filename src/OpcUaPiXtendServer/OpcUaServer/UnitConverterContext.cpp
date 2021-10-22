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
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

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
    UnitConverterContext::input(OpcUaStackCore::OpcUaDataValue& dataValue)
    {
        double nodeValue {0.0};
        double percent {0.0};

        if (!dataValue.getValue(nodeValue)) {
            return false;
        }

        if (!input(nodeValue, percent)) {
            return false;
        }

        dataValue.setValue(percent);
        return true;
    }

    bool
    UnitConverterContext::input(double nodeValue, double& percent)
    {
        // Formula: Y = (A + BX) / (C + DX)
        // Y: Percent from PIN
        // X: Node variable

        double n = (c_ + d_ * nodeValue);
        if (n == 0) {
            Log(Error, "UnitConverterContext::input - found division by 0");
            return false;
        }

        percent = (a_ + b_ * nodeValue) / n;
        return true;
    }

    bool
    UnitConverterContext::output(OpcUaStackCore::OpcUaDataValue& dataValue)
    {
        double nodeValue {0.0};
        double percent {0.0};

        if (!dataValue.getValue(percent)) {
            return false;
        }

        if (!output(percent, nodeValue)) {
            return false;
        }

        dataValue.setValue(nodeValue);
        return true;
    }

    double
	UnitConverterContext::a(void)
    {
    	return a_;
    }

    double
	UnitConverterContext::b(void)
    {
    	return b_;
    }

    double
	UnitConverterContext::c(void)
    {
    	return c_;
    }

    double
	UnitConverterContext::d(void)
    {
    	return d_;
    }

    bool
    UnitConverterContext::output(double percent, double& nodeValue)
    {
        // Formula: X = (CY - A) / (B - DY)
        // Y: Percent from PIN
        // X: Node variable

        double n = (b_ - d_ * percent);
        if (n == 0) {
            Log(Error, "UnitConverterContext::output - found division by 0");
            return false;
        }

        nodeValue = ((-a_) + c_ * percent) / n;
        return true;
    }

}
