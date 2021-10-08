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

#include "OpcUaPiXtendServer/PiXtend/HardwareAccessSpi/PiXtendV2LInst.h"
#include "OpcUaStackCore/Base/Log.h"

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
        resetSpiInputData(spiInputData_);
        resetSpiOutputData(spiOutputData_);
        resetSpiOutputDataDac(spiOutputDataDac_);

        //Configure SPI
        Spi_SetupV2(0); // communication with microcontroller
        Spi_SetupV2(1); // communication with DAC (analog inputs/outputs)

        // read first time - configuration
        int32_t trxValue = Spi_AutoModeV2L(&spiOutputData_, &spiInputData_);
        Spi_AutoModeDAC(&spiOutputDataDac_);

        if (!spiHelper_.checkTrxValue(trxValue))
        {
            OpcUaStackCore::Log(OpcUaStackCore::Error,
                "transaction error in module v2l");
            return false;
        }

        if (spiInputData_.byModelIn != model_)
        {
            OpcUaStackCore::Log(OpcUaStackCore::Error,
                "receive undefined model in module v2l")
                .parameter("expected model", model_)
                .parameter("received model", spiInputData_.byModelIn);
            return false;
        }

        if (spiInputData_.byHardware != hardware_)
        {
            OpcUaStackCore::Log(OpcUaStackCore::Error,
                "different hardware versions in module v2l")
                .parameter("expected hardware", hardware_)
                .parameter("received hardware", spiInputData_.byHardware);
            return false;
        }

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
        // transfer data
        int32_t trxValue = Spi_AutoModeV2L(&spiOutputData_, &spiInputData_);
        Spi_AutoModeDAC(&spiOutputDataDac_);

        // check transaction value
        if (!spiHelper_.checkTrxValue(trxValue))
        {
            OpcUaStackCore::Log(OpcUaStackCore::Error,
                "transaction error in module v2l");
        }

        // cycle time in <ms>
        delay(delayTime_);
    }

    // Status information

    uint8_t
    PiXtendV2LInst::firmware(void)
    {
        return spiInputData_.byFirmware;
    }

    uint8_t
    PiXtendV2LInst::hardware(void)
    {
        return spiInputData_.byHardware;
    }

    uint8_t
    PiXtendV2LInst::model(void)
    {
        return spiInputData_.byModelIn;
    }

    uint8_t
    PiXtendV2LInst::ucStatus(void)
    {
        return spiInputData_.byUCState;
    }

    uint8_t
    PiXtendV2LInst::ucWarning(void)
    {
        return spiInputData_.byUCWarnings;
    }

    // Inputs Analog

    double
    PiXtendV2LInst::ai0(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn0);
    }

    double
    PiXtendV2LInst::ai1(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn1);
    }

    double
    PiXtendV2LInst::ai2(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn2);
    }

    double
    PiXtendV2LInst::ai3(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn3);
    }

    double
    PiXtendV2LInst::ai4(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn4);
    }

    double
    PiXtendV2LInst::ai5(void)
    {
        return spiHelper_.analog2Percent(spiInputData_.wAnalogIn5);
    }

    // Output Analog

    void
    PiXtendV2LInst::ao0(double data)
    {
        spiOutputDataDac_.wAOut0 = spiHelper_.percent2Analog(data);
    }

    double
    PiXtendV2LInst::ao0(void)
    {
        return spiHelper_.analog2Percent(spiOutputDataDac_.wAOut0);
    }

    void
    PiXtendV2LInst::ao1(double data)
    {
        spiOutputDataDac_.wAOut1 = spiHelper_.percent2Analog(data);
    }

    double
    PiXtendV2LInst::ao1(void)
    {
        return spiHelper_.analog2Percent(spiOutputDataDac_.wAOut1);
    }

    // Inputs Digital

    bool
    PiXtendV2LInst::di0(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 0);
    }

    bool
    PiXtendV2LInst::di1(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 1);
    }

    bool
    PiXtendV2LInst::di2(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 2);
    }

    bool
    PiXtendV2LInst::di3(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 3);
    }

    bool
    PiXtendV2LInst::di4(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 4);
    }

    bool
    PiXtendV2LInst::di5(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 5);
    }

    bool
    PiXtendV2LInst::di6(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 6);
    }

    bool
    PiXtendV2LInst::di7(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn0, 7);
    }

    bool
    PiXtendV2LInst::di8(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 0);
    }

    bool
    PiXtendV2LInst::di9(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 1);
    }

    bool
    PiXtendV2LInst::di10(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 2);
    }

    bool
    PiXtendV2LInst::di11(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 3);
    }

    bool
    PiXtendV2LInst::di12(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 4);
    }

    bool
    PiXtendV2LInst::di13(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 5);
    }

    bool
    PiXtendV2LInst::di14(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 6);
    }

    bool
    PiXtendV2LInst::di15(void)
    {
        return spiHelper_.bit2Bool(spiInputData_.byDigitalIn1, 7);
    }

    // Output Digital

    void
    PiXtendV2LInst::do0(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 0);
    }

    bool
    PiXtendV2LInst::do0(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 0);
    }

    void
    PiXtendV2LInst::do1(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 1);
    }

    bool
    PiXtendV2LInst::do1(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 1);
    }

    void
    PiXtendV2LInst::do2(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 2);
    }

    bool
    PiXtendV2LInst::do2(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 2);
    }

    void
    PiXtendV2LInst::do3(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 3);
    }

    bool
    PiXtendV2LInst::do3(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 3);
    }

    void
    PiXtendV2LInst::do4(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 4);
    }

    bool
    PiXtendV2LInst::do4(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 4);
    }

    void
    PiXtendV2LInst::do5(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 5);
    }

    bool
    PiXtendV2LInst::do5(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 5);
    }

    void
    PiXtendV2LInst::do6(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 6);
    }

    bool
    PiXtendV2LInst::do6(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 6);
    }

    void
    PiXtendV2LInst::do7(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut0, bit, 7);
    }

    bool
    PiXtendV2LInst::do7(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut0, 7);
    }

    void
    PiXtendV2LInst::do8(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut1, bit, 0);
    }

    bool
    PiXtendV2LInst::do8(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut1, 0);
    }

    void
    PiXtendV2LInst::do9(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut1, bit, 1);
    }

    bool
    PiXtendV2LInst::do9(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut1, 1);
    }

    void
    PiXtendV2LInst::do10(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut1, bit, 2);
    }

    bool
    PiXtendV2LInst::do10(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut1, 2);
    }

    void
    PiXtendV2LInst::do11(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byDigitalOut1, bit, 3);
    }

    bool
    PiXtendV2LInst::do11(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byDigitalOut1, 3);
    }

    // Relay

    void
    PiXtendV2LInst::relay0(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byRelayOut, bit, 0);
    }

    bool
    PiXtendV2LInst::relay0(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byRelayOut, 0);
    }

    void
    PiXtendV2LInst::relay1(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byRelayOut, bit, 1);
    }

    bool
    PiXtendV2LInst::relay1(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byRelayOut, 1);
    }

    void
    PiXtendV2LInst::relay2(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byRelayOut, bit, 2);
    }

    bool
    PiXtendV2LInst::relay2(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byRelayOut, 2);
    }

    void
    PiXtendV2LInst::relay3(bool data)
    {
        uint8_t bit = (data) ? 0x1 : 0x0;
        spiHelper_.changeBit(spiOutputData_.byRelayOut, bit, 3);
    }

    bool
    PiXtendV2LInst::relay3(void)
    {
        return spiHelper_.bit2Bool(spiOutputData_.byRelayOut, 3);
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

    void
    PiXtendV2LInst::resetSpiInputData(PiXtendSpiInputData& spiInputData)
    {
        spiInputData.byFirmware = 0;
        spiInputData.byHardware = 0;
        spiInputData.byModelIn = 0;
        spiInputData.byUCState = 0;
        spiInputData.byUCWarnings = 0;
        spiInputData.byDigitalIn0 = 0;
        spiInputData.byDigitalIn1 = 0;
        spiInputData.wAnalogIn0 = 0;
        spiInputData.wAnalogIn1 = 0;
        spiInputData.wAnalogIn2 = 0;
        spiInputData.wAnalogIn3 = 0;
        spiInputData.wAnalogIn4 = 0;
        spiInputData.wAnalogIn5 = 0;
        spiInputData.byGPIOIn = 0;
        spiInputData.wTemp0 = 0;
        spiInputData.byTemp0Error = 0;
        spiInputData.wTemp1 = 0;
        spiInputData.byTemp1Error = 0;
        spiInputData.wTemp2 = 0;
        spiInputData.byTemp2Error = 0;
        spiInputData.wTemp3 = 0;
        spiInputData.byTemp3Error = 0;
        spiInputData.wHumid0 = 0;
        spiInputData.wHumid1 = 0;
        spiInputData.wHumid2 = 0;
        spiInputData.wHumid3 = 0;
        spiInputData.rAnalogIn0 = 0.0;
        spiInputData.rAnalogIn1 = 0.0;
        spiInputData.rAnalogIn2 = 0.0;
        spiInputData.rAnalogIn3 = 0.0;
        spiInputData.rAnalogIn4 = 0.0;
        spiInputData.rAnalogIn5 = 0.0;
        spiInputData.rTemp0 = 0.0;
        spiInputData.rTemp1 = 0.0;
        spiInputData.rTemp2 = 0.0;
        spiInputData.rTemp3 = 0.0;
        spiInputData.rHumid0 = 0.0;
        spiInputData.rHumid1 = 0.0;
        spiInputData.rHumid2 = 0.0;
        spiInputData.rHumid3 = 0.0;
        memset(spiInputData.abyRetainDataIn, 0, sizeof(spiInputData.abyRetainDataIn));
    }

    void
    PiXtendV2LInst::resetSpiOutputData(PiXtendSpiOutputData& spiOutputData)
    {
        spiOutputData.byModelOut = model_;
        spiOutputData.byUCMode = 0;
        spiOutputData.byUCCtrl0 = 0;
        spiOutputData.byUCCtrl1 = 0;
        spiOutputData.byDigitalInDebounce01 = 0;
        spiOutputData.byDigitalInDebounce23 = 0;
        spiOutputData.byDigitalInDebounce45 = 0;
        spiOutputData.byDigitalInDebounce67 = 0;
        spiOutputData.byDigitalInDebounce89 = 0;
        spiOutputData.byDigitalInDebounce1011 = 0;
        spiOutputData.byDigitalInDebounce1213 = 0;
        spiOutputData.byDigitalInDebounce1415 = 0;
        spiOutputData.byDigitalOut0 = 0;
        spiOutputData.byDigitalOut1 = 0;
        spiOutputData.byRelayOut = 0;
        spiOutputData.byGPIOCtrl = 0;
        spiOutputData.byGPIOOut = 0;
        spiOutputData.byGPIODebounce01 = 0;
        spiOutputData.byGPIODebounce23 = 0;
        spiOutputData.byPWM0Ctrl0 = 0;
        spiOutputData.wPWM0Ctrl1 = 0;
        spiOutputData.wPWM0A = 0;
        spiOutputData.wPWM0B = 0;
        spiOutputData.byPWM1Ctrl0 = 0;
        spiOutputData.wPWM1Ctrl1 = 0;
        spiOutputData.wPWM1A = 0;
        spiOutputData.wPWM1B = 0;
        spiOutputData.byPWM2Ctrl0 = 0;
        spiOutputData.wPWM2Ctrl1 = 0;
        spiOutputData.wPWM2A = 0;
        spiOutputData.wPWM2B = 0;
        spiOutputData.byJumper10V = 0;
        spiOutputData.byGPIO0Dht11 = 0;
        spiOutputData.byGPIO1Dht11 = 0;
        spiOutputData.byGPIO2Dht11 = 0;
        spiOutputData.byGPIO3Dht11 = 0;
        memset(spiOutputData.abyRetainDataOut, 0, sizeof(spiOutputData.abyRetainDataOut));
    }

    void
    PiXtendV2LInst::resetSpiOutputDataDac(PiXtendSpiOutputDataDac& spiOutputDataDac)
    {
        spiOutputDataDac.wAOut0 = 0;
        spiOutputDataDac.wAOut1 = 0;
    }

}
