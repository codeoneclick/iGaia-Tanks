//
//  CVertexBuffer.h
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBuffer_h
#define iGaia_CVertexBuffer_h

/*#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <stdlib.h>

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class CVertexBuffer
{
protected:
    static const std::string k_SLOT_POSITION;
    static const std::string k_SLOT_TEXCOORD;
    static const std::string k_SLOT_NORMAL;
    static const std::string k_SLOT_TANGENT;
    static const std::string k_SLOT_COLOR;
    
struct SVertex
{
    glm::vec3*    m_pPositionSourceData;
    glm::vec2*    m_pTexcoordSourceData;
    glm::u8vec4*  m_pNormalSourceData;  
    glm::u8vec4*  m_pTangentSourceData; 
    glm::u8vec4*  m_pColorSourceData;
};

protected:
    GLuint m_iHandle;
    GLuint m_iShaderHandle;
    unsigned int m_iNumVertexes;
    unsigned int m_iSize;
    bool m_bIsInVRAM;
    
    GLint m_iPositionSlot;
    GLint m_iTexcoordSlot;
    GLint m_iNormalSlot;
    GLint m_iTangentSlot;
    GLint m_iColorSlot;
    
    SVertex m_WorkingSourceData;
    char* m_pSourceData;
    GLenum m_eMode;
public:
    CVertexBuffer(unsigned int _iNumVertexes);
    ~CVertexBuffer(void);
    
    unsigned int Get_NumVertexes(void) { return  m_iNumVertexes; }
    
    inline glm::vec3* GetOrCreate_PositionSourceData(void)
    {
        if(m_WorkingSourceData.m_pPositionSourceData == NULL)
        {
            m_WorkingSourceData.m_pPositionSourceData = new glm::vec3[m_iNumVertexes];
        }
        return m_WorkingSourceData.m_pPositionSourceData;
    };
    
    inline glm::vec2* GetOrCreate_TexcoordSourceData(void)
    {
        if(m_WorkingSourceData.m_pTexcoordSourceData == NULL)
        {
            m_WorkingSourceData.m_pTexcoordSourceData = new glm::vec2[m_iNumVertexes];
        }
        return m_WorkingSourceData.m_pTexcoordSourceData;
    };
    
    inline glm::u8vec4* GetOrCreate_NormalSourceData(void)
    {
        if(m_WorkingSourceData.m_pNormalSourceData == NULL)
        {
            m_WorkingSourceData.m_pNormalSourceData = new glm::u8vec4[m_iNumVertexes];
        }
        return m_WorkingSourceData.m_pNormalSourceData;
    };
    
    inline glm::u8vec4* GetOrCreate_TangentSourceData(void)
    {
        if(m_WorkingSourceData.m_pTangentSourceData == NULL)
        {
            m_WorkingSourceData.m_pTangentSourceData = new glm::u8vec4[m_iNumVertexes];
        }
        return m_WorkingSourceData.m_pTangentSourceData;
    };
    
    inline glm::u8vec4* GetOrCreate_ColorSourceData(void)
    {
        if(m_WorkingSourceData.m_pColorSourceData == NULL)
        {
            m_WorkingSourceData.m_pColorSourceData = new glm::u8vec4[m_iNumVertexes];
        }
        return m_WorkingSourceData.m_pColorSourceData;
    }
    
    void Set_Mode(GLenum _eMode) { m_eMode = _eMode; }
    
    inline void Set_ShaderRef(GLuint _iShaderHandler)
    {
        m_iShaderHandle = _iShaderHandler;
        m_iPositionSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_POSITION.c_str());
        m_iTexcoordSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_TEXCOORD.c_str());
        m_iNormalSlot   = glGetAttribLocation(m_iShaderHandle, k_SLOT_NORMAL.c_str());
        m_iTangentSlot  = glGetAttribLocation(m_iShaderHandle, k_SLOT_TANGENT.c_str());
        m_iColorSlot    = glGetAttribLocation(m_iShaderHandle, k_SLOT_COLOR.c_str());
    };
    
    inline GLuint Get_ShaderRef(void) { return m_iShaderHandle; }
    
    static glm::u8vec4 CompressVEC3(const glm::vec3& _vUncopressed);
    static glm::vec3   UnCompressU8VEC4(const glm::u8vec4 _vCompressed);
    
    void Enable(void);
    void Disable(void);
    
    void Lock(void);
    void Unlock(void);
    
    void AppendWorkingSourceData(void);
    void CommitFromRAMToVRAM(void);
    
};*/

#endif
