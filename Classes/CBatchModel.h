//
//  CBatchModel
//  iGaia
//
//  Created by Sergey Sergeev on 8/19/12.
//
//

#ifndef __iGaia__CBatchModel__
#define __iGaia__CBatchModel__

#include <iostream>
#include "IBatch.h"

class CBatchModel : public IBatch
{
protected:
    CMaterial* m_pMaterial;
    CMesh* m_pMesh;
public:
    CBatchModel(void);
    ~CBatchModel(void);
    void Create(IVertexBuffer::E_VERTEX_BUFFER_MODE _eVertexBufferMode);
    void PushNodeRef(INode* _pNode);
    void ResetNodeRef(void);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CBatch__) */
