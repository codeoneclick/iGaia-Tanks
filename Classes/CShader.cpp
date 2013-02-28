//
//  CShader.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CShader.h"

extern const struct SShaderVertexSlot
{
    std::string m_position;
    std::string m_texcoord;
    std::string m_normal;
    std::string m_tangent;
    std::string m_color;
    
} SShaderVertexSlot;

extern const struct SShaderAttributes
{
    std::string m_worldMatrix;
    std::string m_viewMatrix;
    std::string m_projectionMatrix;
    std::string m_worldViewProjectionMatrix;
    std::string m_cameraPosition;
    std::string m_lightPosition;
    std::string m_clipPlane;
    std::string m_texcoordOffset;
    std::string m_time;
    
} SShaderAttributes;

extern const struct SShaderTextureSlot
{
    std::string m_texture_01;
    std::string m_texture_02;
    std::string m_texture_03;
    std::string m_texture_04;
    std::string m_texture_05;
    std::string m_texture_06;
    std::string m_texture_07;
    std::string m_texture_08;
    
} SShaderTextureSlot;

const struct SShaderVertexSlot SShaderVertexSlot =
{
    .m_position = "IN_SLOT_Position",
    .m_texcoord = "IN_SLOT_TexCoord",
    .m_normal = "IN_SLOT_Normal",
    .m_tangent = "IN_SLOT_Tangent",
    .m_color = "IN_SLOT_Color"
};

const struct SShaderAttributes SShaderAttributes =
{
    .m_worldMatrix = "EXT_MATRIX_World",
    .m_viewMatrix = "EXT_MATRIX_View",
    .m_projectionMatrix = "EXT_MATRIX_Projection",
    .m_worldViewProjectionMatrix = "EXT_MATRIX_WVP",
    .m_cameraPosition = "EXT_View",
    .m_lightPosition = "EXT_Light",
    .m_clipPlane = "EXT_Clip_Plane",
    .m_texcoordOffset = "EXT_Texcoord_Offset",
    .m_time = "EXT_Timer"
};

const struct SShaderTextureSlot SShaderTextureSlot =
{
    .m_texture_01 = "EXT_TEXTURE_01",
    .m_texture_02 = "EXT_TEXTURE_02",
    .m_texture_03 = "EXT_TEXTURE_03",
    .m_texture_04 = "EXT_TEXTURE_04",
    .m_texture_05 = "EXT_TEXTURE_05",
    .m_texture_06 = "EXT_TEXTURE_06",
    .m_texture_07 = "EXT_TEXTURE_07",
    .m_texture_08 = "EXT_TEXTURE_08"
};

CShader::CShader(ui32 _handle)
{
    m_handle = _handle;
    
    m_attributes[E_SHADER_ATTRIBUTE_MATRIX_WORLD] = glGetUniformLocation(m_handle, SShaderAttributes.m_worldMatrix.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_MATRIX_VIEW] = glGetUniformLocation(m_handle, SShaderAttributes.m_viewMatrix.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_MATRIX_PROJECTION] = glGetUniformLocation(m_handle, SShaderAttributes.m_projectionMatrix.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_MATRIX_WVP] = glGetUniformLocation(m_handle, SShaderAttributes.m_worldViewProjectionMatrix.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION] = glGetUniformLocation(m_handle, SShaderAttributes.m_cameraPosition.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION] = glGetUniformLocation(m_handle, SShaderAttributes.m_lightPosition.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE] = glGetUniformLocation(m_handle, SShaderAttributes.m_clipPlane.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_VECTOR_TEXTURE_DISPLACE] = glGetUniformLocation(m_handle, SShaderAttributes.m_texcoordOffset.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_FLOAT_TIMER] = glGetUniformLocation(m_handle, SShaderAttributes.m_time.c_str());
    
    m_textureSlots[E_TEXTURE_SLOT_01] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_01.c_str());
    m_textureSlots[E_TEXTURE_SLOT_02] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_02.c_str());
    m_textureSlots[E_TEXTURE_SLOT_03] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_03.c_str());
    m_textureSlots[E_TEXTURE_SLOT_04] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_04.c_str());
    m_textureSlots[E_TEXTURE_SLOT_05] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_05.c_str());
    m_textureSlots[E_TEXTURE_SLOT_06] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_06.c_str());
    m_textureSlots[E_TEXTURE_SLOT_07] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_07.c_str());
    m_textureSlots[E_TEXTURE_SLOT_08] = glGetUniformLocation(m_handle, SShaderTextureSlot.m_texture_08.c_str());
    
    m_vertexSlots[E_SHADER_VERTEX_SLOT_POSITION] = glGetAttribLocation(m_handle, SShaderVertexSlot.m_position.c_str());
    m_vertexSlots[E_SHADER_VERTEX_SLOT_TEXCOORD] = glGetAttribLocation(m_handle, SShaderVertexSlot.m_texcoord.c_str());
    m_vertexSlots[E_SHADER_VERTEX_SLOT_NORMAL] = glGetAttribLocation(m_handle, SShaderVertexSlot.m_normal.c_str());
    m_vertexSlots[E_SHADER_VERTEX_SLOT_TANGENT] = glGetAttribLocation(m_handle, SShaderVertexSlot.m_tangent.c_str());
    m_vertexSlots[E_SHADER_VERTEX_SLOT_COLOR] = glGetAttribLocation(m_handle, SShaderVertexSlot.m_color.c_str());
}

CShader::~CShader(void)
{
    
}

void CShader::Set_Matrix3x3(const glm::mat3x3 &_matrix, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniformMatrix3fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Matrix3x3Custom(const glm::mat3x3 &_matrix, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniformMatrix3fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Matrix4x4(const glm::mat4x4 &_matrix, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniformMatrix4fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Matrix4x4Custom(const glm::mat4x4 &_matrix, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniformMatrix4fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Vector2(const glm::vec2 &_vector, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniform2fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector2Custom(const glm::vec2 &_vector, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform2fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector3(const glm::vec3 &_vector, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniform3fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector3Custom(const glm::vec3 &_vector, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform3fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector4(const glm::vec4 &_vector, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniform4fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector4Custom(const glm::vec4 &_vector, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform4fv(handle, 1, &_vector[0]);
}

void CShader::Set_Float(f32 _value, E_SHADER_ATTRIBUTE _attribute)
{
    i32 handle = m_attributes[_attribute];
    glUniform1f(handle, _value);
}

void CShader::Set_FloatCustom(f32 _value, const std::string &_attribute)
{
    i32 handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform1f(handle, _value);
}

void CShader::Set_Texture(CTexture *_texture, E_TEXTURE_SLOT _slot)
{
    glActiveTexture(GL_TEXTURE0 + _slot);
    _texture->Bind();
    glUniform1i(m_textureSlots[_slot], _slot);
}

void CShader::Bind(void)
{
    glUseProgram(m_handle);
}

void CShader::Unbind(void)
{
    glUseProgram(NULL);
}




