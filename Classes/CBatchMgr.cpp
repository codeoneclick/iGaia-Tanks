//
//  CBatchMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/21/12.
//
//

#include "CBatchMgr.h"

CBatchMgr::CBatchMgr(void)
{
    
}

CBatchMgr::~CBatchMgr(void)
{
    
}

void CBatchMgr::Push(INode *_pNode, CBatch::E_BATCH_MODE _eMode)
{
    std::map<std::string, CBatch*>::iterator pBatchIterator = m_lContainer.find(_pNode->Get_BatchingName());
    if(pBatchIterator == m_lContainer.end())
    {
        m_lContainer[_pNode->Get_BatchingName()] = new CBatch(_eMode);
    }
    m_lContainer[_pNode->Get_BatchingName()]->Push_MeshRef(_pNode);
}

void CBatchMgr::Update(void)
{
    std::map<std::string, CBatch*>::iterator pBatchIteratorBegin = m_lContainer.begin();
    std::map<std::string, CBatch*>::iterator pBatchIteratorEnd = m_lContainer.end();
    
    while (pBatchIteratorBegin != pBatchIteratorEnd)
    {
        pBatchIteratorBegin->second->Reset_MeshRef();
        ++pBatchIteratorBegin;
    }
}

void CBatchMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::map<std::string, CBatch*>::iterator pBatchIteratorBegin = m_lContainer.begin();
    std::map<std::string, CBatch*>::iterator pBatchIteratorEnd = m_lContainer.end();
    
    while (pBatchIteratorBegin != pBatchIteratorEnd)
    {
        pBatchIteratorBegin->second->Update();
        pBatchIteratorBegin->second->Render(_eMode);
        ++pBatchIteratorBegin;
    }
}