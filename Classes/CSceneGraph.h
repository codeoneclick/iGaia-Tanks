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
#include "CRenderMgr.h"
#include "CSceneUpdateMgr.h"

class CSceneGraph
{
private:

    CCamera* m_camera;
    CLight* m_light;

    std::set<CShape3d*> m_shapes3dContainer;

protected:

    CRenderMgr* m_renderMgr;
    CSceneUpdateMgr* m_updateMgr;

public:

    CSceneGraph(void);
    ~CSceneGraph(void);

    inline void Set_RenderMgr(CRenderMgr* _renderMgr)
    {
        assert(m_renderMgr == nullptr);
        assert(_renderMgr != nullptr);
        m_renderMgr = _renderMgr;
    };
    
    inline void Set_UpdateMgr(CSceneUpdateMgr* _updateMgr)
    {
        assert(m_updateMgr == nullptr);
        assert(_updateMgr != nullptr);
        m_updateMgr = _updateMgr;
    };

    void Set_Camera(CCamera* _camera);
    void Set_Light(CLight* _light);

    void InsertShape3d(CShape3d* _shape3d);
    void RemoveShape3d(CShape3d* _shape3d);
};


#endif 
