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
#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2LServer.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaPiXtendServer
{

    PiXtendV2LServer::PiXtendV2LServer(void)
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
        serverVariable = boost::make_shared<ServerVariable>("DI_DI8_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI9_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI10_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI11_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI12_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI13_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI14_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DI_DI15_Variable");
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
        serverVariable = boost::make_shared<ServerVariable>("DO_DO8_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO9_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO10_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("DO_DO11_Variable");
        serverVariables().registerServerVariable(serverVariable);

        // register relay variables
        serverVariable = boost::make_shared<ServerVariable>("RELAY_RELAY0_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("RELAY_RELAY1_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("RELAY_RELAY2_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("RELAY_RELAY3_Variable");
        serverVariables().registerServerVariable(serverVariable);

        // register analog input variables
        serverVariable = boost::make_shared<ServerVariable>("AI_AI0_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AI_AI1_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AI_AI2_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AI_AI3_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AI_AI4_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AI_AI5_Variable");
        serverVariables().registerServerVariable(serverVariable);

        // register analog output variables
        serverVariable = boost::make_shared<ServerVariable>("AO_AO0_Variable");
        serverVariables().registerServerVariable(serverVariable);
        serverVariable = boost::make_shared<ServerVariable>("AO_AO1_Variable");
        serverVariables().registerServerVariable(serverVariable);
    }

    PiXtendV2LServer::~PiXtendV2LServer(void)
    {
    }

    bool
    PiXtendV2LServer::startup(
        OpcUaStackServer::ApplicationServiceIf* applicationServiceIf,
        const std::string& instanceName,
        const std::string& namespaceName,
        uint16_t namespaceIndex,
        const OpcUaStackCore::OpcUaNodeId& parentNodeId
    )
    {
        applicationServiceIf_ = applicationServiceIf;
        instanceName_ = instanceName;
        namespaceName_ = namespaceName;
        namespaceIndex_ = namespaceIndex;
        parentNodeId_ = parentNodeId;

        // get pixtend v2l access interface
        pixtend_ = PiXtendModulesFactory::createPiXtendV2L();

        // startup pixtend interface
        pixtend_->startup();

        // create object instance in information model
        if (!createObjectInstance()) {
            return false;
        }

        return true;
    }

    bool
	PiXtendV2LServer::shutdown(void)
    {
    	// shutdown pixtend interface
    	pixtend_->shutdown();

    	// FIXME: TBD

    	return true;
    }

    bool
    PiXtendV2LServer::createObjectInstance(void)
    {
        //
        // create V2L object instance in opc ua information model
        //
        objectTypeNamespaceName(namespaceName_);
        objectTypeNodeId(OpcUaNodeId(1003, namespaceIndex_));
        Object::SPtr obj = shared_from_this();
        CreateObjectInstance createObjectInstance(
            namespaceName_,                                 // namespace name of the object instance
            OpcUaLocalizedText("", instanceName_),          // display name of the object instance
            parentNodeId_,                                  // parent node of the object instance
            OpcUaNodeId(OpcUaId_Organizes),                 // reference type between object and variable instance
            obj
        );
        if (!createObjectInstance.query(applicationServiceIf_)) {
            Log(Error, "create PiXtendV2L object response error (query)");
            return false;
        }
        if (createObjectInstance.resultCode() != Success) {
            Log(Error, "create PiXtendV2L object response error (result code)")
                .parameter("ResultCode", createObjectInstance.resultCode());
            return false;
        }

        return true;
    }

}
