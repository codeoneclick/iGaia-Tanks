//
//  CShader.h
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CShader_h
#define CShader_h

#include "HCommon.h"
#include "CTexture.h"

class CShader
{
private:

protected:
    
    i32 m_attributes[E_SHADER_ATTRIBUTE_MAX];
    i32 m_textureSlots[E_TEXTURE_SLOT_MAX];
    std::map<E_SHADER_VERTEX_SLOT, i32> m_vertexSlots;
    ui32 m_handle;
    
public:
    
    CShader(ui32 _handle);
    ~CShader(void);
    
    inline std::map<E_SHADER_VERTEX_SLOT, i32> Get_VertexSlots(void)
    {
        return m_vertexSlots;
    };
    
    void Set_Matrix3x3(const glm::mat3x3& _matrix, E_SHADER_ATTRIBUTE _attribute);
    void Set_Matrix3x3Custom(const glm::mat3x3& _matrix, const std::string& _attribute);
    void Set_Matrix4x4(const glm::mat4x4& _matrix, E_SHADER_ATTRIBUTE _attribute);
    void Set_Matrix4x4Custom(const glm::mat4x4& _matrix, const std::string& _attribute);
    void Set_Vector2(const glm::vec2& _vector, E_SHADER_ATTRIBUTE _attribute);
    void Set_Vector2Custom(const glm::vec2& _vector, const std::string& _attribute);
    void Set_Vector3(const glm::vec3& _vector, E_SHADER_ATTRIBUTE _attribute);
    void Set_Vector3Custom(const glm::vec3& _vector, const std::string& _attribute);
    void Set_Vector4(const glm::vec4& _vector, E_SHADER_ATTRIBUTE _attribute);
    void Set_Vector4Custom(const glm::vec4& _vector, const std::string& _attribute);
    void Set_Float(f32 _value, E_SHADER_ATTRIBUTE _attribute);
    void Set_FloatCustom(f32 _value, const std::string& _attribute);
    void Set_Texture(CTexture* _texture, E_TEXTURE_SLOT _slot);
    
    void Bind(void);
    void Unbind(void);

    
};


#endif
