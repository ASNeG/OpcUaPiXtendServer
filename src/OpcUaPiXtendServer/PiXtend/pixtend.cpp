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
   Autor: Samuel Huebl (Samuel@huebl-sgh.de)

   Usage:
   pixtend <Module> <Pin> <Operation>

   	   Module:		[V2L | V2S | DO | AO]
   	   Pin:			D0, ...
   	   Operation:	read |
   	   				write [<D-Value> | A-Value]
   	   D-Value:		on | off
   	   A-Value:		double

 */

#include <boost/program_options.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <memory>

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendV2SDummy.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendV2SInst.h"

using namespace OpcUaPiXtendServer;

int main(int argc, char** argv)
{

    // initialize configuration modules

    std::shared_ptr<PiXtendV2S> pixtendV2SSPtr = nullptr;
#ifdef OPCUAPIXTENDSERVER_V2S_MODUL
    pixtendV2SSPtr = std::make_shared<PiXtendV2SInst>();
#else
    pixtendV2SSPtr = std::make_shared<PiXtendV2SDummy>();
#endif

	// FIXME: adjustments for pixtend tool

#if 0

	std::string in{""};
	std::string out{""};
	std::string addressString{""};
	uint16_t address;
	bool verbose = false;

	// set command line options
	boost::program_options::options_description desc{std::string(argv[0])};
	desc.add_options()
		("help,h", "produce help message")
		("in,i", boost::program_options::value<std::string>()->required(), "name of input hex file")
		("out,o", boost::program_options::value<std::string>()->required(), "name of output binary file")
		("address,a", boost::program_options::value<std::string>()->required(), "address offset")
		("verbose,v", "output of infos")
	;

	// parse commend line options
	boost::program_options::variables_map vm;
	try
	{
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm
		);

		// handle help option
		if (vm.count("help")) {
		    std::cout << desc << "\n";
		    return 1;
		}

		boost::program_options::notify(vm);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	in = vm["in"].as<std::string>();
	out = vm["out"].as<std::string>();
	addressString = vm["address"].as<std::string>();
	if (vm.count("verbose")) {
		verbose = true;
	}

	// read hex file
	HexFile hexFile;
	hexFile.verbose(verbose);
	if (!hexFile.readHexFile(in)) {
		return 1;
	}

	// get pointer to binary data
	std::stringstream ss;
	ss << addressString;
	ss >> std::hex >> address;

	uint8_t* memBuf;
	uint32_t memLen;
	if (!hexFile.getSegment(address, &memBuf, &memLen)) {
		std::cout << "Error: segment data not found (" << addressString << ")" << std::endl;
		return 1;
	}

	// open binary file
	boost::filesystem::ofstream binFile(out);

	// write binary file
	for (uint32_t idx = 0; idx < memLen; idx++) {
		binFile << std::setfill('0') << std::setw(2) << std::hex << (uint32_t)memBuf[idx];
		if ((idx+1) % 32 == 0) binFile << std::endl;
	}

	// close binary file
	binFile.close();
#endif

	return 0;
}
