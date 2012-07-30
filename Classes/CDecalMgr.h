//
//  CDecalMgr.h
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#ifndef __iGaia__CDecalMgr__
#define __iGaia__CDecalMgr__

#include <iostream>
#include "CDecal.h"

class CDecalMgr
{
protected:
    std::vector<CDecal*> m_lDecalContainer;
public:
    CDecalMgr(void);
    ~CDecalMgr(void);
    CDecal* Add_Decal(void);
    void Remove_Decal(CDecal* _pDecal);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};


#endif /* defined(__iGaia__CDecalMgr__) */
