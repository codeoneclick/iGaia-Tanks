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
#include "CRenderMgr.h"
#include "CSceneUpdateMgr.h"

class CSceneGraph
{
private:

    CCamera* m_camera;
    CLight* m_light;

    CLandscape* m_landscape;

    std::set<CShape3d*> m_shapes3dContainer;

protected:

    CRenderMgr* m_renderMgr;
    CSceneUpdateMgr* m_updateMgr;

public:

    CSceneGraph(void);
    virtual ~CSceneGraph(void);

    void Set_Camera(CCamera* _camera);
    void Set_Light(CLight* _light);

    void Set_Landscape(CLandscape* _landscape);

    void InsertShape3d(CShape3d* _shape3d);
    void RemoveShape3d(CShape3d* _shape3d);
};


#endif 
