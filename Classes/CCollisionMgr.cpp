//
//  CCollisionMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CInput.h"
#include "CSceneMgr.h"
#include "CWindow.h"
#include "CVertexBufferPositionTexcoord.h"

CCollisionMgr::CCollisionMgr()
{
    m_vTouch3DPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    m_bIsTouch = false;
    m_pBox2dWorld = NULL;
}

CCollisionMgr::~CCollisionMgr()
{
    
}

void CCollisionMgr::Create_Box2dWorld(void)
{
    float fWidth = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Width();
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_Height();
	b2Vec2 vGravity = b2Vec2(0.0f, 0.0f);
    
	m_pBox2dWorld = new b2World(vGravity);
	m_pBox2dWorld->SetContinuousPhysics(true);
    
	b2BodyDef boundBodyDef;
	boundBodyDef.position.Set(0, 0);
	b2Body* boundBody = m_pBox2dWorld->CreateBody(&boundBodyDef);
    
	b2EdgeShape boundBox;
    
	boundBox.Set(b2Vec2(0.0f, 0.0f), b2Vec2(fWidth, 0.0f));
	boundBody->CreateFixture(&boundBox, 0);
    
    
	boundBox.Set(b2Vec2(0.0f, fHeight), b2Vec2(fWidth, fHeight));
	boundBody->CreateFixture(&boundBox, 0);
    
    
	boundBox.Set(b2Vec2(0.0f, fHeight), b2Vec2(0.0f, 0.0f));
	boundBody->CreateFixture(&boundBox, 0);
    
    
	boundBox.Set(b2Vec2(fWidth, fHeight), b2Vec2(fWidth, 0.0f));
	boundBody->CreateFixture(&boundBox, 0);
}

void CCollisionMgr::Destroy_Box2dWorld(void)
{
    SAFE_DELETE(m_pBox2dWorld);
}

void CCollisionMgr::OnScreenTouch(glm::vec2 _vTouchPoint)
{ 
    m_bIsTouch = true; 
    m_vTouch2DPoint = _vTouchPoint;
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    if(pCamera == NULL)
    {
        return;
    }
    
    glm::mat4x4 mView = pCamera->Get_View();
    glm::mat4x4 mProjection = pCamera->Get_Projection();
    
    glm::ivec4 vViewport;
    vViewport[0] = 0;
    vViewport[1] = 0;
    vViewport[2] = CWindow::Get_ScreenHeight();
    vViewport[3] = CWindow::Get_ScreenWidth();

    m_vTouchRay = Unproject(m_vTouch2DPoint, mView, mProjection, vViewport);
    CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);
}

bool CCollisionMgr::RayTriangleIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint)
{
    glm::vec3 vEdge_01 = _vTrianglePoint_02 - _vTrianglePoint_01;
	glm::vec3 vEdge_02 = _vTrianglePoint_03 - _vTrianglePoint_01;
    
    glm::vec3 vPVector = glm::cross(_tRay.m_vDirection, vEdge_02);
	float fDeterminant = glm::dot(vEdge_01, vPVector);
	if(fabs(fDeterminant) < 0.0001f) 
    {
        return false;
    }
    
    float fInvDeterminant = 1.0f / fDeterminant;
    
	glm::vec3 vTVector = _tRay.m_vOrigin - _vTrianglePoint_01;
	float fU = glm::dot(vTVector, vPVector) * fInvDeterminant;  
    if ( fU < -0.0001f || fU > 1.0001f )
    {
        return false;
    }
    
    glm::vec3 vQVector = glm::cross(vTVector, vEdge_01);
	float fV = glm::dot(_tRay.m_vDirection, vQVector) * fInvDeterminant; 
	if ( fV < -0.0001f || (fV + fU) > 1.0001f )
    {
        return false;
    }

	*_vIntersectPoint = _vTrianglePoint_01 + (vEdge_01 * fU) + (vEdge_02 * fV);
	return true;
}

bool CCollisionMgr::Get_CollisionPoint(IVertexBuffer *_pVertexBuffer, CIndexBuffer *_pIndexBuffer, SRay3d& _tRay3d, glm::vec3* _vCollisionPoint)
{
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(_pVertexBuffer->Lock());
    unsigned short* pIndexBufferData = _pIndexBuffer->Get_SourceData();
    unsigned int iNumIndexes = _pIndexBuffer->Get_NumIndexes();
    for(unsigned int index = 0; index < iNumIndexes; index += 3)
    {
        glm::vec3 vPoint_01 = pVertexBufferData[pIndexBufferData[index + 0]].m_vPosition;
        glm::vec3 vPoint_02 = pVertexBufferData[pIndexBufferData[index + 1]].m_vPosition;
        glm::vec3 vPoint_03 = pVertexBufferData[pIndexBufferData[index + 2]].m_vPosition;
            
        if(RayTriangleIntersection(vPoint_01, vPoint_02, vPoint_03, _tRay3d, _vCollisionPoint))
        {
            return true;
        }
    }
    return false;
}

void CCollisionMgr::Add_CollisionListener(ICollisionDelegate *_pOwner)
{
    if(m_pBox2dWorld == NULL)
    {
        return;
    }
    
    m_lCollisionObject.push_back(_pOwner);

    _pOwner->m_pBox2dBodyDef.type = b2_dynamicBody;
    
	_pOwner->m_pBox2dBodyDef.position.Set(_pOwner->Get_OriginPosition().x, _pOwner->Get_OriginPosition().z);
	_pOwner->m_pBox2dBodyDef.userData = _pOwner;
    
    _pOwner->m_pBox2dBody = m_pBox2dWorld->CreateBody(&_pOwner->m_pBox2dBodyDef);
	b2PolygonShape dynamicBox;
    
	dynamicBox.SetAsBox(_pOwner->Get_OriginMaxBound().x - _pOwner->Get_OriginMinBound().x,_pOwner->Get_OriginMaxBound().z - _pOwner->Get_OriginMinBound().z);
	/*b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 2.0f;
	fixtureDef.restitution = 0.7f;*/ 
	_pOwner->m_pBox2dBody->CreateFixture(&dynamicBox, 1);
	//_pOwner->m_pBox2dBody->SetType(b2_dynamicBody);
}

void CCollisionMgr::Remove_CollisionListener(ICollisionDelegate *_pOwner)
{
    std::vector<ICollisionDelegate*>::iterator pBeginIterator = m_lCollisionObject.begin();
    std::vector<ICollisionDelegate*>::iterator pEndIterator = m_lCollisionObject.end();
    while (pBeginIterator != pEndIterator) 
    {
        if(_pOwner == (*pBeginIterator))
        {
            m_pBox2dWorld->DestroyBody(_pOwner->m_pBox2dBody);
            _pOwner->m_pBox2dBody = NULL;
            m_lCollisionObject.erase(pBeginIterator);
            return;
        }
        ++pBeginIterator;
    }
}

void CCollisionMgr::_Update_Box2d(void)
{
    if(m_pBox2dWorld == NULL)
    {
        return;
    }
    
    int32 velocityIterations = 1;
	int32 positionIterations = 1;
    
	m_pBox2dWorld->Step(1.0f / 30.0f, velocityIterations, positionIterations);

    for(unsigned int index = 0; index < m_lCollisionObject.size(); ++index)
    {
        ICollisionDelegate* pOwner = m_lCollisionObject[index];
        pOwner->OnOriginRotationChanged(pOwner->m_pBox2dBody->GetAngle());
        pOwner->OnOriginPositionChanged(glm::vec3(pOwner->m_pBox2dBody->GetPosition().x, 0.0f, pOwner->m_pBox2dBody->GetPosition().y));
    }
    
	/*for(b2Body* pBox2dBody = m_pBox2dWorld->GetBodyList(); pBox2dBody; pBox2dBody = pBox2dBody->GetNext())
	{
		if (pBox2dBody->GetUserData() != NULL)
		{
			ICollisionDelegate* pOwner = static_cast<ICollisionDelegate*>(pBox2dBody->GetUserData());    
            pOwner->OnOriginRotationChanged(pBox2dBody->GetAngle());
            pOwner->OnOriginPositionChanged(glm::vec3(pBox2dBody->GetPosition().x, 0.0f, pBox2dBody->GetPosition().y));
		}
	}*/
}

void CCollisionMgr::Update(void)
{
    _Update_Box2d();
}


