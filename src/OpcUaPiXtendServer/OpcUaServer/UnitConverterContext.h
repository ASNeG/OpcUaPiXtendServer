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

#ifndef __OpcUaPiXtendServer_UnitConverterContext_h__
#define __OpcUaPiXtendServer_UnitConverterContext_h__

#include <boost/shared_ptr.hpp>

namespace OpcUaPiXtendServer
{

    class     UnitConverterContext
    {
      public:
        using SPtr = boost::shared_ptr<UnitConverterContext>;

        UnitConverterContext(double a, double b, double c, double d);
        virtual ~UnitConverterContext(void);

        /**
         * @brief Formula: Y = (A + BX) / (C + DX)
         *        Y: Percent from PIN
         *        X: Node variable
         * @return true by success otherwise false.
         */
        bool input(double nodeValue, double& percent);

        /**
         * @brief Formula: X = (CY - A) / (B - DY)
         *        Y: Percent from PIN
         *        X: Node variable
         * @return true by success otherwise false.
         */
        bool output(double percent, double& nodeValue);

    private:
        double a_ {0.0};
        double b_ {0.0};
        double c_ {0.0};
        double d_ {0.0};
    };

}

#endif
