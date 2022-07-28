/*
   Copyright 2021-2022 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaPiXtendServer_PiXtendBaseServer_h__
#define __OpcUaPiXtendServer_PiXtendBaseServer_h__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaStackServer/StandardObjectType/ObjectBase.h"
#include "OpcUaPiXtendServer/PiXtend/ContextIndex.h"
#include "OpcUaPiXtendServer/OpcUaServer/UnitConverterContext.h"

namespace OpcUaPiXtendServer
{

	class NodePinConfig {
	  public:
		using Vec = std::vector<NodePinConfig>;

        NodePinConfig(std::string nodeName, std::string pinName,
                      std::string instanceName = "",
                      OpcUaStackCore::OpcUaVariant::SPtr value = nullptr)
        : nodeName_(nodeName)
        , pinName_(pinName)
        , instanceName_(instanceName)
        , value_(value)
        {
        }
        ~NodePinConfig(void) = default;

        std::string nodeName_;
        std::string pinName_;
        std::string instanceName_;
        OpcUaStackCore::OpcUaVariant::SPtr value_;
	};

    class PiXtendBaseServer
    : public OpcUaStackServer::ObjectBase
	, public boost::enable_shared_from_this<PiXtendBaseServer>
    {
      public:

    	using SPtr = boost::shared_ptr<PiXtendBaseServer>;

        PiXtendBaseServer(
        	const std::string& typeName,
            const std::string& namespaceName,
			uint32_t typeNodeId
		);
        virtual ~PiXtendBaseServer(void);

        bool startup(
        	OpcUaStackCore::IOThread::SPtr& ioThread,
        	boost::shared_ptr<boost::asio::io_service::strand>& strand,
        	OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
            const std::string& instanceName,
			const OpcUaStackCore::OpcUaNodeId& parentNodeId,
            ContextIndex::SPtr& contextIndex,
            const UnitConverterContext::Map& unitConverterContextMap
		);
        bool shutdown(void);

      protected:
        std::string typeName_ = "";
        uint32_t typeNodeId_ = 0;
        OpcUaStackServer::ApplicationServiceIf* applicationServiceIf_ = nullptr;
        std::string namespaceName_ = "";
        uint16_t namespaceIndex_ = 0;
        std::string instanceName_ = "";
        OpcUaStackCore::OpcUaNodeId parentNodeId_;
        ContextIndex::SPtr contextIndex_;

        NodePinConfig::Vec nodePinConfigVec_;

        virtual bool handleStartup(void) = 0;
        virtual bool handleShutdown(void) = 0;

      private:
        OpcUaStackCore::IOThread::SPtr ioThread_;
        boost::shared_ptr<boost::asio::io_service::strand> strand_;

        bool createObjectInstance(void);

        bool createNodeContext(
            const NodePinConfig::Vec& nodePinConfigVec,
			const UnitConverterContext::Map& unitConverterContextMap
		);

        bool registerServiceFunctions(void);

        // opc ua service function
        void readValue(
        	OpcUaStackCore::ApplicationReadContext* applicationReadContext
		);
        void writeValue(
        	OpcUaStackCore::ApplicationWriteContext* applicationWriteContext
		);
		void receiveMonotoredItemStart(
			OpcUaStackCore::ApplicationMonitoredItemStartContext* monitoredItemStartContext
		);
		void receiveMonitoredItemStop(
			OpcUaStackCore::ApplicationMonitoredItemStopContext* monitoredItemStopContext
		);

        bool findNamespace(void);
    };

}

#endif
