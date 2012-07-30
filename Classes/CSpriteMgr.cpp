//
//  CSpriteMgr.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 5/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSpriteMgr.h"

CSpriteMgr::CSpriteMgr(void)
{
    
}


CSpriteMgr::~CSpriteMgr(void)
{
    
}

CSprite* CSpriteMgr::Add_Sprite(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas)
{
    CSprite* pSprite = new CSprite();
    pSprite->Set_NumFrames(_iNumFrames);
    pSprite->Set_SizeFrame(_vSizeFrame);
    pSprite->Set_SizeAtlas(_vSizeAtlas);
    m_lSpriteContainer.push_back(pSprite);
    pSprite->Load("sprite", IResource::E_THREAD_MAIN);
    return pSprite;
}

CSpriteCross* CSpriteMgr::Add_SpriteCross(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas)
{
    CSpriteCross* pSprite = new CSpriteCross();
    pSprite->Set_NumFrames(_iNumFrames);
    pSprite->Set_SizeFrame(_vSizeFrame);
    pSprite->Set_SizeAtlas(_vSizeAtlas);
    m_lSpriteContainer.push_back(pSprite);
    pSprite->Load("sprite-cross", IResource::E_THREAD_MAIN);
    return pSprite;
}

CBillboard* CSpriteMgr::Add_Billboard(unsigned int _iNumFrames,const glm::vec2& _vSizeFrame,const glm::vec2& _vSizeAtlas)
{
    CBillboard* pSprite = new CBillboard();
    pSprite->Set_NumFrames(_iNumFrames);
    pSprite->Set_SizeFrame(_vSizeFrame);
    pSprite->Set_SizeAtlas(_vSizeAtlas);
    m_lSpriteContainer.push_back(pSprite);
    pSprite->Load("billboard", IResource::E_THREAD_MAIN);
    return pSprite;
}

void CSpriteMgr::Remove_Sprite(INode *pSprite)
{
    std::vector<INode*>::iterator pBeginSpriteIterator = m_lSpriteContainer.begin();
    std::vector<INode*>::iterator pEndSpriteIterator = m_lSpriteContainer.end();
    
    while(pBeginSpriteIterator != pEndSpriteIterator)
    {
        if((*pBeginSpriteIterator) == pSprite)
        {
            m_lSpriteContainer.erase(pBeginSpriteIterator);
            delete pSprite;
            pSprite = NULL;
            break;
        }
        ++pBeginSpriteIterator;
    }
}

void CSpriteMgr::Update(void)
{
    std::vector<INode*>::iterator pBeginSpriteIterator = m_lSpriteContainer.begin();
    std::vector<INode*>::iterator pEndSpriteIterator = m_lSpriteContainer.end();
    
    while(pBeginSpriteIterator != pEndSpriteIterator)
    {
        (*pBeginSpriteIterator)->Update();
        ++pBeginSpriteIterator;
    }
}

void CSpriteMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::vector<INode*>::iterator pBeginSpriteIterator = m_lSpriteContainer.begin();
    std::vector<INode*>::iterator pEndSpriteIterator = m_lSpriteContainer.end();
    
    while(pBeginSpriteIterator != pEndSpriteIterator)
    {
        (*pBeginSpriteIterator)->Render(_eMode);
        ++pBeginSpriteIterator;
    }
}
