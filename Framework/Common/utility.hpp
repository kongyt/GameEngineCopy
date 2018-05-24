#ifndef __Utility_H__
#define __Utility_H__

namespace GE{
    
    template<class T>
    inline void SafeRelease(T** ppInterfaceToRelease)
    {
        if(*ppInterfaceToRelease != nullptr)
        {
            (*ppInterfaceToRelease)->Release();
            (*ppInterfaceToRelease) = nullptr;
        }
    }
    
}

#endif