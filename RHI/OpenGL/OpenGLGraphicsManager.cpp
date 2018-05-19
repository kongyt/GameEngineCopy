#include <stdio.h>
#include "glad/glad.h"
#include "OpenGLGraphicsManager.hpp"

using namespace GE;

extern struct gladGLversionStruct GLVersion;

int GE::OpenGLGraphicsManager::Initialize()
{
	int result;
	
	result = gladLoadGL();
	if(!result){
		printf("OpenGL load failed!\n");
		result = -1;		
	}else{
		result = 0;
		printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);
		
		if(GLAD_GL_VERSION_3_0){
			// set the depth buffer to be entirely cleared to 1.0 values.
			glClearDepth(1.0f);
			
			// enable depth testing.
			glEnable(GL_DEPTH_TEST);
			
			// set the polygon winding to front facing for the left handed system.
			glFrontFace(GL_CW);
			
			// enable back face culling.
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
	}
	
	return result;
}

void GE::OpenGLGraphicsManager::Finalize()
{
	
}

void GE::OpenGLGraphicsManager::Tick()
{
	
}
