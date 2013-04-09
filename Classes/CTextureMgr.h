
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
    
    TSharedPtrResource StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadingCommands* _observer);
};


#endif
