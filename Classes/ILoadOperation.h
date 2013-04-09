//
//  ILoadOperation.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#ifndef ILoadOperation_h
#define ILoadOperation_h

#include "HCommon.h"
#include "IResource.h"
#include "CResourceLoadCallback.h"

class ILoadOperation_INTERFACE;
typedef std::shared_ptr<ILoadOperation_INTERFACE> TSharedPtrLoadOperation;

class ILoadOperation_INTERFACE
{
private:

protected:

    std::string m_name;
    E_PARSER_STATUS m_status;
    std::set<CResourceLoadCallback*> m_listeners;

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

    inline void Register_ResourceLoadCallback(CResourceLoadCallback* _listener)
    {
        m_listeners.insert(_listener);
    };

    inline void Unregister_ResourceLoadCallback(CResourceLoadCallback* _listener)
    {
        m_listeners.erase(_listener);
    };

	void Execute_ResourceLoadCallbacks(TSharedPtrResource _resource);
};

#endif 
