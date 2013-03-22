//
//  CSceneContainer.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CSceneContainer_h
#define CSceneContainer_h

#include "HCommon.h"
#include "CCamera.h"
#include "CLight.h"
#include "CGameObject3d.h"

class CSceneContainer
{
private:
    
    std::set<CGameObject3d*> m_gameObjects3dContainer;
    std::set<CCamera*> m_camerasContainer;
    std::set<CLight*> m_lightsContainer;
    
protected:

public:
    
    CSceneContainer(void) {};
    ~CSceneContainer(void);

    void AddGameObject3d(CGameObject3d* _gameObject3d);
    void RemoveGameObject3d(CGameObject3d* _gameObject3d);

    void AddCamera(CCamera* _camera);
    void RemoveCamera(CCamera* _camera);

    void AddLight(CLight* _light);
    void RemoveLight(CLight* _light);
    
};

#endif 
