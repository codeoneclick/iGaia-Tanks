//
//  CWindow.h
//  iGaia
//
//  Created by sergey.sergeev on 12/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CWindow_h
#define iGaia_CWindow_h
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

class CWindow
{
private:
    static int m_iScreenWidth;
    static int m_iScreenHeight;
    static int m_iOffScreenWidth;
    static int m_iOffScreenHeight;
    static GLuint m_hScreenFBO;
public:
    static int Get_ScreenWidth()  { return m_iScreenWidth;  }
    static int Get_ScreenHeight() { return m_iScreenHeight; }
    static void Set_ScreenWidth(int _iWidth)   { m_iScreenWidth  = _iWidth;  }
    static void Set_ScreenHeight(int _iHeight) { m_iScreenHeight = _iHeight; } 
    
    static int Get_OffScreenWidth()  { return m_iOffScreenWidth;  }
    static int Get_OffScreenHeight() { return m_iOffScreenHeight; }
    static void Set_OffScreenWidth(int _iWidth)   { m_iOffScreenWidth  = _iWidth;  }
    static void Set_OffScreenHeight(int _iHeight) { m_iOffScreenHeight = _iHeight; }
    static void Set_ScreenFBO(GLuint _hScreenFBO) { m_hScreenFBO = _hScreenFBO; }
    static GLuint Get_ScreenFBO(void) { return m_hScreenFBO; }
};

#endif
