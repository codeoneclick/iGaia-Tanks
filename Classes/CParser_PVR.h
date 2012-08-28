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
    struct SDescription
    {
        GLenum m_glFormat;
        GLenum m_glType;
        int m_uiBPP;
        glm::vec2 m_vSize;
        unsigned int m_uiMIP;
        char* m_pData;
        bool m_bCompressed;
        unsigned int m_iNumFaces;
        
        SDescription(void)
        {
            m_pData = nullptr;
        };
        
        ~SDescription(void)
        {
            SAFE_DELETE(m_pData);
        };
    };
    
private:
    SDescription* m_pDescription;
public:
    CParser_PVR(void);
    ~CParser_PVR(void);
    void Load(const std::string& _sName);
    IResource* Commit(void);
};

#endif
