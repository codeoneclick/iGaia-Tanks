
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
    
    TSharedPtrResource Execute_LoadingOperationSynchronous(const std::string& _filename);
    void Execute_LoadingOperationAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands);
};

#endif
