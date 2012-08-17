//
//  CGameAIMgr.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CGameAIMgr.h"

CGameAIMgr::CGameAIMgr(void)
{
    srand(time(NULL));
}

CGameAIMgr::~CGameAIMgr(void)
{
     m_lContainer.clear();
}

void CGameAIMgr::Add_AICharacterController(ICharacterController *_pCharacterController)
{
    m_lContainer.push_back(static_cast<CCharacterControllerEnemy*>(_pCharacterController));
}

void CGameAIMgr::Remove_AICharacterController(ICharacterController *_pCharacterController)
{
    for(size_t index = 0; index > m_lContainer.size(); ++index)
    {
        if(m_lContainer[index] == _pCharacterController)
        {
            m_lContainer.erase(m_lContainer.begin() + index);
        }
    }
}

float CGameAIMgr::_Get_RandomFromRange(float _fMin, float _fMax)
{
    float fRange = _fMax - _fMin;
    return _fMin + float(fRange * rand() / (RAND_MAX + 1.0f)); 
}

glm::vec2 CGameAIMgr::_GenerateMovePoint(void)
{
    int iWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    int iHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
    float fRandPositionX = _Get_RandomFromRange(1.0f, iWidth - 1.0f);
    float fRandPositionZ = _Get_RandomFromRange(1.0f, iHeight - 1.0f);
    return glm::vec2(fRandPositionX, fRandPositionZ);
}

void CGameAIMgr::Update(void)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        CCharacterControllerEnemy::E_AI_STATE eState = m_lContainer[index]->Get_AIState();
        if(eState == CCharacterControllerEnemy::E_AI_STATE_NONE)
        {
            glm::vec2 vGeneratedPoint = _GenerateMovePoint();
            m_lContainer[index]->Set_AIMovePoint(glm::vec3(vGeneratedPoint.x, 0.0f, vGeneratedPoint.y));
            m_lContainer[index]->Set_AIState(CCharacterControllerEnemy::E_AI_STATE_MOVE, 0);
        }
    }
}




