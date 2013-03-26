//
//  CSceneGraph.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CSceneGraph_h
#define CSceneGraph_h

#include "CCamera.h"
#include "CLight.h"
#include "CShape3d.h"
#include "CLandscape.h"
#include "CLandscapeDecal.h"
#include "COcean.h"
#include "CParticleEmitter.h"
#include "CRenderMgr.h"
#include "CSceneUpdateMgr.h"
#include "CCollisionMgr.h"
#include "CGuiMgr.h"

class CSceneGraph
{
private:

    CCamera* m_camera;
    CLight* m_light;

    CLandscape* m_landscape;
    COcean* m_ocean;

    std::set<CShape3d*> m_shapes3dContainer;
    std::set<CParticleEmitter*> m_particleEmittersContainer;
    std::set<CLandscapeDecal*> m_landscapeDecalsContainer;

protected:

    CRenderMgr* m_renderMgr;
    CSceneUpdateMgr* m_updateMgr;
    CCollisionMgr* m_collisionMgr;
    CGuiMgr* m_guiMgr;

public:

    CSceneGraph(void);
    virtual ~CSceneGraph(void);

    void Set_Camera(CCamera* _camera);
    void Set_Light(CLight* _light);

    void Set_Landscape(CLandscape* _landscape);
    void Set_Ocean(COcean* _ocean);

    void InsertShape3d(CShape3d* _shape3d);
    void RemoveShape3d(CShape3d* _shape3d);

    void InsertParticleEmitter(CParticleEmitter* _particleEmitter);
    void RemoveParticleEmitter(CParticleEmitter* _particleEmitter);

    void InsertLandscapeDecal(CLandscapeDecal* _landscapeDecal);
    void RemoveLandscapeDecal(CLandscapeDecal* _landscapeDecal);

    void InsertCollider(CCollisionCallback_INTERFACE* _collider, bool _isStatic);
    void RemoveCollider(CCollisionCallback_INTERFACE* _collider);
};


#endif 
