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

#ifndef __ObjectServer_ObjectApp_h__
#define __ObjectServer_ObjectApp_h__

#include <unordered_map>
#include <vector>

#include "OpcUaStackCore/Utility/IOThread.h"
#include "OpcUaStackCore/Base/Config.h"

#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaStackServer/Application/ApplicationInfo.h"

#include "OpcUaPiXtendServer/ObjectServer/ObjectsCfg.h"
#include "OpcUaPiXtendServer/ObjectServer/ObjectServer.h"
#include "OpcUaPiXtendServer/PiXtend/ContextIndex.h"

namespace OpcUaPiXtendServer
{

    class ObjectApp
    {
      public:
        ObjectApp(void);
        virtual ~ObjectApp(void);

        bool startup(
            OpcUaStackCore::IOThread::SPtr& ioThread,
            boost::shared_ptr<boost::asio::io_service::strand> strand,
            OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
            OpcUaStackServer::ApplicationInfo* applicationInfo,
            OpcUaStackCore::Config& config,
            ContextIndex::SPtr contextIndex
        );
        bool shutdown(void);

      private:
        OpcUaStackCore::IOThread::SPtr ioThread_ {nullptr};
        boost::shared_ptr<boost::asio::io_service::strand> strand_ {nullptr};

        OpcUaStackServer::ApplicationServiceIf* applicationServiceIf_ {nullptr};
        OpcUaStackServer::ApplicationInfo* applicationInfo_ {nullptr};

        ContextIndex::SPtr contextIndex_ {nullptr};

        bool startupObjectServers(ObjectsCfg& cfg);
        bool shutdownObjectServers(void);

        bool startupServerLoop(void);
        bool shutdownServerLoop(void);
        void serverLoop(void);

        bool createFolderObject(
        	std::string& folderObject,
			OpcUaStackCore::OpcUaNodeId& folderObjectNodeId
		);

        std::vector<ObjectServer::SPtr> objectServers_;
        std::unordered_map<std::string /*folderObject*/, OpcUaStackCore::OpcUaNodeId> folderObjects_;
    };

}

#endif
