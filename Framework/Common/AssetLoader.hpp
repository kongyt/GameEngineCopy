#ifndef __AssetLoader_H__
#define __AssetLoader_H__

#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include "IRuntimeModule.hpp"
#include "Buffer.hpp"

namespace GE{
    class AssetLoader : public IRuntimeModule{
    public:
        virtual ~AssetLoader(){};
        
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
        
        typedef void* AssetFilePtr;
        
        enum AssetOpenMode{
            OPEN_TEXT   = 0,    // open in text mode
            OPEN_BINARY = 1,    // open in binary mode            
        };
        
        enum AssetSeekBase{
            SEEK_SET    = 0,    // SEEK_SET
            SEEK_CUR    = 1,    // SEEK_CUR
            SEEK_END    = 2,    // SEEK_END
        };
        
        bool AddSearchPath(const char* path);
        
        bool RemoveSearchPath(const char* path);
        
        bool FileExists(const char* filePath);
        
        AssetFilePtr OpenFile(const char* name, AssetOpenMode mode);
        
        Buffer SyncOpenAndReadText(const char* filePath);
        
        size_t SyncRead(const AssetFilePtr& fp, Buffer& buf);
        
        void CloseFile(AssetFilePtr& fp);
        
        size_t GetSize(const AssetFilePtr& fp);
        
        int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);
        
        inline std::string SyncOpenAndReadTextFileToString(const char* fileName)
        {
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            char* content = reinterpret_cast<char*>(buffer.m_pData);
            
            if(content){
                result = std::string(std::move(content));
            }
            
            return result;
        }
        
    private:
        std::vector<std::string> m_strSearchPath;
    };
    
}

#endif