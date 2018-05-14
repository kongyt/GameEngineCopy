#ifndef __IApplication_H__
#define __IApplication_H__

#include "Interface.hpp"

namespace GE{
	
	Interface IApplication : implements IRuntimeModule
	{
	public:
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		
		virtual void Tick() = 0;
		
		virtual bool IsQuit() = 0;		
	};
	
}


#endif