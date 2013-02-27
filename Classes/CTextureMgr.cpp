//
//  CTextureController.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CTextureMgr.h"
#include "CTexture.h"
#include "CLoadOperation_PVR.h"

CTextureMgr::CTextureMgr(void)
{

}

CTextureMgr::~CTextureMgr(void)
{
    
}

IResource_INTERFACE* CTextureMgr::StartLoadOperation(const std::string& _filename, E_RESOURCE_LOAD_THREAD _thread, CResourceLoadCallback_INTERFACE* _listener)
{
    CTexture* texture = nullptr;
    
    if(_thread == E_RESOURCE_LOAD_THREAD_SYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            texture = static_cast<CTexture*>(m_resourceContainer[_filename]);
            texture->IncReferencesCount();
        }
        else
        {
            CLoadOperation_PVR* operation = new CLoadOperation_PVR();
            operation->Load(_filename);
            if(operation->Get_Status() == E_PARSER_STATUS_DONE)
            {
                texture = static_cast<CTexture*>(operation->Build());
                operation->Dispatch(texture);
                texture->IncReferencesCount();
            }
            delete operation;
        }
    }
    else if(_thread == E_RESOURCE_LOAD_THREAD_ASYNC)
    {
        if(m_resourceContainer.find(_filename) != m_resourceContainer.end())
        {
            CTexture* texture = static_cast<CTexture*>(m_resourceContainer[_filename]);
            Dispatch(_listener, texture);
        }
        else
        {
            if(m_operationsQueue.find(_filename) == m_operationsQueue.end())
            {
                CLoadOperation_PVR* operation = new CLoadOperation_PVR();
                m_operationsQueue.insert(std::make_pair(_filename, operation));
            }

            CLoadOperation_PVR* operation = static_cast<CLoadOperation_PVR*>(m_operationsQueue.find(_filename)->second);
            AddListener(_listener, operation);
        }
    }
    return texture;
}



