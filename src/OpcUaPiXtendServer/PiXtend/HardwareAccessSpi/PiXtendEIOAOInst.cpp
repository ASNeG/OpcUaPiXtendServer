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

#include "OpcUaPiXtendServer/PiXtend/HardwareAccessSpi/PiXtendEIOAOInst.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIOAOInst::PiXtendEIOAOInst(const std::string& instanceName)
    : PiXtendEIOAO(instanceName)
    {
    }

    PiXtendEIOAOInst::~PiXtendEIOAOInst(void)
    {
    }

    // Configuration

    bool
    PiXtendEIOAOInst::startup(uint32_t moduleAddress)
    {
        return true;
    }

    bool
    PiXtendEIOAOInst::shutdown(void)
    {
        return true;
    }

    void
	PiXtendEIOAOInst::handleHardwareAccess(void)
    {
    	// FIXME: TBD
    }

    // Inputs Analog

    double
    PiXtendEIOAOInst::ai0(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai1(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai2(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai3(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai4(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai5(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai6(void)
    {
        return 0.0;
    }

    double
    PiXtendEIOAOInst::ai7(void)
    {
        return 0.0;
    }


    // Output Analog

    void
    PiXtendEIOAOInst::ao0(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao0(void)
    {
        return 0.0;
    }

    void
    PiXtendEIOAOInst::ao1(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao1(void)
    {
        return 0.0;
    }

    void
    PiXtendEIOAOInst::ao2(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao2(void)
    {
        return 0.0;
    }

    void
    PiXtendEIOAOInst::ao3(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao3(void)
    {
        return 0.0;
    }

    void
    PiXtendEIOAOInst::ao4(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao4(void)
    {
        return 0.0;
    }

    void
    PiXtendEIOAOInst::ao5(double data)
    {

    }

    double
    PiXtendEIOAOInst::ao5(void)
    {
        return 0.0;
    }

}
