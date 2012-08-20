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
    std::vector<CCharacterControllerEnemy*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<CCharacterControllerEnemy*>::iterator pEndIterator = m_lContainer.end();

    while (pBeginIterator != pEndIterator)
    {
        CCharacterControllerEnemy::E_AI_STATE eState = (*pBeginIterator)->Get_AIState();
		switch (eState) {
			case CCharacterControllerEnemy::E_AI_STATE_STAND:
			{
			
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_MOVE:
			{
				glm::vec2 vPoint_01 = glm::vec2((*pBeginIterator)->Get_Position());
				if ((*pBeginIterator)->Get_Target()) {
					glm::vec2 vPoint_02 = glm::vec2((*pBeginIterator)->Get_Target()->Get_Position());
					float fDistanceToTargetPoint = glm::distance(vPoint_01, vPoint_02);
					if (fDistanceToTargetPoint < k_AI_SHOOT_DISTANCE) {
						(*pBeginIterator)->Set_AIMovePoint(glm::vec3((*pBeginIterator)->Get_Target()->Get_Position().x, 0.0f, (*pBeginIterator)->Get_Target()->Get_Position().y));
						(*pBeginIterator)->Set_AIState(CCharacterControllerEnemy::E_AI_STATE_CHASE, 0);
					}
				}
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_CHASE:
			{
				
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_CHASE_ATTACK:
			{
				
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_BACK:
			{
				
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_BACK_ATTACK:
			{
				
			}
				break;
			case CCharacterControllerEnemy::E_AI_STATE_NONE:
			default:
			{
				glm::vec2 vGeneratedPoint = _GenerateMovePoint();
				(*pBeginIterator)->Set_AIMovePoint(glm::vec3(vGeneratedPoint.x, 0.0f, vGeneratedPoint.y));
				(*pBeginIterator)->Set_AIState(CCharacterControllerEnemy::E_AI_STATE_MOVE, 0);
			}
				break;
		}
		
        ++pBeginIterator;
    }
}




