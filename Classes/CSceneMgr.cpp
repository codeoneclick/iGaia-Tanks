//
//  CSceneMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneMgr.h"
#include "CModel.h"
#include "CLandscape.h"
#include "CLandscapeEdges.h"
#include "CGrass.h"
#include "COcean.h"
#include "CSkyBox.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CCameraFree.h"
#include "CCameraTarget.h"
#include "CWindow.h"
#include "CRenderMgr.h"
#include "CLightPoint.h"
#include "CTimer.h"
#include "CSettings.h"
#include "dispatch/dispatch.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr(void)
{
    m_pCamera = nullptr;
    m_pLight = nullptr;
    m_pHeightMapSetterRef = nullptr;
    m_pEnvironment = nullptr;
    
    m_pRenderMgr = new CRenderMgr();
    m_pCollisionMgr = new CCollisionMgr();
    m_pParticleMgr = new CParticleMgr();
    m_pDecalMgr = new CDecalMgr();
    m_pSpriteMgr = new CSpriteMgr();
}

CSceneMgr::~CSceneMgr(void)
{
    
}

CSceneMgr* CSceneMgr::Instance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CSceneMgr();
    }    
    return m_pInstance;
}


INode* CSceneMgr::Add_CustomModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CModel();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    return pNode;
}

void CSceneMgr::Remove_CustomModel(INode *_pNode)
{
    Remove_Model(_pNode);
}

void CSceneMgr::LoadEnvironment(const std::string &_sName)
{
    m_pEnvironment = new CEnvironment();
    m_pEnvironment->Load("environment");
    m_pCollisionMgr->Create_Box2dWorld();
}

void CSceneMgr::UnloadEnvironment(void)
{
    SAFE_DELETE(m_pEnvironment);
}

void CSceneMgr::AddEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->AddEventListener(_pNode, _eEvent);
}

void CSceneMgr::RemoveEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->RemoveEventListener(_pNode, _eEvent);
}

ICamera* CSceneMgr::CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane)
{
    CCameraFree* pCamera = new CCameraFree();
    pCamera->Create(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
    m_pCamera = pCamera;
    return pCamera;
}

ICamera* CSceneMgr::CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, ICharacterController *_pTarget)
{
    CCameraTarget* pCamera = new CCameraTarget();
    pCamera->Create(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
    pCamera->Set_Target(_pTarget);
    m_pCamera = pCamera;
    return pCamera;
}

void CSceneMgr::Remove_Model(INode *_pNode)
{
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    INode* pNode = NULL;
    
    while (pBIterator != pEIterator)
    {
        pNode = (*pBIterator);
        if(pNode == _pNode)
        {
            m_lContainer.erase(pBIterator);
            SAFE_DELETE(pNode);
            break;
        }
        ++pBIterator;
    }
}

void CSceneMgr::Update(void)
{
    m_pCamera->Update();
    m_pCollisionMgr->Update();
    
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    while (pBIterator != pEIterator)
    {
        (*pBIterator)->Update();
        ++pBIterator;
    }
    
    m_pEnvironment->Update();

    m_pDecalMgr->Update();
    m_pParticleMgr->Update();
}

void CSceneMgr::_DrawSimpleStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    
    m_pEnvironment->Get_SkyBox()->Render(CShader::E_RENDER_MODE_SIMPLE);
    
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_SIMPLE);
        ++pBeginNodeIterator;
    }
    
    m_pEnvironment->Get_Landscape()->Render(CShader::E_RENDER_MODE_SIMPLE);
    
    m_pDecalMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    
    m_pEnvironment->Get_LandscapeEdges()->Render(CShader::E_RENDER_MODE_SIMPLE);
    m_pEnvironment->Get_Ocean()->Render(CShader::E_RENDER_MODE_SIMPLE);
    m_pEnvironment->Get_Grass()->Render(CShader::E_RENDER_MODE_SIMPLE);
    
    m_pParticleMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
}

void CSceneMgr::_DrawReflectionStep(void)
{
    float fWaterLevel = -0.1f;
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    vCameraPosition.y = -vCameraPosition.y + fWaterLevel * 2.0;
    glm::vec3 vCameraLookAt = m_pCamera->Get_LookAt();
    vCameraLookAt.y = -vCameraLookAt.y + fWaterLevel * 2.0f;
    m_pCamera->Set_View(glm::lookAt(vCameraPosition, vCameraLookAt, glm::vec3(0.0f,-1.0f,0.0f)));
    
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderMode(CShader::E_RENDER_MODE_REFLECTION))
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_REFLECTION);
        }
        ++pBeginNodeIterator;
    }

    m_pEnvironment->Get_Landscape()->Update();
    m_pEnvironment->Get_Landscape()->Render(CShader::E_RENDER_MODE_REFLECTION);
    
    m_pCamera->Set_View(glm::lookAt(m_pCamera->Get_Position(), m_pCamera->Get_LookAt(), glm::vec3(0.0f,1.0f,0.0f)));
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
}

void CSceneMgr::_DrawRefractionStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
    
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderMode(CShader::E_RENDER_MODE_REFRACTION))
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_REFRACTION);
        }
        ++pBeginNodeIterator;
    }
    
    m_pEnvironment->Get_Landscape()->Update();
    m_pEnvironment->Get_Landscape()->Render(CShader::E_RENDER_MODE_REFRACTION);
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
}

void CSceneMgr::_DrawScreenNormalMapStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
    
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP))
        {
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
        }
        ++pBeginNodeIterator;
    }
    
    m_pEnvironment->Get_Landscape()->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);

    m_pParticleMgr->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
}

void CSceneMgr::Render(void)
{
    CSettings::g_iCurrentTrianglesPerFrame = 0;
    
    if(CSettings::g_bOceanReflection)
    {
        _DrawReflectionStep();
    }
        
    if(CSettings::g_bOceanRefraction)
    {
        _DrawRefractionStep();
    }
    
    if(CSettings::g_bEdgeDetect)
    {
        _DrawScreenNormalMapStep();
    }
    
    _DrawSimpleStep();
    
    m_pRenderMgr->DrawResult();
    
    CSettings::g_iTotalTriagnlesPerFrame = CSettings::g_iCurrentTrianglesPerFrame;
    
    static int iLastTime = 0;
    int iCurrentTime = CTimer::Instance()->Get_TickCount();
    ++CSettings::g_iCurrentFramesPerSecond;
    
    if(iCurrentTime - iLastTime > 1000 )
    {
        iLastTime = iCurrentTime;
        CSettings::g_iTotalFramesPerSecond = CSettings::g_iCurrentFramesPerSecond;
        CSettings::g_iCurrentFramesPerSecond = 0;
    }

}



