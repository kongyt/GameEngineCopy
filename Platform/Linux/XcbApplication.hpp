#ifndef __XcbApplication_H__
#define __XcbApplication_H__

#include <xcb/xcb.h>

namespace GE{
	class XcbApplication : public BaseApplication
	{
	public:
		XcbApplication(GfxConfiguration& config)
			:BaseApplication(config){};
			
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
	
	protected:
		xcb_connection_t*	m_pConn		= nullptr;
		xcb_screen_t*		m_pScreen	= nullptr;
		xcb_window_t		m_Window;
		uint32_t			m_nVi		= 0;	
	};
}

#endif