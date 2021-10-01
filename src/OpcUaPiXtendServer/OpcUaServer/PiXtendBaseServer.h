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

#ifndef __OpcUaPiXtendServer_PiXtendBaseServer_h__
#define __OpcUaPiXtendServer_PiXtendBaseServer_h__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackServer/Application/ApplicationIf.h"
#include "OpcUaStackServer/StandardObjectType/ObjectBase.h"
#include "OpcUaPiXtendServer/OpcUaServer/NodeContextDigitalIO.h"

#define BASE_DO_RF(CLASS, PIN) boost::bind(static_cast<bool (CLASS::*)(void)>(&CLASS::PIN) , pixtend_.get())
#define BASE_DO_WF(CLASS, PIN) boost::bind(static_cast<void (CLASS::*)(bool)>(&CLASS::PIN) , pixtend_.get(), _1)

namespace OpcUaPiXtendServer
{

	class DOConfig {
	  public:
		using Vec = std::vector<DOConfig>;

       	std::string nodeName_;
		NodeContextDigitalIO::ReadFunc readFunc_;
		NodeContextDigitalIO::WriteFunc writeFunc_;
	};

    class PiXtendBaseServer
    : public OpcUaStackServer::ObjectBase
	, public boost::enable_shared_from_this<PiXtendBaseServer>
    {
      public:

    	using SPtr = boost::shared_ptr<PiXtendBaseServer>;

        PiXtendBaseServer(
        	const std::string& typeName,
			uint32_t typeNodeId
		);
        virtual ~PiXtendBaseServer(void);

        bool startup(
        	OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
            const std::string& instanceName,
			const std::string& namespaceName,
			uint16_t namespaceIndex,
			const OpcUaStackCore::OpcUaNodeId& parentNodeId
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

        DOConfig::Vec dOConfigVec_;

        virtual bool handleStartup(void) = 0;
        virtual bool handleShutdown(void) = 0;

        bool createObjectInstance(void);

        bool createNodeContext(
        	const DOConfig::Vec& d0configVec
		);
        bool createNodeContextDigitalIO(
        	OpcUaStackServer::ServerVariable::SPtr& serverVariable,
        	const std::string& nodeName,
			NodeContextDigitalIO::ReadFunc readFunc,
			NodeContextDigitalIO::WriteFunc writeFunc
		);

      private:
    };

}

#endif
