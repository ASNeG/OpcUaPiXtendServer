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
 */

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaPiXtendServer/Library/PiXtendServer.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{



	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// class PiXtendServer
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	PiXtendServer::PiXtendServer(void)
	{
	}

	PiXtendServer::~PiXtendServer(void)
	{
	}

	bool
	PiXtendServer::startup(
		IOThread::SPtr& ioThread,
		boost::shared_ptr<boost::asio::io_service::strand> strand,
		ApplicationServiceIf* applicationServiceIf,
		ApplicationInfo* applicationInfo,
		OpcUaStackCore::Config& config
	)
	{
		Log(Debug, "PiXtendServer::startup");

		ioThread_ = ioThread;
		strand_ = strand;
		applicationServiceIf_ = applicationServiceIf;
		applicationInfo_ = applicationInfo;


		// parse controller configuration
		// FIXME: TBD

		return true;
	}

	bool
	PiXtendServer::shutdown(void)
	{
		Log(Debug, "PiXtendServer::shutdown");

		return true;
	}

}
