//
//  CRenderOperationScreenOutput.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/28/13.
//
//

#ifndef CRenderOperationScreenOutput_h
#define CRenderOperationScreenOutput_h

#include "CMaterial.h"
#include "CMesh.h"

class CRenderOperationScreenOutput
{
private:
    
protected:
    
    CMaterial* m_material;
    ui32 m_frameBufferHandle;
    ui32 m_renderBufferHandle;
    ui32 m_frameWidth;
    ui32 m_frameHeight;
    CMesh* m_mesh;
    
public:
    
    CRenderOperationScreenOutput(ui32 _frameWidth, ui32 _frameHeight, CMaterial* _material, ui32 _frameBufferHandle, ui32 _renderBufferHandle, const std::string& _name);
    ~CRenderOperationScreenOutput(void);
    
    inline CMaterial* Get_Material(void)
    {
        return m_material;
    }
    
    void Bind(void);
    void Unbind(void);
    void Draw(void);
};

#endif 
