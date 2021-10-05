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

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2SInst.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2SInst::PiXtendV2SInst(const std::string& name)
    : PiXtendV2S(name)
    {
    }

    PiXtendV2SInst::~PiXtendV2SInst(void)
    {
    }

    // Configuration

    bool
    PiXtendV2SInst::startup(void)
    {
        return true;
    }

    bool
    PiXtendV2SInst::shutdown(void)
    {
        return true;
    }

    // Inputs Analog

    double
    PiXtendV2SInst::ai0(void)
    {
        return 0.0;
    }

    double
    PiXtendV2SInst::ai1(void)
    {
        return 0.0;
    }

    // Output Analog

    void
    PiXtendV2SInst::ao0(double data)
    {

    }

    double
    PiXtendV2SInst::ao0(void)
    {
        return 0.0;
    }

    void
    PiXtendV2SInst::ao1(double data)
    {

    }

    double
    PiXtendV2SInst::ao1(void)
    {
        return 0.0;
    }

    // Inputs Digital

    bool
    PiXtendV2SInst::di0(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di1(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di2(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di3(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di4(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di5(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di6(void)
    {
        return false;
    }

    bool
    PiXtendV2SInst::di7(void)
    {
        return false;
    }

    // Output Digital

    void
    PiXtendV2SInst::do0(bool data)
    {

    }

    bool
    PiXtendV2SInst::do0(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::do1(bool data)
    {

    }

    bool
    PiXtendV2SInst::do1(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::do2(bool data)
    {

    }

    bool
    PiXtendV2SInst::do2(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::do3(bool data)
    {

    }

    bool
    PiXtendV2SInst::do3(void)
    {
        return false;
    }

    // Relay

    void
    PiXtendV2SInst::relay0(bool data)
    {

    }

    bool
    PiXtendV2SInst::relay0(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::relay1(bool data)
    {

    }

    bool
    PiXtendV2SInst::relay1(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::relay2(bool data)
    {

    }

    bool
    PiXtendV2SInst::relay2(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::relay3(bool data)
    {

    }
    bool
    PiXtendV2SInst::relay3(void)
    {
        return false;
    }

    // Input/Output General Purpose

    void
    PiXtendV2SInst::gpio0(bool data)
    {

    }

    bool
    PiXtendV2SInst::gpio0(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::gpio1(bool data)
    {

    }

    bool
    PiXtendV2SInst::gpio1(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::gpio2(bool data)
    {

    }

    bool
    PiXtendV2SInst::gpio2(void)
    {
        return false;
    }

    void
    PiXtendV2SInst::gpio3(bool data)
    {

    }

    bool
    PiXtendV2SInst::gpio3(void)
    {
        return false;
    }

}
