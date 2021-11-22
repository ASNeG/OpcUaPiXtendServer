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

#include "OpcUaPiXtendServer/ObjectServer/ObjectServer.h"

namespace OpcUaPiXtendServer
{

    ObjectServer::ObjectServer(ObjectCfg::SPtr objectCfgSPtr)
    : PiXtendBaseServer(objectCfgSPtr->name(), objectCfgSPtr->namespaceName(), objectCfgSPtr->type())
    , objectCfgSPtr_(objectCfgSPtr)
    {
    }

    ObjectServer::~ObjectServer(void)
    {
    }

    bool
    ObjectServer::handleStartup(void)
    {
        for (auto& nodeMapCfg: objectCfgSPtr_->nodeMapCfgs())
        {
            if (nodeMapCfg == nullptr) {
                continue;
            }

            nodePinConfigVec_.push_back( {nodeMapCfg->nodeName(),
                                          nodeMapCfg->pinName(),
                                          nodeMapCfg->pinInstanceName(),
                                          nodeMapCfg->value()} );
        }

        return true;
    }

    bool
    ObjectServer::handleShutdown(void)
    {
        return true;
    }
}
