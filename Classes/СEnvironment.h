//
//  СEnvironment.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/31/12.
//
//

#ifndef __iGaia___Environment__
#define __iGaia___Environment__

#include "CCommon.h"
#include "CHeightMapSetter.h"
#include "CLandscape.h"
#include "CLandscapeEdges.h"
#include "CGrass.h"
#include "COcean.h"
#include "CSkyBox.h"

class CEnviroment
{
protected:
    CHeightMapSetter* m_pHeightMapSetter;
    CLandscape* m_pLandscape;
    CLandscapeEdges* m_pLandscapeEdges;
    CGrass* m_pGrass;
    COcean* m_pOcean;
    CSkyBox* m_pSkyBox;
public:
    CEnviroment(void);
    ~CEnviroment(void);
    void Load(const std::string& _sName);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    inline INode* Get_Landscape(void) const { return m_pLandscape; }
    inline INode* Get_LandscapeEdges(void) const { return m_pLandscapeEdges; }
    inline INode* Get_Grass(void) const { return m_pGrass; }
    inline INode* Get_Ocean(void) const { return m_pOcean; }
    inline INode* Get_SkyBox(void) const { return m_pSkyBox; }
};

#endif /* defined(__iGaia___Environment__) */
