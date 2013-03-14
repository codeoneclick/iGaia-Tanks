//
//  CLandscape.h
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CLandscape_h
#define iGaia_CLandscape_h

#include "CGameObject3d.h"
#include "CHeightmapProcessor.h"
#include "CQuadTree.h"
#include "CLandscapeChunk.h"

class CLandscape : public CGameObject3d
{
private:

    CHeightmapProcessor* m_heightmapProcessor;
    CLandscapeChunk** m_landscapeContainer;
    
    ui32 m_numChunkRows;
    ui32 m_numChunkCells;
    
protected:

    void OnResourceDidLoad(IResource_INTERFACE* _resource);

    void OnUpdate(f32 _deltatime);

    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);

public:

    CLandscape(void);
    ~CLandscape(void);

    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename);
    
    void Set_Camera(CCamera* _camera);
    void Set_Light(CLight* _light);

    void Set_RenderMgr(CRenderMgr* _renderMgr);
    void Set_UpdateMgr(CSceneUpdateMgr* _updateMgr);

    void ListenRenderMgr(bool _value);
    void ListenUpdateMgr(bool _value);

    inline f32* Get_HeightmapData(void)
    {
        assert(m_heightmapProcessor != nullptr);
        assert(m_heightmapProcessor->Get_HeightmapData() != nullptr);
        return m_heightmapProcessor->Get_HeightmapData();
    };

    inline ui32 Get_HeightmapWidth(void)
    {
        assert(m_heightmapProcessor != nullptr);
        assert(m_heightmapProcessor->Get_Width() != 0);
        return m_heightmapProcessor->Get_Width();
    };

    inline ui32 Get_HeightmapHeight(void)
    {
        assert(m_heightmapProcessor != nullptr);
        assert(m_heightmapProcessor->Get_Height() != 0);
        return m_heightmapProcessor->Get_Height();
    };
};

#endif
