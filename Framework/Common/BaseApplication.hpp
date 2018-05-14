#ifndef __BaseApplication_H__
#define __BaseApplication_H__

#include "IApplication.hpp"

namespace GE{
	class BaseApplication : implements IApplication
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		
		virtual void Tick();
		virtual bool IsQuit();		
		
	protected:
		// Flag if need quit the main loop of the application
		bool m_bQuit;
	};
	
}

#endif