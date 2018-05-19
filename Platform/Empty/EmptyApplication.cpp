#include "BaseApplication.hpp"

namespace GE{
	GfxConfiguration config;
	
	BaseApplication g_App(config);
	IApplication* g_pApp = &g_App;
}