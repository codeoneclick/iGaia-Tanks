//
//  CParser_PVR.h
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CParser_PVR_h
#define iGaia_CParser_PVR_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"
#include <glm/glm.hpp>
#include "CTexture.h"
#include "IParser.h"

class CParser_PVR : public IParser
{
protected:
    
    GLenum m_format;
    int m_bytesPerPixel;
    glm::vec2 m_size;
    char* m_dataSource;
    unsigned int m_headerOffset;
    
public:
    CParser_PVR(void);
    ~CParser_PVR(void);
    void Load(const std::string& _name);
    IResource* Commit(void);
};

#endif
