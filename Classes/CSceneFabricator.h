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
#include "CSceneContainer.h"
#include "CResourceMgrsFacade.h"
#include "CShaderComposite.h"

class CSceneFabricator
{
private:

protected:
    
    CSceneContainer* m_sceneContainer;
    CShaderComposite* m_shaderComposite;
    CResourceMgrsFacade* m_resourceMgrsFacade;
    
public:

    CSceneFabricator(void);
    ~CSceneFabricator(void);

    inline void Set_ShaderComposite(CShaderComposite* _shaderComposite)
    {
        m_shaderComposite = _shaderComposite;
    }

    CCamera* CreateCamera(f32 _fov, f32 _near, f32 _far,const glm::vec4& _viewport);
    CLight* CreateLight(void);

    CShape3d* CreateShape3d(const std::string& _filename);
};

#endif 
