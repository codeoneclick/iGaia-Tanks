//
//  CSpriteMgr.h
//  iGaia
//
//  Created by Sergey Sergeev on 5/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CSpriteMgr_h
#define iGaia_CSpriteMgr_h

#include <iostream>
#include "CSprite.h"
#include "CBillboard.h"
#include "CSpriteCross.h"

class CSpriteMgr
{
protected:
    std::vector<INode*> m_lSpriteContainer;
public:
    CSpriteMgr(void);
    ~CSpriteMgr(void);
    CSprite* Add_Sprite(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas);
    CSpriteCross* Add_SpriteCross(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas);
    CBillboard* Add_Billboard(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas);
    void Remove_Sprite(INode* pSprite);
    
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};


#endif
