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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2LInst.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2LInst::PiXtendV2LInst(const std::string& instanceName)
    : PiXtendV2L(instanceName)
    {
    }

    PiXtendV2LInst::~PiXtendV2LInst(void)
    {
    }

    // Configuration

    bool
    PiXtendV2LInst::startup(void)
    {
        return true;
    }

    bool
    PiXtendV2LInst::shutdown(void)
    {
        return true;
    }

    void
 	PiXtendV2LInst::handleHardwareAccess(void)
    {
        // FIXME: TBD
    }

    // Inputs Analog

    double
    PiXtendV2LInst::ai0(void)
    {
        return 0.0;
    }

    double
    PiXtendV2LInst::ai1(void)
    {
        return 0.0;
    }

    double
    PiXtendV2LInst::ai2(void)
    {
        return 0.0;
    }

    double
    PiXtendV2LInst::ai3(void)
    {
        return 0.0;
    }

    double
    PiXtendV2LInst::ai4(void)
    {
        return 0.0;
    }

    double
    PiXtendV2LInst::ai5(void)
    {
        return 0.0;
    }


    // Output Analog

    void
    PiXtendV2LInst::ao0(double data)
    {
    	std::cout << "set ao0" << std::endl;
    	testValue = data;
    }

    double
    PiXtendV2LInst::ao0(void)
    {
    	std::cout << "get ao0" << std::endl;
        return testValue;
    }

    void
    PiXtendV2LInst::ao1(double data)
    {

    }

    double
    PiXtendV2LInst::ao1(void)
    {
        return 0.0;
    }

    // Inputs Digital

    bool
    PiXtendV2LInst::di0(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di1(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di2(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di3(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di4(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di5(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di6(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di7(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di8(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di9(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di10(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di11(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di12(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di13(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di14(void)
    {
        return false;
    }

    bool
    PiXtendV2LInst::di15(void)
    {
        return false;
    }


    // Output Digital

    void
    PiXtendV2LInst::do0(bool data)
    {

    }

    bool
    PiXtendV2LInst::do0(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do1(bool data)
    {

    }

    bool
    PiXtendV2LInst::do1(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do2(bool data)
    {

    }

    bool
    PiXtendV2LInst::do2(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do3(bool data)
    {

    }

    bool
    PiXtendV2LInst::do3(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do4(bool data)
    {

    }

    bool
    PiXtendV2LInst::do4(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do5(bool data)
    {

    }

    bool
    PiXtendV2LInst::do5(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do6(bool data)
    {

    }

    bool
    PiXtendV2LInst::do6(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do7(bool data)
    {

    }

    bool
    PiXtendV2LInst::do7(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do8(bool data)
    {

    }

    bool
    PiXtendV2LInst::do8(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do9(bool data)
    {

    }

    bool
    PiXtendV2LInst::do9(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do10(bool data)
    {

    }

    bool
    PiXtendV2LInst::do10(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::do11(bool data)
    {

    }

    bool
    PiXtendV2LInst::do11(void)
    {
        return false;
    }

    // Relay

    void
    PiXtendV2LInst::relay0(bool data)
    {

    }

    bool
    PiXtendV2LInst::relay0(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::relay1(bool data)
    {

    }

    bool
    PiXtendV2LInst::relay1(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::relay2(bool data)
    {

    }

    bool
    PiXtendV2LInst::relay2(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::relay3(bool data)
    {

    }
    bool
    PiXtendV2LInst::relay3(void)
    {
        return false;
    }

    // Input/Output General Purpose

    void
    PiXtendV2LInst::gpio0(bool data)
    {

    }

    bool
    PiXtendV2LInst::gpio0(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::gpio1(bool data)
    {

    }

    bool
    PiXtendV2LInst::gpio1(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::gpio2(bool data)
    {

    }

    bool
    PiXtendV2LInst::gpio2(void)
    {
        return false;
    }

    void
    PiXtendV2LInst::gpio3(bool data)
    {

    }

    bool
    PiXtendV2LInst::gpio3(void)
    {
        return false;
    }

}
