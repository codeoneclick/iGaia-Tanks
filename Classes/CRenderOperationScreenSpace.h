//
//  CRenderOperationScreenSpace.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CRenderOperationScreenSpace_h
#define CRenderOperationScreenSpace_h

#include "CMaterial.h"
#include "CMesh.h"
#include "CShaderComposite.h"

class CRenderOperationScreenSpace
{
private:

protected:
    
    CTexture* m_operatingTexture;
    CMaterial* m_material;
    ui32 m_frameBufferHandle;
    ui32 m_depthBufferHandle;
    ui32 m_frameWidth;
    ui32 m_frameHeight;
    CMesh* m_mesh;

public:

    CRenderOperationScreenSpace(ui32 _frameWidth, ui32 _frameHeight, E_RENDER_MODE_SCREEN_SPACE _mode, CMaterial* _material, const std::string& _name);
    ~CRenderOperationScreenSpace(void);
    
    inline CTexture* Get_OperatingTexture(void)
    {
        return m_operatingTexture;
    }

    inline CMaterial* Get_Material(void)
    {
        return m_material;
    }

    void Bind(void);
    void Unbind(void);

    void Draw(void);
};

#endif 
