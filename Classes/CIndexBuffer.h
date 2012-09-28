//
//  CIndexBuffer.h
//  iGaia
//
//  Created by sergey.sergeev on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CIndexBuffer_h
#define iGaia_CIndexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class CIndexBuffer
{ 
private:
    unsigned int m_hanlde;
    unsigned short* m_dataSource;
    unsigned int m_numIndexes;
    GLenum m_mode;
public:
    CIndexBuffer(unsigned int _numIndexes, unsigned int _mode);
    ~CIndexBuffer(void);
    
    unsigned int Get_NumIndexes(void)
    {
        return m_numIndexes;
    }

    unsigned short* Lock(void);
    void Unlock(void);

    void Bind(void);
    void Unbind(void);
};


#endif
