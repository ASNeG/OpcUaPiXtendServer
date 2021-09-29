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

#include "OpcUaPiXtendServer/OpcUaServer/PiXtendV2SServer.h"

namespace OpcUaPiXtendServer
{

    PiXtendV2SServer::PiXtendV2SServer(void)
    {
    }

    PiXtendV2SServer::~PiXtendV2SServer(void)
    {
    }

    bool
	PiXtendV2SServer::startup(
		const std::string& instanceName,
		const OpcUaStackCore::OpcUaNodeId& parentNodeId
	)
    {
    	// get pixtend v2s access interface
    	PiXtendModules piXtendModules;
    	pixtend_ = piXtendModules.getPiXtendV2S();

    	// startup pixtend interface
    	// pixtend_.startup();

    	// FIXME: TBD

    	return true;
    }

    bool
	PiXtendV2SServer::shutdown(void)
    {
    	// shutdown pixtend interface
    	// pixtend_.shutdown();

    	// FIXME: TBD
    	return true;
    }

}
