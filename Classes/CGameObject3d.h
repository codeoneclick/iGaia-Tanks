//
//  INode.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CGameObject3d_h
#define CGameObject3d_h

#include "HCommon.h"
#include "CRenderMgr.h"
#include "CSceneUpdateMgr.h"
#include "CResourceMgrsFacade.h"
#include "CMaterial.h"
#include "CCamera.h"
#include "CLight.h"

class CGameObject3d :
public CSceneUpdateCallback_INTERFACE,
public CRenderCallback_INTERFACE,
public CResourceLoadCallback_INTERFACE
{
private:

protected:

    glm::mat4x4 m_matrixScale;
    glm::mat4x4 m_matrixRotation;
    glm::mat4x4 m_matrixTranslation;
    glm::mat4x4 m_matrixWorld;
    glm::mat4x4 m_matrixWVP;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    glm::vec2 m_texcoordDisplacement;

    CMaterial* m_materials[E_RENDER_MODE_WORLD_SPACE_MAX];
    CMesh* m_mesh;

    CCamera* m_camera;
    CLight* m_light;

    CRenderMgr* m_renderMgr;
    CSceneUpdateMgr* m_updateMgr;

    virtual void OnResourceDidLoad(IResource_INTERFACE* _resource);

    virtual void OnUpdate(f32 _deltatime);

    virtual ui32 OnDrawIndex(void) = 0;
    virtual void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    virtual void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    virtual void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);

public:
    
    CGameObject3d(void);
    virtual ~CGameObject3d(void);

    inline void Set_Position(const glm::vec3& _position)
    {
        m_position = _position;
    };

    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };

    inline void Set_Rotation(const glm::vec3& _rotation)
    {
        m_rotation = _rotation;
    };

    inline glm::vec3 Get_Rotation(void)
    {
        return m_rotation;
    };

    inline void Set_Scale(const glm::vec3& _scale)
    {
        m_scale = _scale;
    };

    inline glm::vec3 Get_Scale(void)
    {
        return m_scale;
    };

    inline void Set_TexcoordDisplacement(const glm::vec2& _texcoordDisplacement)
    {
        m_texcoordDisplacement = _texcoordDisplacement;
    };

    inline glm::vec2 Get_TexcoordDisplacement(void)
    {
        return m_texcoordDisplacement;
    };

    virtual void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename) = 0;

    glm::vec3 Get_MaxBound(void);
    glm::vec3 Get_MinBound(void);

    inline void Set_Camera(CCamera* _camera)
    {
        m_camera = _camera;
    };
    
    inline void Set_Light(CLight* _light)
    {
        m_light = _light;
    };

    void Set_Texture(CTexture* _texture, E_TEXTURE_SLOT _slot, E_RENDER_MODE_WORLD_SPACE _mode);
    void Set_Clipping(const glm::vec4& _clipping, E_RENDER_MODE_WORLD_SPACE _mode);

    inline void Set_RenderMgr(CRenderMgr* _renderMgr)
    {
        m_renderMgr = _renderMgr;
    };

    inline void Set_UpdateMgr(CSceneUpdateMgr* _updateMgr)
    {
        m_updateMgr = _updateMgr;
    };

    void ListenRenderMgr(bool _value);
    void ListenUpdateMgr(bool _value);
};

#endif










