//
//  CShader.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShader.h"

const std::string CShader::k_VERTEX_SLOT_POSITION = "IN_SLOT_Position";
const std::string CShader::k_VERTEX_SLOT_TEXCOORD = "IN_SLOT_TexCoord";
const std::string CShader::k_VERTEX_SLOT_NORMAL = "IN_SLOT_Normal";
const std::string CShader::k_VERTEX_SLOT_TANGENT = "IN_SLOT_Tangent";
const std::string CShader::k_VERTEX_SLOT_COLOR = "IN_SLOT_Color";

const std::string CShader::k_ATTRIBUTE_MATRIX_WORLD = "EXT_MATRIX_World";
const std::string CShader::k_ATTRIBUTE_MATRIX_VIEW = "EXT_MATRIX_View";
const std::string CShader::k_ATTRIBUTE_MATRIX_PROJECTION = "EXT_MATRIX_Projection";
const std::string CShader::k_ATTRIBUTE_MATRIX_WVP = "EXT_MATRIX_WVP";
const std::string CShader::k_ATTRIBUTE_VECTOR_CAMERA_POSITION = "EXT_View";
const std::string CShader::k_ATTRIBUTE_VECTOR_LIGHT_POSITION = "EXT_Light";
const std::string CShader::k_ATTRIBUTE_VECTOR_CLIP_PLANE = "EXT_Clip_Plane";
const std::string CShader::k_ATTRIBUTE_FLOAT_TIMER = "EXT_Timer";
const std::string CShader::k_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET = "EXT_Texcoord_Offset";

const std::string CShader::k_TEXTURE_SLOT_01 = "EXT_TEXTURE_01";
const std::string CShader::k_TEXTURE_SLOT_02 = "EXT_TEXTURE_02";
const std::string CShader::k_TEXTURE_SLOT_03 = "EXT_TEXTURE_03";
const std::string CShader::k_TEXTURE_SLOT_04 = "EXT_TEXTURE_04";
const std::string CShader::k_TEXTURE_SLOT_05 = "EXT_TEXTURE_05";
const std::string CShader::k_TEXTURE_SLOT_06 = "EXT_TEXTURE_06";
const std::string CShader::k_TEXTURE_SLOT_07 = "EXT_TEXTURE_07";
const std::string CShader::k_TEXTURE_SLOT_08 = "EXT_TEXTURE_08";

CShader::CShader(unsigned int _handle)
{
    m_handle = _handle;
    
    m_attributes[E_ATTRIBUTE_MATRIX_WORLD] = glGetUniformLocation(m_handle, k_ATTRIBUTE_MATRIX_WORLD.c_str());
    m_attributes[E_ATTRIBUTE_MATRIX_VIEW] = glGetUniformLocation(m_handle, k_ATTRIBUTE_MATRIX_VIEW.c_str());
    m_attributes[E_ATTRIBUTE_MATRIX_PROJECTION] = glGetUniformLocation(m_handle, k_ATTRIBUTE_MATRIX_PROJECTION.c_str());
    m_attributes[E_ATTRIBUTE_MATRIX_WVP] = glGetUniformLocation(m_handle, k_ATTRIBUTE_MATRIX_WVP.c_str());
    m_attributes[E_ATTRIBUTE_VECTOR_CAMERA_POSITION] = glGetUniformLocation(m_handle, k_ATTRIBUTE_VECTOR_CAMERA_POSITION.c_str());
    m_attributes[E_ATTRIBUTE_VECTOR_LIGHT_POSITION] = glGetUniformLocation(m_handle, k_ATTRIBUTE_VECTOR_LIGHT_POSITION.c_str());
    m_attributes[E_ATTRIBUTE_VECTOR_CLIP_PLANE] = glGetUniformLocation(m_handle, k_ATTRIBUTE_VECTOR_CLIP_PLANE.c_str());
    m_attributes[E_ATTRIBUTE_FLOAT_TIMER] = glGetUniformLocation(m_handle, k_ATTRIBUTE_FLOAT_TIMER.c_str());
    m_attributes[E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET] = glGetUniformLocation(m_handle, k_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET.c_str());
    
    m_textureSlots[E_TEXTURE_SLOT_01] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_01.c_str());
    m_textureSlots[E_TEXTURE_SLOT_02] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_02.c_str());
    m_textureSlots[E_TEXTURE_SLOT_03] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_03.c_str());
    m_textureSlots[E_TEXTURE_SLOT_04] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_04.c_str());
    m_textureSlots[E_TEXTURE_SLOT_05] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_05.c_str());
    m_textureSlots[E_TEXTURE_SLOT_06] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_06.c_str());
    m_textureSlots[E_TEXTURE_SLOT_07] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_07.c_str());
    m_textureSlots[E_TEXTURE_SLOT_08] = glGetUniformLocation(m_handle, k_TEXTURE_SLOT_08.c_str());
    
    m_vertexSlots[E_VERTEX_SLOT_POSITION] = glGetAttribLocation(m_handle, k_VERTEX_SLOT_POSITION.c_str());
    m_vertexSlots[E_VERTEX_SLOT_TEXCOORD] = glGetAttribLocation(m_handle, k_VERTEX_SLOT_TEXCOORD.c_str());
    m_vertexSlots[E_VERTEX_SLOT_NORMAL] = glGetAttribLocation(m_handle, k_VERTEX_SLOT_NORMAL.c_str());
    m_vertexSlots[E_VERTEX_SLOT_TANGENT] = glGetAttribLocation(m_handle, k_VERTEX_SLOT_TANGENT.c_str());
    m_vertexSlots[E_VERTEX_SLOT_COLOR] = glGetAttribLocation(m_handle, k_VERTEX_SLOT_COLOR.c_str());
}

CShader::~CShader(void)
{
    
}

void CShader::Set_Matrix4x4(const glm::mat4x4 &_matrix, CShader::E_ATTRIBUTE _attribute)
{
    int handle = m_attributes[_attribute];
    glUniformMatrix4fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_CustomMatrix4x4(const glm::mat4x4 &_matrix, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniformMatrix4fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Matrix3x3(const glm::mat3x3 &_matrix, CShader::E_ATTRIBUTE _attribute)
{
    int handle = m_attributes[_attribute];
    glUniformMatrix3fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_CustomMatrix3x3(const glm::mat3x3 &_matrix, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniformMatrix3fv(handle, 1, 0, &_matrix[0][0]);
}

void CShader::Set_Vector2(const glm::vec2 &_vector, CShader::E_ATTRIBUTE _attribute)
{
    int handle = m_attributes[_attribute];
    glUniform2fv(handle, 1, &_vector[0]);
}

void CShader::Set_CustomVector2(const glm::vec2 &_vector, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform2fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector3(const glm::vec3 &_vector, CShader::E_ATTRIBUTE _attribute)
{
    int handle = m_attributes[_attribute];
    glUniform3fv(handle, 1, &_vector[0]);
}

void CShader::Set_CustomVector3(const glm::vec3 &_vector, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform3fv(handle, 1, &_vector[0]);
}

void CShader::Set_Vector4(const glm::vec4 &_vector, CShader::E_ATTRIBUTE _attribute)
{
    int handle= m_attributes[_attribute];
    glUniform4fv(handle, 1, &_vector[0]);
}

void CShader::Set_CustomVector4(const glm::vec4 &_vector, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform4fv(handle, 1, &_vector[0]);
}

void CShader::Set_Float(float _float, CShader::E_ATTRIBUTE _attribute)
{
    int handle = m_attributes[_attribute];
    glUniform1f(handle, _float);
}

void CShader::Set_CustomFloat(float _float, const std::string &_attribute)
{
    int handle = glGetUniformLocation(m_handle, _attribute.c_str());
    glUniform1f(handle, _float);
}

void CShader::Set_Texture(GLuint _handle, CShader::E_TEXTURE_SLOT _slot)
{
    glActiveTexture(GL_TEXTURE0 + _slot);
    glBindTexture(GL_TEXTURE_2D, _handle);
    glUniform1i(m_textureSlots[_slot], _slot);
}

void CShader::Enable(void)
{
    glUseProgram(m_handle);
}

void CShader::Disable(void)
{
    glUseProgram(NULL);
}




