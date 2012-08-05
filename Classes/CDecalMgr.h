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
#include "CLandscapeDecal.h"

class CDecalMgr
{
protected:
    std::vector<INode*> m_lContainer;
public:
    CDecalMgr(void);
    ~CDecalMgr(void);
    INode* Add_LandscapeDecal(void);
    void Remove_Decal(INode* _pDecal);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};


#endif /* defined(__iGaia__CDecalMgr__) */
