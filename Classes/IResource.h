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

class IResource_INTERFACE;
typedef std::shared_ptr<IResource_INTERFACE> TSharedPtrResource;

class IResource_INTERFACE
{
private:

    friend class ILoadOperation_INTERFACE;

protected:

    std::string m_name;
    bool m_isLinked;
    E_RESOURCE_TYPE m_resourceType;
    
public:
    
    IResource_INTERFACE(E_RESOURCE_TYPE _resourceType);
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
    
    inline bool isLinked(void)
    {
        return !m_isLinked;
    };
};

#endif
