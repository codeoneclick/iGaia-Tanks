//
//  CBatchMgr.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/19/12.
//
//

#ifndef __iGaia__CBatchMgr__
#define __iGaia__CBatchMgr__

#include <iostream>
#include <unordered_map>
#include "IBatch.h"

class CBatchMgr
{
protected:
    std::unordered_map<std::string, IBatch*> m_lContainer;
public:
    CBatchMgr(void);
    ~CBatchMgr(void);
    void AddToBatchList(const std::string& _sName, INode* _pNode);
    void RemoveFromBatchList(const std::string& _sName, INode* _pNode);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CBatchMgr__) */
