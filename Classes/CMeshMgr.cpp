//
//  CMeshMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMeshMgr.h"

CMeshMgr::CMeshMgr(void)
{
    CParser_MDL* pParser = new CParser_MDL();
    pParser->Load("base_model.mdl");
    pParser->Commit();
    m_pDefaultMeshSourceData = static_cast<CMesh::SSourceData*>(pParser->Get_SourceData());
}

CMeshMgr::~CMeshMgr(void)
{
    
}

IResource::EventHandle CMeshMgr::AddEventListener(const std::string &_sName, IResource::E_THREAD _eThread, const IResource::EventSignature &_pListener, const std::map<std::string, std::string> *_lParams)
{
    IResource::EventHandle iEventHandle = 0;
    if(_eThread == IResource::E_THREAD_SYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            CMesh* pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
            _pListener(pMesh, iEventHandle);
        }
        else
        {
            IParser* pParser = new CParser_MDL();
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
                pMesh->Set_Name(_sName);
                pMesh->Set_SourceData(pParser->Get_SourceData());
                m_lContainer[_sName] = pMesh;
                _pListener(pMesh, iEventHandle);
            }
            SAFE_DELETE(pParser);
        }
    }
    else if(_eThread == IResource::E_THREAD_ASYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            CMesh* pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_MDL();
            }
            CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
            pMesh->Set_Name(_sName);
            iEventHandle = pMesh->AddEventListener(_pListener);
            m_lContainer[_sName] = pMesh;
        }
    }
    return iEventHandle;
}

void CMeshMgr::Unload(const std::string& _sName)
{
    std::unordered_map<std::string, IResource*>::iterator pMesh = m_lContainer.find(_sName);
    if(pMesh != m_lContainer.end())
    {
        static_cast<CMesh*>((*pMesh).second)->DecRefCount();
        if(static_cast<CMesh*>((*pMesh).second)->Get_RefCount() == 0)
        {
            SAFE_DELETE(((*pMesh).second));
            m_lContainer.erase(pMesh);
        }
    }
}
