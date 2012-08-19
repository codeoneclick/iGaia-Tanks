//
//  IBatch.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/19/12.
//
//

#ifndef __iGaia__IBatch__
#define __iGaia__IBatch__

#include <iostream>
#include "INode.h"

#include "CVertexBufferPositionColor.h"
#include "CVertexBufferPositionTexcoord.h"
#include "CVertexBufferPositionTexcoordColor.h"
#include "CVertexBufferPositionTexcoordNormal.h"
#include "CVertexBufferPositionTexcoordNormalTangent.h"

class IBatch
{
protected:
    CMaterial* m_pMaterial;
    CMesh* m_pMesh;
public:
    IBatch(void);
    ~IBatch(void);
    virtual void Create(IVertexBuffer::E_VERTEX_BUFFER_MODE _eVertexBufferMode) = 0;
    virtual void PushNodeRef(INode* _pNode) = 0;
    virtual void ResetNodeRef(void) = 0;
    virtual void Update(void) = 0;
    virtual void Render(CShader::E_RENDER_MODE _eMode) = 0;
};

#endif /* defined(__iGaia__IBatch__) */
