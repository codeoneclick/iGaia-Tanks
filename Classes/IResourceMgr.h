
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

	std::map<std::string, TSharedPtrLoadOperation> m_operationsQueue;
    std::map<std::string, TSharedPtrResource> m_resourceContainer;

    std::mutex m_mutex;
    std::thread m_thread;

    void Notify_ResourceLoadingObserver(CResourceLoadingCommands* _observer, TSharedPtrResource _resource);
    
public:
    
    IResourceMgr_INTERFACE(void);
    virtual ~IResourceMgr_INTERFACE(void);
    
    virtual void Update(void);
    virtual void Thread(void);

    virtual TSharedPtrResource StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadingCommands* _observer) = 0;
    void CancelLoadOperation(CResourceLoadingCommands* _observer);
	void UnloadResource(TSharedPtrResource resource);
};


#endif
