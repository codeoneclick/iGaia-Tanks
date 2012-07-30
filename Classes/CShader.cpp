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

CShader::CShader(GLuint _hHandle)
{
    m_hHandle = _hHandle;
    
    m_lAttributeContainer[E_ATTRIBUTE_MATRIX_WORLD] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_MATRIX_WORLD.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_MATRIX_VIEW] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_MATRIX_VIEW.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_MATRIX_PROJECTION] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_MATRIX_PROJECTION.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_MATRIX_WVP] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_MATRIX_WVP.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_VECTOR_CAMERA_POSITION] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_VECTOR_CAMERA_POSITION.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_VECTOR_LIGHT_POSITION] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_VECTOR_LIGHT_POSITION.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_VECTOR_CLIP_PLANE] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_VECTOR_CLIP_PLANE.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_FLOAT_TIMER] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_FLOAT_TIMER.c_str());
    m_lAttributeContainer[E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET] = glGetUniformLocation(m_hHandle, k_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET.c_str());
    
    m_lTextureSlotContainer[E_TEXTURE_SLOT_01] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_01.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_02] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_02.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_03] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_03.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_04] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_04.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_05] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_05.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_06] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_06.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_07] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_07.c_str());
    m_lTextureSlotContainer[E_TEXTURE_SLOT_08] = glGetUniformLocation(m_hHandle, k_TEXTURE_SLOT_08.c_str());
    
    m_lVertexSlotContainer[E_VERTEX_SLOT_POSITION] = glGetAttribLocation(m_hHandle, k_VERTEX_SLOT_POSITION.c_str());
    m_lVertexSlotContainer[E_VERTEX_SLOT_TEXCOORD] = glGetAttribLocation(m_hHandle, k_VERTEX_SLOT_TEXCOORD.c_str());
    m_lVertexSlotContainer[E_VERTEX_SLOT_NORMAL] = glGetAttribLocation(m_hHandle, k_VERTEX_SLOT_NORMAL.c_str());
    m_lVertexSlotContainer[E_VERTEX_SLOT_TANGENT] = glGetAttribLocation(m_hHandle, k_VERTEX_SLOT_TANGENT.c_str());
    m_lVertexSlotContainer[E_VERTEX_SLOT_COLOR] = glGetAttribLocation(m_hHandle, k_VERTEX_SLOT_COLOR.c_str());
}

CShader::~CShader(void)
{
    
}

void CShader::Set_Matrix(const glm::mat4x4 &_mValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hAttribute = m_lAttributeContainer[_eAttribute];
    glUniformMatrix4fv(hAttribute, 1, 0, &_mValue[0][0]);
}

void CShader::Set_CustomMatrix(const glm::mat4x4 &_mValue, const std::string &_sAttribute)
{
    GLint hAttribute = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniformMatrix4fv(hAttribute, 1, 0, &_mValue[0][0]);
}

void CShader::Set_Matrix3x3(const glm::mat3x3 &_mValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hAttribute = m_lAttributeContainer[_eAttribute];
    glUniformMatrix3fv(hAttribute, 1, 0, &_mValue[0][0]);
}

void CShader::Set_CustomMatrix3x3(const glm::mat3x3 &_mValue, const std::string &_sAttribute)
{
    GLint hAttribute = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniformMatrix3fv(hAttribute, 1, 0, &_mValue[0][0]);
}

void CShader::Set_Vector2(const glm::vec2 &_vValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hHandle = m_lAttributeContainer[_eAttribute];
    glUniform2fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_CustomVector2(const glm::vec2 &_vValue, const std::string &_sAttribute)
{
    GLint hHandle = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniform2fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_Vector3(const glm::vec3 &_vValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hHandle = m_lAttributeContainer[_eAttribute];
    glUniform3fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_CustomVector3(const glm::vec3 &_vValue, const std::string &_sAttribute)
{
    GLint hHandle = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniform3fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_Vector4(const glm::vec4 &_vValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hHandle = m_lAttributeContainer[_eAttribute];
    glUniform4fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_CustomVector4(const glm::vec4 &_vValue, const std::string &_sAttribute)
{
    GLint hHandle = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniform4fv(hHandle, 1, &_vValue[0]);
}

void CShader::Set_Texture(GLuint _hHandle, CShader::E_TEXTURE_SLOT _eSlot)
{
    glActiveTexture(GL_TEXTURE0 + _eSlot);
    glBindTexture(GL_TEXTURE_2D, _hHandle);
    glUniform1i(m_lTextureSlotContainer[_eSlot], _eSlot);
}

void CShader::Set_Float(float _fValue, CShader::E_ATTRIBUTE _eAttribute)
{
    GLint hHandle = m_lAttributeContainer[_eAttribute];
    glUniform1f(hHandle, _fValue);
}

void CShader::Set_CustomFloat(float _fValue, const std::string &_sAttribute)
{
    GLint hHandle = glGetUniformLocation(m_hHandle, _sAttribute.c_str());
    glUniform1f(hHandle, _fValue);
}

void CShader::Enable(void)
{
    glValidateProgram(m_hHandle);
    GLint success;
    glGetProgramiv(m_hHandle, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLchar messages[256];
        glGetProgramInfoLog(m_hHandle, sizeof(messages), 0, &messages[0]);
        std::cout<<messages<<std::endl;
        return;
    }
    glUseProgram(m_hHandle);
}

void CShader::Disable(void)
{
    glUseProgram(NULL);
}




