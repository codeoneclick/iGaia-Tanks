//
//  INode.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_INode_h
#define iGaia_INode_h

#include "CCommon.h"

#include "CMaterial.h"
#include "CMesh.h"
#include "CBoundingBox.h"
#include "ILight.h"

#include "CResourceMgr.h"
#include "CShaderComposite.h"

#include "CMathHelper.h"

class INode
{
protected:
    
    glm::mat4x4 m_scaleMatrix;
    glm::mat4x4 m_rotationMatrix;
    glm::mat4x4 m_translationMatrix;
    glm::mat4x4 m_worldMatrix;
    glm::mat4x4 m_worldViewProjectionMatrix;
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    
    glm::vec2 m_texcoordOffset;
    
    CMaterial* m_material;
    CMesh* m_mesh;
    
    bool m_visible;
    
public:
    INode(void);
    virtual ~INode(void);
    
    virtual void Load(const std::string& _name, IResource::E_THREAD _thread = IResource::E_THREAD_SYNC) = 0;
    
    virtual void Update(void);
    
    virtual void Render(unsigned int _renderMode);
    
    inline CMesh* Get_Mesh(void)
    {
        return m_mesh;
    }
    
    void Set_Texture(CTexture* _texture, int _index, CTexture::E_WRAP_MODE _wrap);
    void Set_Texture(const std::string &_name, int _index, CTexture::E_WRAP_MODE _wrap, IResource::E_THREAD _thread = IResource::E_THREAD_SYNC);
    void Set_Shader(unsigned int _renderMode, CShader::E_SHADER _shader);

    glm::vec3 Get_MaxBound(void);
    glm::vec3 Get_MinBound(void);
    
    inline void Set_Position(const glm::vec3& _position)
    {
        m_position = _position;
    }
    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    }
    inline void Set_Rotation(const glm::vec3& _rotation)
    {
        m_rotation = _rotation;
        m_rotation.x = CMathHelper::Get_WrapAngle(m_rotation.x, 0.0f, 360.0f);
        m_rotation.y = CMathHelper::Get_WrapAngle(m_rotation.y, 0.0f, 360.0f);
        m_rotation.z = CMathHelper::Get_WrapAngle(m_rotation.z, 0.0f, 360.0f);
    }
    inline glm::vec3 Get_Rotation(void)
    {
        return m_rotation;
    }
    inline void Set_Scale(const glm::vec3& _scale)
    {
        m_scale = _scale;
    }
    inline glm::vec3 Get_Scale(void)
    {
        return m_scale;
    }
    
    inline void Set_TexCoordOffset(glm::vec2 _texcoordOffset)
    {
        m_texcoordOffset = _texcoordOffset;
    }
    inline glm::vec2 Get_TexCoordOffset(void)
    {
        return m_texcoordOffset;
    }

    void BindRenderMode(unsigned int _renderMode, bool _value);
    bool CheckRenderMode(unsigned int _renderMode);

    inline bool Get_Visible(void)
    {
        return m_visible;
    }
    inline void Set_Visible(bool _visible)
    {
        m_visible = _visible;
    }
};

#endif










