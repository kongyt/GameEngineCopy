#ifndef __GraphicsManager_H__
#define __GraphicsManager_H__

#include "IRuntimeModule.hpp"

namespace GE{
    
    class GraphicsManager : implements IRuntimeModule
    {
    public:
        virtual ~GraphicsManager(){} 

		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
    };    
    
}

#endif