#include "BaseApplication.hpp"
#include <iostream>

using namespace GE;

bool GE::BaseApplication::m_bQuit = false;

GE::BaseApplication::BaseApplication(GfxConfiguration& cfg)
	:m_Config(cfg)
{
	
}

// Parse command line, read configuration, initialize all sub modules
int GE::BaseApplication::Initialize()
{
	std::cout << m_Config;
	
	return 0;	
}


// Finalize all sub modules and clean up all runtime temporary files.
void GE::BaseApplication::Finalize()
{
		
}


// One cycle of the main loop
void GE::BaseApplication::Tick()
{
	
	
}

bool GE::BaseApplication::IsQuit()
{
	return m_bQuit;	
}