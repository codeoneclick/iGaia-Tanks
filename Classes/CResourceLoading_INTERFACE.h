
#ifndef CResourceLoading_INTERFACE_h
#define CResourceLoading_INTERFACE_h

#include "HCommon.h"

extern "C" class IResource_INTERFACE;
typedef std::shared_ptr<IResource_INTERFACE> TSharedPtrResource;

typedef std::function<void(TSharedPtrResource _resource)> __ON_RESOURCE_DID_LOAD_CALLBACK;

class CResourceLoadingCommands final
{
private:

    friend class CResourceLoading_INTERFACE;
    
    __ON_RESOURCE_DID_LOAD_CALLBACK m_onResourceDidLoadCallback;

protected:
    
    CResourceLoadingCommands(void) {};

    void Register_OnResourceLoadCallback(const __ON_RESOURCE_DID_LOAD_CALLBACK& _listener);
    
public:
    
    ~CResourceLoadingCommands(void) {};

    void Execute_OnResourceDidLoadCallback(TSharedPtrResource _resource);
};

class CResourceLoading_INTERFACE
{
private:

    CResourceLoadingCommands m_commands;
    void RegisterCommands(void);
    
protected:

    CResourceLoading_INTERFACE(void);

    virtual void OnResourceDidLoad(TSharedPtrResource _resource) = 0;
    
public:

    virtual ~CResourceLoading_INTERFACE(void) {};

    inline CResourceLoadingCommands* Get_Commands(void)
    {
		return &m_commands;
    };
};

#endif 
