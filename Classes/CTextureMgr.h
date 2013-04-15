
#ifndef CTextureMgr_h
#define CTextureMgr_h

#include "IResourceMgr.h"

class CTextureMgr : public IResourceMgr_INTERFACE
{
private:

protected:
    
public:
    
    CTextureMgr(void);
    ~CTextureMgr(void);
    
    TSharedPtrResource Execute_LoadingOperationSynchronous(const std::string& _filename);
    void Execute_LoadingOperationAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands);
};


#endif
