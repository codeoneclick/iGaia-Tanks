//
//  IResource.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IResource_h
#define iGaia_IResource_h

#include "stdlib.h"

#include <string>
#include <vector>


#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class IResource
{
public:
    enum E_CREATION_MODE
    {
        E_CREATION_MODE_NATIVE = 0,
        E_CREATION_MODE_CUSTOM
    };

    enum E_MGR
    {
        E_MGR_TEXTURE = 0,
        E_MGR_MESH
    };
    
    enum E_THREAD
    {
        E_THREAD_SYNC = 0,
        E_THREAD_ASYNC
    };
    
    enum E_RESOURCE_TYPE
    {
        E_RESOURCE_TYPE_NONE = 0,
        E_RESOURCE_TYPE_TEXTURE,
        E_RESOURCE_TYPE_MESH,
        E_RESOURCE_TYPE_SHADER
    };
    
protected:
    int m_referenceCount;
    std::string m_name;
    E_RESOURCE_TYPE m_resourceType;
    E_CREATION_MODE m_creationMode;
public:
    IResource(void);
    virtual ~IResource(void);
    inline void IncReferenceCount(void)
    {
        m_referenceCount++;
    }
    inline void DecReferenceCount(void)
    {
        m_referenceCount--;
    }
    inline int Get_ReferenceCount(void)
    {
        return m_referenceCount;
    }
    inline void Set_Name(const std::string& _name)
    {
        m_name = _name;
    }
    inline std::string Get_Name(void)
    {
        return m_name;
    }
    inline E_RESOURCE_TYPE Get_ResourceType(void)
    {
        return m_resourceType;
    }
    inline E_CREATION_MODE Get_CreationMode(void)
    {
        return m_creationMode;
    }
    
    virtual void PutInstance(IResource* _resource) = 0;
};


#endif
