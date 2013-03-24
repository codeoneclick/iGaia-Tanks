//
//  CSceneFabricator.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CSceneFabricator_h
#define CSceneFabricator_h

#include "CCamera.h"
#include "CLight.h"
#include "CShape3d.h"
#include "CParticleEmitter.h"
#include "CLandscape.h"
#include "CLandscapeDecal.h"
#include "COcean.h"
#include "CSceneContainer.h"
#include "CResourceMgrsFacade.h"
#include "CShaderComposite.h"

class CSceneFabricator
{
private:

    CSceneContainer* m_sceneContainer;
    CResourceMgrsFacade* m_resourceMgrsFacade;
    
protected:
    
    CShaderComposite* m_shaderComposite;
    
public:

    CSceneFabricator(void);
    virtual ~CSceneFabricator(void);

    CCamera* CreateCamera(f32 _fov, f32 _near, f32 _far,const glm::vec4& _viewport);
    CLight* CreateLight(void);

    CShape3d* CreateShape3d(const std::string& _filename);
    void DeleteShape3d(CShape3d* _shape3d);

    CParticleEmitter* CreateParticleEmitter(const std::string& _filename);
    void DeleteParticleEmitter(CParticleEmitter* _particleEmitter);

    CLandscape* CreateLandscape(const std::string& _filename);
    void DeleteLandscape(CLandscape* _landscape);

    CLandscapeDecal* CreateLandscapeDecal(const std::string& _filename);
    void DeleteLandscapeDecal(CLandscapeDecal* _landscapeDecal);

    COcean* CreateOcean(const std::string& _filename);
    void DeleteOcean(COcean* _ocean);
};

#endif 
