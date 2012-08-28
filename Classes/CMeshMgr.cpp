//
//  CMeshMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMeshMgr.h"
#include "dispatch/dispatch.h"

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

IResource* CMeshMgr::LoadDefault(void)
{
    return m_pDefault;
}

IResource* CMeshMgr::LoadSync(const std::string &_sName)
{
    CMesh* pMesh = nullptr;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
        pMesh->IncRefCount();
    }
    else
    {
        IParser* pParser = new CParser_MDL();
        pParser->Load(_sName.c_str());
        
        if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
        {
            pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
            pMesh->Set_SourceData(pParser->Get_SourceData());
            m_lContainer[_sName] = pMesh;
        }
        else
        {
            pMesh = m_pDefault;
        }
        SAFE_DELETE(pParser);
    }
    return pMesh;
}

void CMeshMgr::LoadAsync(const std::string &_sName, const IResource::EventSignature &_pListener)
{
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        CMesh* pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
        pMesh->IncRefCount();
        _pListener(pMesh);
    }
    else
    {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            CParser_MDL* pParser = new CParser_MDL();
            pParser->Load(_sName.c_str());
            dispatch_async(dispatch_get_main_queue(), ^{
                if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
                {
                    CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
                    pParser->Commit();
                    pMesh->Set_SourceData(pParser->Get_SourceData());
                    m_lContainer[_sName] = pMesh;
                    _pListener(pMesh);
                }
            });
        });
    }
}

IResource* CMeshMgr::Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams)
{
    CMesh* pMesh = NULL;
    
    if(_eThread == IResource::E_THREAD_SYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
        }
        else
        {
            pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
            pMesh->Set_SourceData(m_pDefaultMeshSourceData);
            
            IParser* pParser = new CParser_MDL();
            
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pMesh->Set_SourceData(pParser->Get_SourceData());
            }
            delete pParser;
        }
    }
    else if(_eThread == IResource::E_THREAD_ASYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_MDL();
            }
            pMesh = new CMesh(IResource::E_CREATION_MODE_NATIVE);
            pMesh->Set_SourceData(m_pDefaultMeshSourceData);
            pMesh->Set_Name(_sName);
            pMesh->Add_DelegateOwner(_pDelegate);
            m_lContainer[_sName] = pMesh;
        }
    }
    return pMesh;
}

void CMeshMgr::Unload(const std::string& _sName)
{
    CMesh* pMesh = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
        pMesh->DecRefCount();
        if(pMesh->Get_RefCount() == 0)
        {
            delete pMesh;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}
