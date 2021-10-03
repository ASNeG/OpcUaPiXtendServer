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

#ifndef __OpcUaPiXtendServer_NodeContextAnalogIO_h__
#define __OpcUaPiXtendServer_NodeContextAnalogIO_h__

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "OpcUaPiXtendServer/OpcUaServer/NodeContext.h"

namespace OpcUaPiXtendServer
{

    class NodeContextAnalogIO
	: public NodeContext
    {
      public:

    	using SPtr = boost::shared_ptr<NodeContextAnalogIO>;
       	using ReadFunc = boost::function<double (void)>;
        using WriteFunc = boost::function<void (double)>;

        NodeContextAnalogIO(void);
        virtual ~NodeContextAnalogIO(void);

        bool existReadFunc(void);
        void setReadFunc(ReadFunc readFunc);
        void unsetReadFunc(void);
        ReadFunc getReadFunc(void);

        bool existWriteFunc(void);
        void setWriteFunc(WriteFunc writeFunc);
        void unsetWriteFunc(void);
        WriteFunc getWriteFunc(void);

      private:
        std::pair<bool, ReadFunc> readFunc_;
        std::pair<bool, WriteFunc> writeFunc_;
    };

}

#endif
