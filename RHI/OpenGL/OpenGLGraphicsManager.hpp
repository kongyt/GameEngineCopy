#ifndef __OpenGLGraphicsManager_H__
#define __OpenGLGraphicsManager_H__

#include "GraphicsManager.hpp"

namespace GE{
	
	class OpenGLGraphicsManager : public GraphicsManager
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		
		virtual void Tick();
		
	private:
	
	};
	
}

#endif