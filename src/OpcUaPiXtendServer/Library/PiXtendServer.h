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

#ifndef __OpcUaPiXtendServer_PiXtendServer_h__
#define __OpcUaPiXtendServer_PiXtendServer_h__

#include <unordered_map>
#include "OpcUaStackCore/Utility/IOThread.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaStackServer/Application/ApplicationInfo.h"

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2SServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2LServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIODOServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIOAOServer.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendServerControllerCfg.h"

namespace OpcUaPiXtendServer
{

	class PiXtendServer
	{
	  public:

		PiXtendServer(void);
		virtual ~PiXtendServer(void);

		bool startup(
			OpcUaStackCore::IOThread::SPtr& ioThread,
			boost::shared_ptr<boost::asio::io_service::strand> strand,
			OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
			OpcUaStackServer::ApplicationInfo* applicationInfo,
			OpcUaStackCore::Config& config
		);
		bool shutdown(void);

	  private:
		OpcUaStackCore::IOThread::SPtr ioThread_ = nullptr;
		boost::shared_ptr<boost::asio::io_service::strand> strand_ = nullptr;

		OpcUaStackServer::ApplicationServiceIf* applicationServiceIf_ = nullptr;
		OpcUaStackServer::ApplicationInfo* applicationInfo_ = nullptr;

		const std::string namespaceName_ = "http://ASNeG.de/PiXtend/";
        uint16_t namespaceIndex_ = 0;
		const OpcUaStackCore::OpcUaNodeId piXtendRootNodeId_ = OpcUaStackCore::OpcUaNodeId("PiXtend", 1);

		ContextIndex::SPtr contextIndex_ = boost::make_shared<ContextIndex>();

		bool findNamespace(void);
		bool createPiXtendRootObject(void);

		bool startupPiXtend(PiXtendServerControllerCfg& cfg);

        bool createSeverModuleV2S(std::string name);
        bool createServerModuleV2L(std::string name);
        bool createServerModuleEIOAO(std::string name, uint32_t address);
        bool createServerModuleEIODO(std::string name, uint32_t address);

        PiXtendV2S::SPtr piXtendV2S_ {nullptr};

        PiXtendV2SServer::SPtr piXtendV2SServer_ {nullptr};
        PiXtendV2LServer::SPtr piXtendV2LServer_ {nullptr};
        std::unordered_map<uint32_t /*address*/, PiXtendEIOAOServer::SPtr> piXtendEIOAOServerMap_;
        std::unordered_map<uint32_t /*address*/, PiXtendEIODOServer::SPtr> piXtendEIODOServerMap_;
	};

}

#endif
