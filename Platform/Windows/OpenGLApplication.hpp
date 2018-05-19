#ifndef __OpenGLApplication_H__
#define __OpenGLApplication_H__

#include "WindowsApplication.hpp"

namespace GE{
	
	class OpenGLApplication : public WindowsApplication{
	public:
		OpenGLApplication(GfxConfiguration& config)
			: WindowsApplication(config){};
			
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		
	private:
		HGLRC m_RenderContext;
		
	};
	
}

#endif