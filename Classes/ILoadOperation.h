
#ifndef ILoadOperation_h
#define ILoadOperation_h

#include "HCommon.h"
#include "IResource.h"
#include "CResourceLoading_INTERFACE.h"

class ILoadOperation_INTERFACE;
typedef std::shared_ptr<ILoadOperation_INTERFACE> TSharedPtrLoadOperation;

class ILoadOperation_INTERFACE
{
private:

protected:

    std::string m_name;
    E_PARSER_STATUS m_status;
    std::set<CResourceLoadingCommands*> m_observers;

    void _Register(IResource_INTERFACE* _resource);

public:
    
    ILoadOperation_INTERFACE(void);
    virtual ~ILoadOperation_INTERFACE(void) {};

    virtual void Load(const std::string& _filename) = 0;
    virtual IResource_INTERFACE* Link(void) = 0;

    inline E_PARSER_STATUS Get_Status(void)
    {
        return m_status;
    };

    inline void Register_ResourceLoadingObserver(CResourceLoadingCommands* _observer)
    {
        m_observers.insert(_observer);
    };

    inline void Unregister_ResourceLoadingObserver(CResourceLoadingCommands* _observer)
    {
        m_observers.erase(_observer);
    };

	void Notify_ResourceLoadingObservers(TSharedPtrResource _resource);
};

#endif 
