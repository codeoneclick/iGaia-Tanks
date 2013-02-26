//
//  IResource.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef IResource_h
#define IResource_h

#include "HCommon.h"
#include "CResourceLoadCallback.h"

class IResource
{
private:
    
protected:

    std::string m_name;
    ui32 m_referencesCount;
    E_RESOURCE_TYPE m_resourceType;
    std::set<CResourceLoadCallback*> m_listeners;
    
public:
    
    IResource(void);
    virtual ~IResource(void);

    inline std::string Get_Name(void)
    {
        return m_name;
    };

    inline E_RESOURCE_TYPE Get_ResourceType(void)
    {
        return m_resourceType;
    };

    inline void IncReferencesCount(void)
    {
        m_referencesCount++;
    };

    inline void DecReferencesCount(void)
    {
        m_referencesCount--;
    };

    inline ui32 Get_ReferencesCount(void)
    {
        return m_referencesCount;
    };

    inline void AddLoadingListener(CResourceLoadCallback* _listener)
    {
        m_listeners.insert(_listener);
    };

    inline void RemoveLoadingListener(CResourceLoadCallback* _listener)
    {
        m_listeners.erase(_listener);
    };

    void NotifyLoadingListeners(void);
};

#endif
