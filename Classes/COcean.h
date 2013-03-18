//
//  CWater.h
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef COcean_h
#define COcean_h

#include "CGameObject3d.h"

class COcean: public CGameObject3d
{
private:
    
    CTexture* m_reflectionTexture;
    CTexture* m_refractionTexture;
    CTexture* m_heightmapTexture;
    f32 m_width;
    f32 m_height;
    f32 m_altitude;
    f32 m_waveGeneratorTimer;
    f32 m_waveGeneratorInterval;
    
protected:

    void OnResourceDidLoad(IResource_INTERFACE* _resource);

    void OnUpdate(f32 _deltatime);

    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);
    
public:
    
    COcean(void);
    ~COcean(void);

    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename);

    inline void Set_ReflectionTexture(CTexture* _texture)
    {
        assert(m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON] != nullptr);
        m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON]->Set_Texture(_texture, E_TEXTURE_SLOT_02);
    }
    
    inline void Set_RefractionTexture(CTexture* _texture)
    {
        assert(m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON] != nullptr);
        m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON]->Set_Texture(_texture, E_TEXTURE_SLOT_03);
    }
    
    inline void Set_HeightmapTexture(CTexture* _texture)
    {
        assert(m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON] != nullptr);
        m_materials[E_RENDER_MODE_WORLD_SPACE_COMMON]->Set_Texture(_texture, E_TEXTURE_SLOT_04);
    }

    inline f32 Get_Altitude(void)
    {
        return m_altitude;
    }
};

#endif
