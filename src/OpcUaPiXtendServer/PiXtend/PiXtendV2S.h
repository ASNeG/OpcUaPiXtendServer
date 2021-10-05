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

#ifndef __OpcUaPiXtendServer_PiXtendV2S_h__
#define __OpcUaPiXtendServer_PiXtendV2S_h__

#include <boost/shared_ptr.hpp>
#include <string>
#include <functional>

#include "OpcUaPiXtendServer/PiXtend/PiXtendBase.h"

namespace OpcUaPiXtendServer
{

    class PiXtendV2S
	: public PiXtendBase
    {
      public:
    	using SPtr = boost::shared_ptr<PiXtendV2S>;

        PiXtendV2S(const std::string& name);
        virtual ~PiXtendV2S(void);

        // Configuration

        virtual void handleRegisterContext(void) override;
        virtual bool startup(void) = 0;
        virtual bool shutdown(void) = 0;

        // Inputs Analog

        virtual double ai0(void) = 0;
        virtual double ai1(void) = 0;

        // Output Analog

        virtual void ao0(double data) = 0;
        virtual double ao0(void) = 0;
        virtual void ao1(double data) = 0;
        virtual double ao1(void) = 0;

        // Inputs Digital

        virtual bool di0(void) = 0;
        virtual bool di1(void) = 0;
        virtual bool di2(void) = 0;
        virtual bool di3(void) = 0;
        virtual bool di4(void) = 0;
        virtual bool di5(void) = 0;
        virtual bool di6(void) = 0;
        virtual bool di7(void) = 0;

        // Output Digital

        virtual void do0(bool data) = 0;
        virtual bool do0(void) = 0;
        virtual void do1(bool data) = 0;
        virtual bool do1(void) = 0;
        virtual void do2(bool data) = 0;
        virtual bool do2(void) = 0;
        virtual void do3(bool data) = 0;
        virtual bool do3(void) = 0;

        // Relay

        virtual void relay0(bool data) = 0;
        virtual bool relay0(void) = 0;
        virtual void relay1(bool data) = 0;
        virtual bool relay1(void) = 0;
        virtual void relay2(bool data) = 0;
        virtual bool relay2(void) = 0;
        virtual void relay3(bool data) = 0;
        virtual bool relay3(void) = 0;

        // Input/Output General Purpose

        virtual void gpio0(bool data) = 0;
        virtual bool gpio0(void) = 0;
        virtual void gpio1(bool data) = 0;
        virtual bool gpio1(void) = 0;
        virtual void gpio2(bool data) = 0;
        virtual bool gpio2(void) = 0;
        virtual void gpio3(bool data) = 0;
        virtual bool gpio3(void) = 0;
    };

}

#endif
