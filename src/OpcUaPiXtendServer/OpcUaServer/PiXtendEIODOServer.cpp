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

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendEIODOServer.h"

namespace OpcUaPiXtendServer
{

    PiXtendEIODOServer::PiXtendEIODOServer(void)
    {
    }

    PiXtendEIODOServer::~PiXtendEIODOServer(void)
    {
    }

    bool
	PiXtendEIODOServer::startup(
		const std::string& instanceName,
		const OpcUaStackCore::OpcUaNodeId& parentNodeId
	)
    {
        uint32_t moduleAddress = 0;

    	// get pixtend v2s access interface
    	pixtend_ = PiXtendModulesFactory::createPiXtendEIODO();

    	// startup pixtend interface
    	pixtend_->startup(moduleAddress);

    	// FIXME: TBD

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

}
