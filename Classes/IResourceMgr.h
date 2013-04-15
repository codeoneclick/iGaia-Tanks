
#ifndef IResourceMgr_h
#define IResourceMgr_h

#include "HCommon.h"
#include "IResource.h"
#include "ILoadOperation.h"
#include "CResourceLoading_INTERFACE.h"

class IResourceMgr_INTERFACE
{
private:
    
protected:
    
    std::unordered_map<std::string, TSharedPtrResource> m_resources;
    std::unordered_map<std::string, TSharedPtrLoadOperation> m_operationsQueue;
    
    typedef std::unordered_map<std::string, TSharedPtrResource>::iterator TResourceIterator;
    typedef std::unordered_map<std::string, TSharedPtrLoadOperation>::iterator TOperationIterator;

    std::mutex m_mutex;
    std::thread m_thread;
    bool m_isThreadRunning;

    void Execute_CallbackCommands(const CResourceLoadingCommands* _commands, TSharedPtrResource _resource);
    
public:
    
    IResourceMgr_INTERFACE(void);
    virtual ~IResourceMgr_INTERFACE(void);
    
    virtual void Update(void);
    virtual void Thread(void);
    
    virtual TSharedPtrResource Execute_LoadingOperationSynchronous(const std::string& _filename) = 0;
    virtual void Execute_LoadingOperationAsynchronous(const std::string& _filename, const CResourceLoadingCommands* _commands) = 0;
    void Cancel_LoadingOperation(const CResourceLoadingCommands* _commands);
	void Unload_Resource(TSharedPtrResource _resource);
};


#endif
