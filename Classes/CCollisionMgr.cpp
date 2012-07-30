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
}

CCollisionMgr::~CCollisionMgr()
{
    
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

void CCollisionMgr::Update()
{
    
}


