#ifndef __Interface_H__
#define __Interface_H__

#define Interface class
#define implements public

namespace GE{
	Interface IRuntimeModule{
		public:
		virtual ~IRuntimeModule(){};
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		
		virtual void Tick() = 0;
	};
	
}

#endif