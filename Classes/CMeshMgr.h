
#ifndef CMeshMgr_h
#define CMeshMgr_h

#include "IResourceMgr.h"

class CMeshMgr : public IResourceMgr_INTERFACE
{
private:
    
protected:
    
public:
    
    CMeshMgr(void);
    ~CMeshMgr(void);
    
    TSharedPtrResource StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadingCommands* _observer);
};

#endif
