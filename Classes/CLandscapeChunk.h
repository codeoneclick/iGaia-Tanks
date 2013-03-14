//
//  CLandscapeChunk.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/14/13.
//
//

#ifndef CLandscapeChunk_h
#define CLandscapeChunk_h

#include "CGameObject3d.h"
#include "CQuadTree.h"

class CLandscapeChunk : public CGameObject3d
{
private:
    
    friend class CLandscape;
    CQuadTree* m_quadTree;
    
protected:
    
    void OnResourceDidLoad(IResource_INTERFACE* _resource);
    
    void OnUpdate(f32 _deltatime);
    
    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);
    
public:
    
    CLandscapeChunk(void);
    ~CLandscapeChunk(void);
    
    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename)
    {
        assert(false);
    };
    
    void Load(CMesh* _mesh, CMaterial** _materials, ui32 _width, ui32 _height);
};

#endif 
