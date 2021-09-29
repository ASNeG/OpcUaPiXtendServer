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

#ifndef __OpcUaPiXtendServer_PiXtendEIODO_h__
#define __OpcUaPiXtendServer_PiXtendEIODO_h__

#include <string>
#include <functional>

namespace OpcUaPiXtendServer
{

    class PiXtendEIODO
    {
      public:
        PiXtendEIODO(void);
        virtual ~PiXtendEIODO(void);

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
        virtual void do4(bool data) = 0;
        virtual bool do4(void) = 0;
        virtual void do5(bool data) = 0;
        virtual bool do5(void) = 0;
        virtual void do6(bool data) = 0;
        virtual bool do6(void) = 0;
        virtual void do7(bool data) = 0;
        virtual bool do7(void) = 0;
    };

}

#endif
