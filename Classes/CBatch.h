//
//  CBatch.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/19/12.
//
//

#ifndef __iGaia__CBatch__
#define __iGaia__CBatch__

#include <iostream>
#include "INode.h"

class CBatch
{
protected:
    CMaterial* m_pMaterial;
public:
    CBatch(void);
    ~CBatch(void);
    void AddNode(INode* _pNode);
    void ClearNodes(void);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CBatch__) */
