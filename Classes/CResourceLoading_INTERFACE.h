
#ifndef CResourceLoading_INTERFACE_h
#define CResourceLoading_INTERFACE_h

#include "HCommon.h"

extern "C" class IResource_INTERFACE;
typedef std::shared_ptr<IResource_INTERFACE> TSharedPtrResource;

typedef std::function<void(TSharedPtrResource _resource)> __ON_RESOURCE_LOADED_CALLBACK;

class CResourceLoadingCommands final
{
private:

    friend class CResourceLoading_INTERFACE;
    
    __ON_RESOURCE_LOADED_CALLBACK m_onResourceLoadedCallback;

protected:
    
    CResourceLoadingCommands(void) {};

    void Register_OnResourceLoadedCallback(const __ON_RESOURCE_LOADED_CALLBACK& _listener);
    
public:
    
    ~CResourceLoadingCommands(void) {};

    void Execute_OnResourceLoadedCallback(TSharedPtrResource _resource) const;
};

class CResourceLoading_INTERFACE
{
private:

    CResourceLoadingCommands m_resourceLoadingCommands;
    void RegisterResourceLoadingCommands(void);
    
protected:

    CResourceLoading_INTERFACE(void);

    virtual void OnResourceLoaded(TSharedPtrResource _resource) = 0;
    
public:

    virtual ~CResourceLoading_INTERFACE(void) {};

    inline const CResourceLoadingCommands* Get_ResourceLoadingCommands(void)
    {
		return &m_resourceLoadingCommands;
    };
};

#endif 
