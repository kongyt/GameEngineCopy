#include "BaseApplication.hpp"


// Parse command line, read configuration, initialize all sub modules
int GE::BaseApplication::Initialize()
{
	m_bQuit = false;
	
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