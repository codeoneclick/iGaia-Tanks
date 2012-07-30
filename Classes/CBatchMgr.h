//
//  CBatchMgr.h
//  iGaia
//
//  Created by sergey sergeev on 6/21/12.
//
//

#ifndef __iGaia__CBatchMgr__
#define __iGaia__CBatchMgr__

#include <iostream>
#include "CBatch.h"

class CBatchMgr
{
protected:
    std::map<std::string, CBatch*> m_lContainer;
public:
    CBatchMgr(void);
    ~CBatchMgr(void);
    
    void Push(INode* _pNode, CBatch::E_BATCH_MODE _eMode);
    
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CBatchMgr__) */
