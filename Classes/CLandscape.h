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

class CLandscape : public CGameObject3d
{
private:

    CHeightmapProcessor* m_heightmapProcessor;

    CQuadTree* m_quadTree;

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
};

#endif
