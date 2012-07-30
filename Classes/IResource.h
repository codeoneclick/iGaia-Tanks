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
#include "IDelegate.h"

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class IResource
{
public:
    enum E_CREATION_MODE { E_CREATION_MODE_NATIVE = 0, E_CREATION_MODE_CUSTOM }; 
#define STANDART_MODEL "STANDART_MODEL"
    enum E_STANDART_MODEL { E_STANDART_MODEL_NONE = 0, E_STANDART_MODEL_PLANE, E_STANDART_MODEL_CUBE }; 
    enum E_MGR { E_MGR_TEXTURE = 0,  E_MGR_MESH };
    enum E_THREAD { E_THREAD_MAIN = 0, E_THREAD_BACKGROUND };
    
    enum E_SHADER { E_SHADER_LANDSCAPE = 0, E_SHADER_LANDSCAPE_ND, E_SHADER_MODEL, E_SHADER_MODEL_ND, E_SHADER_GRASS, E_SHADER_GRASS_ND, E_SHADER_OCEAN, E_SHADER_DECAL, E_SHADER_PARTICLE, E_SHADER_PARTICLE_ND, E_SHADER_SKYBOX, E_SHADER_SCREEN_PLANE, E_SHADER_SCREEN_PLANE_BLOOM_EXTRACT, E_SHADER_SCREEN_PLANE_BLOOM_COMBINE, E_SHADER_SCREEN_PLANE_BLUR, E_SHADER_SCREEN_PLANE_EDGE_DETECT, E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL };
    
    /*{ E_SHADER_COLOR = 0, E_SHADER_TEXTURE, E_SHADER_BLOOM_EXTRACT, E_SHADER_BLUR, E_SHADER_BLOOM_COMBINE, E_SHADER_EDGE_DETECT, E_SHADER_LANDSCAPE,  E_SHADER_UNIT, E_SHADER_NORMAL_DEPTH, E_SHADER_PROJECT_TEXTURE, E_SHADER_WATER, E_SHADER_PRE_NORMAL_DEPTH_UNIT, E_SHADER_ANIM_TEXCOORD_UNIT, E_SHADER_SHADOW_MAP, E_SHADER_TEXTURE_CUBE, E_SHADER_SHADOW_PLANE, E_SHADER_DECAL, E_SHADER_GRASS, E_SHADER_PARTICLE_EMITTER, E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER };*/
    
    enum E_RESOURCE_TYPE { E_RESOURCE_TYPE_NONE = 0, E_RESOURCE_TYPE_TEXTURE, E_RESOURCE_TYPE_MESH, E_RESOURCE_TYPE_SHADER };
protected:
    int m_iRefCount;
    std::string m_sName;
    E_RESOURCE_TYPE m_eResourceType;
    std::vector<IDelegate*> m_lDelegateOwners;
    E_CREATION_MODE m_eCreationMode;
public:
    IResource(void);
    virtual ~IResource(void);
    virtual void Release(void);
    inline void IncRefCount(void) { m_iRefCount++; }
    inline void DecRefCount(void) { m_iRefCount--; }
    inline int  Get_RefCount(void) { return m_iRefCount; }
    inline void Set_Name(const std::string& _sName) { m_sName = _sName; }
    inline std::string Get_Name(void) { return m_sName; }
    virtual void Set_SourceData(void* _pSourceData) = 0;
    inline E_RESOURCE_TYPE Get_ResourceType(void) { return m_eResourceType; }
    inline E_CREATION_MODE Get_CreationMode(void) { return m_eCreationMode; }

    void Add_DelegateOwner(IDelegate* _pDelegateOwner);
    void Remove_DelegateOnwer(IDelegate* _pDelegateOwner);

    void Push_SignalToDelegateOwners(void);
};


#endif
