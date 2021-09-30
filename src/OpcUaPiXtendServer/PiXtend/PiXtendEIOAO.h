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

#ifndef __OpcUaPiXtendServer_PiXtendEIOAO_h__
#define __OpcUaPiXtendServer_PiXtendEIOAO_h__

#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <functional>

namespace OpcUaPiXtendServer
{

    class PiXtendEIOAO
    {
      public:
        using SPtr = boost::shared_ptr<PiXtendEIOAO>;

        PiXtendEIOAO(void);
        virtual ~PiXtendEIOAO(void);

        // Configuration

        virtual bool startup(uint32_t moduleAddress) = 0;
        virtual bool shutdown(void) = 0;

        // Inputs Analog

        virtual double ai0(void) = 0;
        virtual double ai1(void) = 0;
        virtual double ai2(void) = 0;
        virtual double ai3(void) = 0;
        virtual double ai4(void) = 0;
        virtual double ai5(void) = 0;
        virtual double ai6(void) = 0;
        virtual double ai7(void) = 0;

        // Output Analog

        virtual void ao0(double data) = 0;
        virtual double ao0(void) = 0;
        virtual void ao1(double data) = 0;
        virtual double ao1(void) = 0;
        virtual void ao2(double data) = 0;
        virtual double ao2(void) = 0;
        virtual void ao3(double data) = 0;
        virtual double ao3(void) = 0;
        virtual void ao4(double data) = 0;
        virtual double ao4(void) = 0;
        virtual void ao5(double data) = 0;
        virtual double ao5(void) = 0;
    };

}

#endif
