//
//  CSceneMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CSceneMgr_h
#define iGaia_CSceneMgr_h

#include "INode.h"
#include "ILight.h"
#include "ICamera.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CHeightMapSetter.h"
#include "CParticleMgr.h"
#include "CDecalMgr.h"
#include "CSpriteMgr.h"
#include "CBatchMgr.h"
#include "CFrustum.h"

class ICharacterController;
class CSceneMgr
{
private:
    static CSceneMgr* m_pInsatnce;
    static const unsigned int k_MAX_LIGHTS; 
    
    std::vector<INode*> m_lContainer;
    std::map<unsigned int, ILight*> m_lLights;
    ILight* m_pGlobalLight;
    INode* m_pSkyBox;
    INode* m_pLandscape;
    INode* m_pOcean;
    ICamera* m_pCamera;
    CFrustum* m_pFrustum;
    
    CRenderMgr* m_pRenderMgr;
    CCollisionMgr* m_pCollisionMgr;
    CParticleMgr* m_pParticleMgr;
    CDecalMgr* m_pDecalMgr;
    CSpriteMgr* m_pSpriteMgr;
    CBatchMgr* m_pBatchMgr;
    CHeightMapSetter* m_pHeightMapSetterRef;
    
    void _DrawSimpleStep(void);
    void _DrawReflectionStep(void);
    void _DrawRefractionStep(void);
    void _DrawScreenNormalMapStep(void);
    void _DrawShadowMapStep(void);
public:
    CSceneMgr(void);
    ~CSceneMgr(void);
    
    static CSceneMgr* Instance(void);
    
    ILight* Get_Light(ILight::E_LIGHT_MODE _eMode, unsigned int _iIndex = 0);
    ICamera* Get_Camera(void) { return m_pCamera; }
    void Set_Camera(ICamera* _pCamera);
    CFrustum* Get_Frustum(void) { return m_pFrustum; }
    
    void Set_GlobalLight(ILight* _pLight) { m_pGlobalLight = _pLight; }
    ILight* Get_GlobalLight(void) { return m_pGlobalLight; }
    
    INode* Add_CustomModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* Add_LandscapeModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* Add_LandscapeGrassModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* Add_OceanModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* Add_SkyBoxModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    
    void Remove_CustomModel(INode* _pNode);
    void Remove_LandscapeModel(INode* _pNode);
    void Remove_LandscapeGrassModel(INode* _pNode);
    void Remove_OceanModel(INode* _pNode);
    void Remove_SkyBoxModel(INode* _pNode);
    
    void AddEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    void RemoveEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    
    ICamera* CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane);
    ICamera* CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, ICharacterController* _pTarget);
    void Remove_Camera(ICamera* _pCamera);
    
    CRenderMgr* Get_RenderMgr(void) { return m_pRenderMgr; }
    CCollisionMgr* Get_CollisionMgr(void) { return m_pCollisionMgr; }
    CParticleMgr* Get_ParticleMgr(void) { return m_pParticleMgr; }
    CDecalMgr* Get_DecalMgr(void) { return m_pDecalMgr; }
    CSpriteMgr* Get_SpriteMgr(void) { return m_pSpriteMgr; }
    CBatchMgr* Get_BatchMgr(void) { return m_pBatchMgr; }
    
    CHeightMapSetter* Get_HeightMapSetterRef(void) { return m_pHeightMapSetterRef; }
    void Set_HeightMapSetterRef(CHeightMapSetter* _pHeightMapSetterRef) { m_pHeightMapSetterRef = _pHeightMapSetterRef; }                                                         
    
    unsigned char Get_UniqueColorId(INode* _pNode);
    
    void Remove_Model(INode *_pNode);
    void Update(void);
    void Render(void);
};

#endif
