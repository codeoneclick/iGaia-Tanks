//
//  CIndexBuffer.h
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CIndexBuffer_h
#define iGaia_CIndexBuffer_h

#ifdef OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif EMULATION_GL
#include <GL/glew.h>
#ifndef GL_GLEXT_PROTOTYPES
#       define GL_GLEXT_PROTOTYPES 1
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <vector>

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class CIndexBuffer
{ 
private:
    unsigned short* m_pSourceData;
    unsigned short* m_pWorkingSourceData;
    GLuint m_hHandle;
    unsigned int m_iNumIndexes;
    unsigned int m_iNumWorkingIndexes;
    bool m_bIsCommited;
    GLenum m_eMode;
public:
    CIndexBuffer(unsigned int _iNumIndexes, unsigned int _eMode);
    ~CIndexBuffer(void);
    
    unsigned int Get_NumIndexes(void) { return m_iNumIndexes; }
    unsigned int Get_NumWorkingIndexes(void) { return m_iNumWorkingIndexes; }
    void Set_NumWorkingIndexes(unsigned int _iNumWorkingIndexes) { m_iNumWorkingIndexes = _iNumWorkingIndexes; }
    unsigned short* Get_WorkingSourceDataRef(void);
    unsigned short* Get_SourceData(void);
    unsigned short* Get_SourceDataFromVRAM(void);
    void Enable(void);
    void Disable(void);
    void Commit(void);
};


#endif
