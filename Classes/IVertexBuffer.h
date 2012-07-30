//
//  IVertexBuffer.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IVertexBuffer_h
#define iGaia_IVertexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <stdlib.h>
#include "CShader.h"

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

#define k_STRIDE_SIZE 32

class IVertexBuffer
{
protected:
    char* m_pData;
    GLuint m_hHandle;
    GLenum m_eMode;
    unsigned int m_iNumVertexes;
    std::map<CShader::E_RENDER_MODE, CShader*> m_lShaderRefContainer;
    bool m_bIsCommited;
public:
    IVertexBuffer(void);
    virtual ~IVertexBuffer(void);
    
    void Add_ShaderRef(CShader::E_RENDER_MODE _eRenderMode, CShader* _pShaderRef);
    inline unsigned int Get_NumVertexes(void) { return m_iNumVertexes; }
    
    static glm::u8vec4 CompressVEC3(const glm::vec3& _vUncopressed);
    static glm::vec3   UnCompressU8VEC4(const glm::u8vec4& _vCompressed);
    
    inline void* Lock(void) { return m_pData; }
    void Unlock(void);
    
    void Commit(void);
    
    virtual void Enable(CShader::E_RENDER_MODE _eRenderMode) = 0;
    virtual void Disable(CShader::E_RENDER_MODE _eRenderMode) = 0;
};

#endif
