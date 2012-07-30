//
//  CShader.h
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CShader_h
#define iGaia_CShader_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "stdlib.h"
#include <string>
#include <glm/glm.hpp>
#include <map>

class CShader
{
public:
    enum E_RENDER_MODE { E_RENDER_MODE_SIMPLE = 0, E_RENDER_MODE_REFLECTION, E_RENDER_MODE_REFRACTION, E_RENDER_MODE_SCREEN_NORMAL_MAP, E_RENDER_MODE_MAX , E_RENDER_MODE_SCREEN_SPACE_SIMPLE, E_RENDER_MODE_SCREEN_SPACE_BLOOM_EXTRACT, E_RENDER_MODE_SCREEN_SPACE_BLOOM_COMBINE, E_RENDER_MODE_SCREEN_SPACE_BLUR, E_RENDER_MODE_SCREEN_SPACE_EDGE_DETECT};
    enum E_VERTEX_SLOT { E_VERTEX_SLOT_POSITION = 0, E_VERTEX_SLOT_TEXCOORD, E_VERTEX_SLOT_NORMAL, E_VERTEX_SLOT_TANGENT, E_VERTEX_SLOT_COLOR };
    enum E_ATTRIBUTE { E_ATTRIBUTE_MATRIX_WORLD = 0, E_ATTRIBUTE_MATRIX_VIEW, E_ATTRIBUTE_MATRIX_PROJECTION, E_ATTRIBUTE_MATRIX_WVP, E_ATTRIBUTE_VECTOR_CAMERA_POSITION, E_ATTRIBUTE_VECTOR_LIGHT_POSITION, E_ATTRIBUTE_VECTOR_CLIP_PLANE, E_ATTRIBUTE_FLOAT_TIMER, E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET };
    enum E_TEXTURE_SLOT { E_TEXTURE_SLOT_01 = 0, E_TEXTURE_SLOT_02, E_TEXTURE_SLOT_03, E_TEXTURE_SLOT_04, E_TEXTURE_SLOT_05, E_TEXTURE_SLOT_06, E_TEXTURE_SLOT_07, E_TEXTURE_SLOT_08 };
protected:
    static const std::string k_VERTEX_SLOT_POSITION;
    static const std::string k_VERTEX_SLOT_TEXCOORD;
    static const std::string k_VERTEX_SLOT_NORMAL;
    static const std::string k_VERTEX_SLOT_TANGENT;
    static const std::string k_VERTEX_SLOT_COLOR;
    
    static const std::string k_ATTRIBUTE_MATRIX_WORLD;
    static const std::string k_ATTRIBUTE_MATRIX_VIEW;
    static const std::string k_ATTRIBUTE_MATRIX_PROJECTION;
    static const std::string k_ATTRIBUTE_MATRIX_WVP;
    static const std::string k_ATTRIBUTE_VECTOR_CAMERA_POSITION;
    static const std::string k_ATTRIBUTE_VECTOR_LIGHT_POSITION;
    static const std::string k_ATTRIBUTE_VECTOR_CLIP_PLANE;
    static const std::string k_ATTRIBUTE_FLOAT_TIMER;
    static const std::string k_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET;
    
    static const std::string k_TEXTURE_SLOT_01;
    static const std::string k_TEXTURE_SLOT_02;
    static const std::string k_TEXTURE_SLOT_03;
    static const std::string k_TEXTURE_SLOT_04;
    static const std::string k_TEXTURE_SLOT_05;
    static const std::string k_TEXTURE_SLOT_06;
    static const std::string k_TEXTURE_SLOT_07;
    static const std::string k_TEXTURE_SLOT_08;
    
    GLuint m_hHandle;
    
    std::map<E_ATTRIBUTE, GLint>    m_lAttributeContainer;
    std::map<E_VERTEX_SLOT, GLint>  m_lVertexSlotContainer;
    std::map<E_TEXTURE_SLOT, GLint> m_lTextureSlotContainer;
public:
    CShader(GLuint _hHandle);
    ~CShader(void);
    
    void Enable(void);
    void Disable(void);
    
    inline GLuint Get_Handle(void) { return m_hHandle; }
    
    inline GLint Get_VertexSlot(E_VERTEX_SLOT _eSlot) { return m_lVertexSlotContainer[_eSlot]; }
    
    void Set_Matrix(const glm::mat4x4& _mValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomMatrix(const glm::mat4x4& _mValue, const std::string& _sAttribute);
    
    void Set_Matrix3x3(const glm::mat3x3& _mValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomMatrix3x3(const glm::mat3x3& _mValue, const std::string& _sAttribute);
    
    void Set_Vector2(const glm::vec2& _vValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomVector2(const glm::vec2& _vValue, const std::string& _sAttribute);
    
    void Set_Vector3(const glm::vec3& _vValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomVector3(const glm::vec3& _vValue, const std::string& _sAttribute);
    
    void Set_Vector4(const glm::vec4& _vValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomVector4(const glm::vec4& _vValue, const std::string& _sAttribute);
    
    void Set_Float(float _fValue, E_ATTRIBUTE _eAttribute);
    void Set_CustomFloat(float _fValue, const std::string& _sAttribute);
    
    void Set_Texture(GLuint _hHandle, E_TEXTURE_SLOT _eSlot);
};


#endif
