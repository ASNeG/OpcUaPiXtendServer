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

#include "OpcUaPiXtendServer/PiXtend/PiXtendEIODOInst.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIODOInst::PiXtendEIODOInst(const std::string& instanceName)
    : PiXtendEIODO(instanceName)
    {
    }

    PiXtendEIODOInst::~PiXtendEIODOInst(void)
    {
    }

    // Configuration

    bool
    PiXtendEIODOInst::startup(uint32_t moduleAddress)
    {
        return true;
    }

    bool
    PiXtendEIODOInst::shutdown(void)
    {
        return true;
    }

    void
	PiXtendEIODOInst::handleHardwareAccess(void)
    {
    	// FIXME: TBD
    }

    // Inputs Digital

    bool
    PiXtendEIODOInst::di0(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di1(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di2(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di3(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di4(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di5(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di6(void)
    {
        return 0.0;
    }

    bool
    PiXtendEIODOInst::di7(void)
    {
        return 0.0;
    }


    // Output Digital

    void
    PiXtendEIODOInst::do0(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do0(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do1(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do1(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do2(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do2(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do3(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do3(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do4(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do4(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do5(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do5(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do6(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do6(void)
    {
        return 0.0;
    }

    void
    PiXtendEIODOInst::do7(bool data)
    {

    }

    bool
    PiXtendEIODOInst::do7(void)
    {
        return 0.0;
    }

}
