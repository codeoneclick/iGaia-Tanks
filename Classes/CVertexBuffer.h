//
//  CVertexBuffer.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBuffer_h
#define iGaia_CVertexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <stdlib.h>
#include <map>
#include "CShader.h"

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class CVertexBuffer
{
public:
    struct SVertex
    {
        glm::vec3 m_position;
        glm::vec2 m_texcoord;
        glm::u8vec4 m_normal;
        glm::u8vec4 m_tangent;
        glm::u8vec4 m_color;
    };
protected:
    SVertex* m_dataSource;
    GLuint m_handle;
    GLenum m_mode;
    unsigned int m_numVertexes;
    CShader* m_shaderReferences[CShader::E_RENDER_MODE_WORLD_SPACE_MAX + CShader::E_RENDER_MODE_SCREEN_SPACE_MAX];
public:
    CVertexBuffer(unsigned int _numVertexes, unsigned int _mode);
    ~CVertexBuffer(void);
    
    void PutShaderReference(unsigned int _renderMode, CShader* _shader);
    inline unsigned int Get_NumVertexes(void)
    {
        return m_numVertexes;
    }
    
    static glm::u8vec4 CompressVEC3(const glm::vec3& _uncopressed);
    static glm::vec3 UncompressU8VEC4(const glm::u8vec4& _compressed);
    
    inline SVertex* Lock(void)
    {
        return m_dataSource;
    }
    void Unlock(void);
    
    virtual void Bind(unsigned int _renderMode);
    virtual void Unbind(unsigned int _renderMode);
};

#endif
