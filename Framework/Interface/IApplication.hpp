#ifndef __IApplication_H__
#define __IApplication_H__

#include "Interface.hpp"
#include "IRuntimeModule.hpp"
#include "GfxConfiguration.h"

namespace GE{
	
	Interface IApplication : implements IRuntimeModule
	{
	public:
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		
		virtual void Tick() = 0;
		
		virtual bool IsQuit() = 0;		
		
		virtual GfxConfiguration& GetConfiguration() = 0;
	};
	
}


#endif