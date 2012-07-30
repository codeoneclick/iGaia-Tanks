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
        char* m_pTextureData;
        char* m_pHeaderData;
        bool m_bCompressed;
        unsigned int m_iNumFaces;
    };
    
private:
    CTexture::SSourceData* m_pSourceData;
    char* m_pData;
    SDescription* m_pDescription;
public:
    CParser_PVR(void);
    virtual ~CParser_PVR(void);
    virtual void* Get_SourceData(void) { return m_pSourceData; }
    virtual void Load(const std::string& _sName);
    virtual void Commit(void);
};

#endif
