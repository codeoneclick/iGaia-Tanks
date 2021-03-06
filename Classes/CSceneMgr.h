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
#include "CFrustum.h"
#include "CEnvironment.h"

class ICharacterController;
class CSceneMgr
{
private:
    static CSceneMgr* m_pInstance;
    
    std::vector<INode*> m_lContainer;
    ILight* m_pLight;
    ICamera* m_pCamera;
    CEnvironment* m_pEnvironment;
    
    CRenderMgr* m_pRenderMgr;
    CCollisionMgr* m_pCollisionMgr;
    CParticleMgr* m_pParticleMgr;
    CDecalMgr* m_pDecalMgr;
    CSpriteMgr* m_pSpriteMgr;
    
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
    
    ILight* Get_Light(void) { return m_pLight; }
    void Set_Light(ILight* _pLight) { m_pLight = _pLight; }
    
    INode* Add_CustomModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_SYNC);
    void Remove_CustomModel(INode* _pNode);
    void LoadEnvironment(const std::string& _sName);
    void UnloadEnvironment(void);
    
    void AddEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    void RemoveEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    
    ICamera* CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane);
    ICamera* CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, ICharacterController* _pTarget);
    
    CRenderMgr* Get_RenderMgr(void) { return m_pRenderMgr; }
    CCollisionMgr* Get_CollisionMgr(void) { return m_pCollisionMgr; }
    CParticleMgr* Get_ParticleMgr(void) { return m_pParticleMgr; }
    CDecalMgr* Get_DecalMgr(void) { return m_pDecalMgr; }
    CSpriteMgr* Get_SpriteMgr(void) { return m_pSpriteMgr; }
    
    CHeightMapSetter* Get_HeightMapSetterRef(void) { return m_pHeightMapSetterRef; }
    void Set_HeightMapSetterRef(CHeightMapSetter* _pHeightMapSetterRef) { m_pHeightMapSetterRef = _pHeightMapSetterRef; }                                                         
    
    unsigned char Get_UniqueColorId(INode* _pNode);
    
    void Remove_Model(INode *_pNode);
    void Update(void);
    void Render(void);
};

#endif
