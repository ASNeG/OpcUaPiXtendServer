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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/ServiceSetApplication/CreateObjectInstance.h"
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIODOServer.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    PiXtendEIODOServer::PiXtendEIODOServer(void)
    {
        ServerVariable::SPtr serverVariable;

        // register digital input variables
        serverVariable = boost::make_shared<ServerVariable>("DI_DI0_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI1_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI2_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI3_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI4_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI5_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI6_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI7_Variable");
        serverVariables().registerServerVariable(serverVariable);

        // register digital output variables
        serverVariable = boost::make_shared<ServerVariable>("DO_DO0_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO1_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO2_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO3_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO4_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO5_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO6_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO7_Variable");
        serverVariables().registerServerVariable(serverVariable);

    }

    PiXtendEIODOServer::~PiXtendEIODOServer(void)
    {
    }

    bool
	PiXtendEIODOServer::startup(
	    OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
	    const std::string& instanceName,
	    const std::string& namespaceName,
	    uint16_t namespaceIndex,
	    const OpcUaStackCore::OpcUaNodeId& parentNodeId,
	    uint32_t moduleAddress
	)
    {
        applicationServiceIf_ = applicationServiceIf;
        instanceName_ = instanceName;
        namespaceName_ = namespaceName;
        namespaceIndex_ = namespaceIndex;
        parentNodeId_ = parentNodeId;

    	// get pixtend eIO DO access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendEIODO();

    	// startup pixtend interface
    	pixtend_->startup(moduleAddress);

        // create object instance in information model
        if (!createObjectInstance()) {
            return false;
        }

    	return true;
    }

    bool
	PiXtendEIODOServer::shutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();

    	// FIXME: TBD

    	return true;
    }

    bool
    PiXtendEIODOServer::createObjectInstance(void)
    {
        //
        // create EIODO object instance in opc ua information model
        //
        objectTypeNamespaceName(namespaceName_);
        objectTypeNodeId(OpcUaNodeId(1004, namespaceIndex_));
        Object::SPtr obj = shared_from_this();
        CreateObjectInstance createObjectInstance(
            namespaceName_,                                 // namespace name of the object instance
            OpcUaLocalizedText("", instanceName_),          // display name of the object instance
            parentNodeId_,                                  // parent node of the object instance
            OpcUaNodeId(OpcUaId_Organizes),                 // reference type between object and variable instance
            obj
        );
        if (!createObjectInstance.query(applicationServiceIf_)) {
            Log(Error, "create PiXtendEIODO object response error (query)");
            return false;
        }
        if (createObjectInstance.resultCode() != Success) {
            Log(Error, "create PiXtendEIODO object response error (result code)")
                .parameter("ResultCode", createObjectInstance.resultCode());
            return false;
        }

        return true;
    }

}
