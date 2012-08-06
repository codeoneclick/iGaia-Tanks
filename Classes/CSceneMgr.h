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
    static CSceneMgr* m_pInstance;
    
    std::vector<INode*> m_lContainer;
    ILight* m_pLight;
    INode* m_pSkyBox;
    INode* m_pLandscape;
    INode* m_pLandscapeEdges;
    INode* m_pOcean;
    INode* m_pGrass;
    ICamera* m_pCamera;
    
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
    
    ICamera* Get_Camera(void) { return m_pCamera; }
    void Set_Camera(ICamera* _pCamera);
    
    ILight* Get_Light(void) { return m_pLight; }
    void Set_Light(ILight* _pLight) { m_pLight = _pLight; }
    
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
