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

#include "OpcUaPiXtendServer/ModuleUSB/PiXtendEIODOUSBInst.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaPiXtendServer
{

    PiXtendEIODOUSBInst::PiXtendEIODOUSBInst(const std::string& instanceName)
    : PiXtendEIODO(instanceName)
    {
    }

    PiXtendEIODOUSBInst::~PiXtendEIODOUSBInst(void)
    {
    }

    // Configuration

    bool
    PiXtendEIODOUSBInst::startup(uint32_t moduleAddress)
    {
        return true;
    }

    bool
    PiXtendEIODOUSBInst::shutdown(void)
    {
        return true;
    }

    void
 	PiXtendEIODOUSBInst::handleHardwareAccess(void)
    {

    }

    // Inputs Digital

    bool
    PiXtendEIODOUSBInst::di0(void)
    {
        return true;
    }

    bool
    PiXtendEIODOUSBInst::di1(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di2(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di3(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di4(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di5(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di6(void)
    {
    	return true;
    }

    bool
    PiXtendEIODOUSBInst::di7(void)
    {
    	return true;
    }

    // Output Digital

    void
    PiXtendEIODOUSBInst::do0(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do0(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do1(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do1(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do2(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do2(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do3(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do3(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do4(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do4(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do5(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do5(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do6(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do6(void)
    {
        return true;
    }

    void
    PiXtendEIODOUSBInst::do7(bool data)
    {
    }

    bool
    PiXtendEIODOUSBInst::do7(void)
    {
        return true;
    }

}
