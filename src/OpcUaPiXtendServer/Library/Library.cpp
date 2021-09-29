/*
   Copyright 2015-2021 Kai Huebl (kai@huebl-sgh.de)

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
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaPiXtendServer/Library/Library.h"
#include "OpcUaStackServer/ServiceSetApplication/ApplicationService.h"
#include "OpcUaStackServer/ServiceSetApplication/NodeReferenceApplication.h"
#include <iostream>
#include "BuildConfig.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

	Library::Library(void)
	: ApplicationIf()
	{
	}

	Library::~Library(void)
	{
	}

	bool
	Library::startup(void)
	{
		Log(Debug, "Library::startup");

		// get message bus thread pool and strand. Used to run all asynchronous
		// tasks in the application. The strand is used for synchronization. Only
		// one task is running in the application at a time.
		auto messageBusThread = this->applicationThreadPool();
		auto messageBusStrand = messageBusThread->createStrand();

		// read pixtend configuration file
		ConfigXml configXml;
		Config config;
		if (!configXml.parse(applicationInfo()->configFileName(), &config)) {
			Log(Error, "parse configuration file error")
				.parameter("ConfigFileName", applicationInfo()->configFileName())
				.parameter("Reason", configXml.errorMessage());
			return false;
		}
		boost::optional<Config> piXtendServerConfig = config.getChild("OpcUaPiXtendServer");
		if (!piXtendServerConfig) {
			Log(Error, "missing element OpcUaPiXtendServer in server configuration")
				.parameter("ConfigFileName", applicationInfo()->configFileName());
			return false;
		}

		// startup piXtend application
		auto result = piXtendServer_.startup(
			messageBusThread,
			messageBusStrand,
			&service(),
			applicationInfo(),
			*piXtendServerConfig
		);
		if (!result) {
			Log(Error, "init pixtend server error");
			return false;
		}

		return true;
	}

	bool
	Library::shutdown(void)
	{
		Log(Debug, "Library::shutdown");

		// shutdown piXtend application
		auto result = piXtendServer_.shutdown();
		if (!result) {
			Log(Error, "shutdown pixtend server error");
			return false;
		}

		return true;
	}

	std::string
	Library::version(void)
	{
		std::stringstream version;

		version << LIBRARY_VERSION_MAJOR << "." << LIBRARY_VERSION_MINOR << "." << LIBRARY_VERSION_PATCH;
		return version.str();
	}

	std::string
	Library::gitCommit(void)
	{
		return LIBRARY_GIT_COMMIT;
	}

	std::string
	Library::gitBranch(void)
	{
		return LIBRARY_GIT_BRANCH;
	}

}

extern "C" DLLEXPORT void  init(ApplicationIf** applicationIf) {
    *applicationIf = new OpcUaPiXtendServer::Library();
}

