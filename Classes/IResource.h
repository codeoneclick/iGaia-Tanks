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

class IResource_INTERFACE
{
private:

    friend class ILoadOperation_INTERFACE;

protected:

    std::string m_name;
    ui32 m_referencesCount;
    E_RESOURCE_TYPE m_resourceType;
    
public:
    
    IResource_INTERFACE(void);
    virtual ~IResource_INTERFACE(void);

    inline std::string Get_Name(void)
    {
        assert(m_name.length() != 0);
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
};

#endif
