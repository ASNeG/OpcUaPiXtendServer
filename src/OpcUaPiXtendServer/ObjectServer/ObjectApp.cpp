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

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Log.h"

#include "OpcUaStackServer/ServiceSetApplication/GetNamespaceInfo.h"
#include "OpcUaStackServer/ServiceSetApplication/CreateNodeInstance.h"

#include "OpcUaPiXtendServer/ObjectServer/ObjectApp.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    ObjectApp::ObjectApp(void)
    {
    }

    ObjectApp::~ObjectApp(void)
    {
    }

    bool
    ObjectApp::startup(
        IOThread::SPtr& ioThread,
        boost::shared_ptr<boost::asio::io_service::strand> strand,
        ApplicationServiceIf* applicationServiceIf,
        ApplicationInfo* applicationInfo,
        Config& config,
        ContextIndex::SPtr contextIndex
    )
    {
        Log(Debug, "ObjectApp::startup");

        ioThread_ = ioThread;
        strand_ = strand;
        applicationServiceIf_ = applicationServiceIf;
        applicationInfo_ = applicationInfo;
        contextIndex_ = contextIndex;

        ObjectsCfg objectsCfg;
        if (!objectsCfg.parse(&config)) {
            Log(Error, "parse objects configuration error")
                .parameter("File", config.configFileName());
            return false;
        }

        // startup server
        Log(Debug, "startup object servers");
        if (!startupObjectServers(objectsCfg)) {
            Log(Error, "startup object servers error");
            return false;
        }

        return true;
    }

    bool
    ObjectApp::shutdown(void)
    {
        Log(Debug, "ObjectApp::shutdown");

        // shutdown object servers
        Log(Debug, "shutdown object servers");
        shutdownObjectServers();

        return true;
    }

    bool
    ObjectApp::startupObjectServers(ObjectsCfg& cfg)
    {
        for (auto objectCfgSPtr: cfg.configObjectCfgs()) {
            if (objectCfgSPtr == nullptr) {
                continue;
            }

            OpcUaNodeId objectFolderNodeId;
            if (!createFolderObject(objectCfgSPtr->folderObject(), objectFolderNodeId)) {
                Log(Error, "object server cannot create folder object!")
                    .parameter("Name", objectCfgSPtr->name());
                continue;
            }

            UnitConverterContext::Map unitConverterContextMap;
            for (auto unitConv : objectCfgSPtr->unitConversionConfigMap()) {
                unitConverterContextMap.insert(std::make_pair(
                    unitConv.first,
                    boost::make_shared<UnitConverterContext>(
                        unitConv.second->a(),
                        unitConv.second->b(),
                        unitConv.second->c(),
                        unitConv.second->d()
                    )
                ));
            }

            ObjectServer::SPtr objectServerSPtr = boost::make_shared<ObjectServer>(objectCfgSPtr);
            if (!objectServerSPtr->startup(
                        ioThread_,
                        strand_,
                        applicationServiceIf_,
                        objectCfgSPtr->name(),
                        objectFolderNodeId,
                        contextIndex_,
                        unitConverterContextMap
                    )) {
                Log(Error, "object server cannot startup!")
                    .parameter("Name", objectCfgSPtr->name());
                continue;
            }

            objectServers_.push_back(objectServerSPtr);
        }

        return true;
    }

    bool
    ObjectApp::shutdownObjectServers(void)
    {
        // shutdown object servers
        for (auto objectServer: objectServers_) {
            objectServer->shutdown();
            objectServer.reset();
        }
        objectServers_.clear();

        return true;
    }

    bool
    ObjectApp::createFolderObject(std::string& folderObject, OpcUaNodeId& folderObjectNodeId)
    {
        auto findObjectFolderNodeId = folderObjects_.find(folderObject);
        if (findObjectFolderNodeId != folderObjects_.end()) {
            folderObjectNodeId = findObjectFolderNodeId->second;
            return true;
        }
        folderObjectNodeId = OpcUaNodeId(folderObject);
        folderObjects_.insert(std::make_pair(folderObject, folderObjectNodeId));

        // create pixtend root object
        CreateNodeInstance createNodeInstance(
            folderObject,                              // name
            NodeClass::EnumObject,                     // node class
            OpcUaNodeId(OpcUaId_ObjectsFolder),        // parent node id (Objects)
            folderObjectNodeId,                        // node id
            OpcUaLocalizedText("en", folderObject),    // dispplay name
            OpcUaQualifiedName(folderObject, 1),       // browse name
            OpcUaNodeId(OpcUaId_HasComponent),         // reference type id
            OpcUaNodeId(OpcUaId_BaseObjectType)        // type node id
        );

        if (!createNodeInstance.query(applicationServiceIf_)) {
            return false;
        }

        return true;
    }

}
