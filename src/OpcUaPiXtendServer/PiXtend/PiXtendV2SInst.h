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

#ifndef __OpcUaPiXtendServer_PiXtendV2SInst_h__
#define __OpcUaPiXtendServer_PiXtendV2SInst_h__

#include "OpcUaPiXtendServer/PiXtend/PiXtendV2S.h"

namespace OpcUaPiXtendServer
{

	class PiXtendV2SInst
	: public PiXtendV2S
	{
	  public:
		PiXtendV2SInst(void);
		~PiXtendV2SInst(void);

		void d0(bool data) override;
	    bool d0(void) override;

		// FIXME: TBD
	};

}

#endif
