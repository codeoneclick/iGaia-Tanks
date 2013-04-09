//
//  CShape3d.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CShape3d_h
#define CShape3d_h

#include "CGameObject3d.h"

class CShape3d : public CGameObject3d
{
private:

protected:

    void OnResourceDidLoad(TSharedPtrResource _resource);

    void OnUpdate(f32 _deltatime);

    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);

public:

    CShape3d(void);
    ~CShape3d(void);

    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename);
};


#endif 
