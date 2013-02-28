//
//  CRenderOperationWorldSpace.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CRenderOperationWorldSpace_h
#define CRenderOperationWorldSpace_h

#include "CMaterial.h"
#include "CRenderCallback.h"

class CRenderOperationWorldSpace
{
private:

protected:
    
    CTexture* m_operatingTexture;
    ui32 m_frameBufferHandle;
    ui32 m_depthBufferHandle;
    ui32 m_frameWidth;
    ui32 m_frameHeight;
    std::map<ui32, std::set<CRenderCallback_INTERFACE*>> m_listeners;
    E_RENDER_MODE_WORLD_SPACE m_mode;

public:

    CRenderOperationWorldSpace(ui32 _frameWidth, ui32 _frameHeight, E_RENDER_MODE_WORLD_SPACE _mode, const std::string& _name);
    ~CRenderOperationWorldSpace(void);

    inline CTexture* Get_OperatingTexture(void)
    {
        return m_operatingTexture;
    }

    void AddEventListener(CRenderCallback_INTERFACE* _listener);
    void RemoveEventListener(CRenderCallback_INTERFACE* _listener);

    void Bind(void);
    void Unbind(void);

    void Draw(void);
};

#endif
