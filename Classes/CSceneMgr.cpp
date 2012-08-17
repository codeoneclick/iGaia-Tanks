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

#ifdef OS_IPHONE
#include "CCommon_IOS.h"
#endif

CSceneMgr* CSceneMgr::m_pInstance = NULL;

CSceneMgr::CSceneMgr(void)
{
    m_pCamera = NULL;
    m_pHeightMapSetterRef = NULL;
    m_pSkyBox = NULL;
    m_pLandscape = NULL;
    m_pLandscapeEdges = NULL;
    m_pOcean = NULL;
    
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
    if(m_pInstance == NULL)
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

INode* CSceneMgr::Add_LandscapeModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CLandscape();
    m_lContainer.push_back(pNode);

	std::string filePath = k_RES_MODELES_PATH + _sName;
#ifdef OS_IPHONE
	filePath = Get_ResourceFileName(_sName); 
#endif

    pNode->Load(filePath, _eThread);
    m_pLandscape = pNode;
    m_pLandscapeEdges = static_cast<CLandscape*>(pNode)->Get_LandscapeEdges();
    m_lContainer.push_back(m_pLandscapeEdges);
    m_pLandscapeEdges->Load(filePath, _eThread);
    return pNode;
}

INode* CSceneMgr::Add_LandscapeGrassModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CGrass();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    m_pGrass = pNode;
    return pNode;
}

INode* CSceneMgr::Add_OceanModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new COcean();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    m_pOcean = pNode;
    return pNode;
}

INode* CSceneMgr::Add_SkyBoxModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CSkyBox();
    pNode->Load(_sName, _eThread);
    m_pSkyBox = pNode;
    return pNode;
}

void CSceneMgr::Remove_CustomModel(INode *_pNode)
{
    Remove_Model(_pNode);
}

void CSceneMgr::Remove_LandscapeModel(INode *_pNode)
{
    Remove_Model( static_cast<CLandscape*>(_pNode)->Get_LandscapeEdges());
    m_pLandscapeEdges = NULL;
    Remove_Model(_pNode);
    m_pLandscape = NULL;
}

void CSceneMgr::Remove_LandscapeGrassModel(INode *_pNode)
{
    Remove_Model(_pNode);
    m_pGrass = NULL;
}

void CSceneMgr::Remove_OceanModel(INode *_pNode)
{
    Remove_Model(_pNode);
    m_pOcean = NULL;
}

void CSceneMgr::Remove_SkyBoxModel(INode *_pNode)
{
    delete m_pSkyBox;
    m_pSkyBox = NULL;
}

void CSceneMgr::AddEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->AddEventListener(_pNode, _eEvent);
}

void CSceneMgr::RemoveEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->RemoveEventListener(_pNode, _eEvent);
}

void CSceneMgr::Set_Camera(ICamera* _pCamera)
{
    m_pCamera = _pCamera;
}

ICamera* CSceneMgr::CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane)
{
    CCameraFree* pCamera = new CCameraFree();
    pCamera->Create(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
    return pCamera;
}

ICamera* CSceneMgr::CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, ICharacterController *_pTarget)
{
    CCameraTarget* pCamera = new CCameraTarget();
    pCamera->Create(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
    pCamera->Set_Target(_pTarget);
    return pCamera;
}

void CSceneMgr::Remove_Camera(ICamera *_pCamera)
{
    SAFE_DELETE(_pCamera);
    m_pCamera = NULL;
}

void CSceneMgr::Remove_Model(INode *_pNode)
{
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index] == _pNode)
        {
            SAFE_DELETE(m_lContainer[index]);
            m_lContainer.erase(m_lContainer.begin() + index);
        }
    }
}

void CSceneMgr::Update(void)
{
    if(m_pCamera != NULL)
    {
        m_pCamera->Update();
    }
    
    /*std::map<int,int> cTempMap;
    for(int i = 0; i < 1000000; ++i)
    {
        cTempMap[i] = i;
    }
    
    uint64_t iFirstTime = CTimer::Instance()->Get_TickCount();
    for (auto& i : cTempMap)
    {
        i.second = 1;
    }
    uint64_t iSecondTime = CTimer::Instance()->Get_TickCount();
    std::cout<<"[CSceneMgr::Update] C++11 Time "<<iSecondTime - iFirstTime<<std::endl;
    
    iFirstTime = CTimer::Instance()->Get_TickCount();
    std::map<int,int>::iterator iterator_01 = cTempMap.begin();
    std::map<int,int>::iterator iretator_02 = cTempMap.end();
    while (iterator_01 != iretator_02)
    {
        (*iterator_01).second = 1;
        ++iterator_01;
    }
    iSecondTime = CTimer::Instance()->Get_TickCount();
    std::cout<<"[CSceneMgr::Update] C++98 Time "<<iSecondTime - iFirstTime<<std::endl;*/
    
    /*iFirstTime = CTimer::Instance()->Get_TickCount();
    for(unsigned int i =0; i < cTempVector.size(); ++i)
    {
        cTempVector[i] = 1;
    }
    iSecondTime = CTimer::Instance()->Get_TickCount();
    std::cout<<"[CSceneMgr::Update] Indexes C++98 Time "<<iSecondTime - iFirstTime<<std::endl;*/

    
    /*for(INode* &pNode : m_lContainer)
    {
        pNode->Update();
    }*/
    
    //std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    //std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        m_lContainer[index]->Update();
    }

    if(m_pCollisionMgr != NULL)
    {
        m_pCollisionMgr->Update();
    }
    
    if(m_pDecalMgr != NULL)
    {
        m_pDecalMgr->Update();
    }
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Update();
    }
    
    if(m_pSpriteMgr != NULL)
    {
        m_pSpriteMgr->Update();
    }
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Set_Position(m_pCamera->Get_Position());
        m_pSkyBox->Update();
    }
}

void CSceneMgr::_DrawSimpleStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    for(INode* &pNode : m_lContainer)
    {
        if(pNode == m_pOcean || pNode == m_pLandscapeEdges || pNode == m_pGrass)
        {
            continue;
        }
        pNode->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pDecalMgr != NULL)
    {
        m_pDecalMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pLandscapeEdges != NULL)
    {
        m_pLandscapeEdges->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pOcean != NULL)
    {
        m_pOcean->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pGrass != NULL)
    {
        m_pGrass->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pSpriteMgr != NULL)
    {
        m_pSpriteMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
}

void CSceneMgr::_DrawReflectionStep(void)
{
    float fWaterLevel = -0.1f;
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
    
    glm::vec3 vCameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    if(m_pCamera != NULL)
    {
        vCameraPosition = m_pCamera->Get_Position();
    }
    
    vCameraPosition.y = -vCameraPosition.y + fWaterLevel * 2.0;
    
    glm::vec3 vCameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    if(m_pCamera != NULL)
    {
         vCameraLookAt = m_pCamera->Get_LookAt();
    }
   
    vCameraLookAt.y = -vCameraLookAt.y + fWaterLevel * 2.0f;
    
    if(m_pCamera != NULL)
    {
        m_pCamera->Set_View(glm::lookAt(vCameraPosition, vCameraLookAt, glm::vec3(0.0f,-1.0f,0.0f)));
    }
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Update();
        m_pSkyBox->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index]->Get_RenderMode(CShader::E_RENDER_MODE_REFLECTION))
        {
            m_lContainer[index]->Update();
            m_lContainer[index]->Render(CShader::E_RENDER_MODE_REFLECTION);
        }
    }
    if(m_pCamera != NULL)
    {
        m_pCamera->Set_View(glm::lookAt(m_pCamera->Get_Position(), m_pCamera->Get_LookAt(), glm::vec3(0.0f,1.0f,0.0f)));
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
}

void CSceneMgr::_DrawRefractionStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index]->Get_RenderMode(CShader::E_RENDER_MODE_REFRACTION))
        {
            m_lContainer[index]->Update();
            m_lContainer[index]->Render(CShader::E_RENDER_MODE_REFRACTION);
        }
    }
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
}

void CSceneMgr::_DrawScreenNormalMapStep(void)
{
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
    for(size_t index = 0; index < m_lContainer.size(); ++index)
    {
        if(m_lContainer[index]->Get_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP))
        {
            m_lContainer[index]->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
        }
    }
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
}

void CSceneMgr::Render(void)
{
    CSettings::g_iCurrentTrianglesPerFrame = 0;
    
    if(m_pHeightMapSetterRef != NULL && !m_pHeightMapSetterRef->Get_IsTextureDetailCreated())
    {
        m_pHeightMapSetterRef->Draw_TextureDetail();
    }
    
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
    
    static CTimer::CTime cLastTime;
    CTimer::CTime cCurrentTime = CTimer::CClock::now();
    ++CSettings::g_iCurrentFramesPerSecond;
    if(CTimer::Get_TimeInterval(cCurrentTime, cLastTime) > 1000 )
    {
        cLastTime = CTimer::CClock::now();
        CSettings::g_iTotalFramesPerSecond = CSettings::g_iCurrentFramesPerSecond;
        CSettings::g_iCurrentFramesPerSecond = 0;
    }

}



