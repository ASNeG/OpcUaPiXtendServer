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

#ifndef __OpcUaPiXtendServer_PiXtendBase_h__
#define __OpcUaPiXtendServer_PiXtendBase_h__

#include <boost/shared_ptr.hpp>
#include <string>
#include <functional>

#include "OpcUaPiXtendServer/PiXtend/ContextIndex.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendDigitalValueContext.h"
#include "OpcUaPiXtendServer/PiXtend/PiXtendAnalogValueContext.h"

#define PIXTEND_BASE_A_RF(CLASS, PIN) boost::bind(static_cast<double (CLASS::*)(void)>(&CLASS::PIN), this)
#define PIXTEND_BASE_D_RF(CLASS, PIN) boost::bind(static_cast<bool (CLASS::*)(void)>(&CLASS::PIN), this)
#define PIXTEND_BASE_A_WF(CLASS, PIN) boost::bind(static_cast<void (CLASS::*)(double)>(&CLASS::PIN), this, _1)
#define PIXTEND_BASE_D_WF(CLASS, PIN) boost::bind(static_cast<void (CLASS::*)(bool)>(&CLASS::PIN), this, _1)

#define PIXTEND_BASE_AI(CLASS, PIN) PiXtendAnalogValueContext::createContext( \
		    PIXTEND_BASE_A_RF(CLASS, PIN), \
			nullptr, \
			nullptr, \
			nullptr \
		)
#define PIXTEND_BASE_AO(CLASS, PIN) PiXtendAnalogValueContext::createContext( \
		    PIXTEND_BASE_A_RF(CLASS, PIN), \
			PIXTEND_BASE_A_WF(CLASS, PIN), \
			nullptr, \
			nullptr \
		)
#define PIXTEND_BASE_DI(CLASS, PIN) PiXtendDigitalValueContext::createContext( \
		    PIXTEND_BASE_D_RF(CLASS, PIN), \
			nullptr, \
			nullptr, \
			nullptr \
		)
#define PIXTEND_BASE_DO(CLASS, PIN) PiXtendDigitalValueContext::createContext( \
		    PIXTEND_BASE_D_RF(CLASS, PIN), \
			PIXTEND_BASE_D_WF(CLASS, PIN), \
			nullptr, \
			nullptr \
		)

namespace OpcUaPiXtendServer
{

    class PiXtendBase
    {
      public:
    	using SPtr = boost::shared_ptr<PiXtendBase>;
    	using CfgElement = std::pair<std::string, PiXtendValueContext::SPtr>;
    	using CfgElementVec = std::vector<CfgElement>;

        PiXtendBase(const std::string& instanceName);
        virtual ~PiXtendBase(void);

        void loop(void);

        void contextIndex(ContextIndex::SPtr& contextIndex);
        ContextIndex::SPtr contextIndex(void);
        std::string instanceName(void);
        bool registerContext(
        	const std::string& contextName,
			PiXtendValueContext::SPtr& piXtendValueContext
        );
        bool registerContext(const CfgElementVec& cfgElementVec);

        virtual void handleHardwareAccess(void) {};
        virtual void handleRegisterContext(void) = 0;

      private:
        ContextIndex::SPtr contextIndex_ {nullptr};
        std::string instanceName_ = "";
        PiXtendValueContext::Vec piXtendValueContextVec_;
    };

}

#endif
