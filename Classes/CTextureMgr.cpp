//
//  CTextureController.cpp
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTextureMgr.h"
#include <cmath>
#include "stdlib.h"
#include <algorithm>
#include "dispatch/dispatch.h"

CTextureMgr::CTextureMgr(void)
{
    CParser_PVR* pParser = new CParser_PVR();
    pParser->Load("default.pvr");
    pParser->Commit();
    m_pDefaultTextureSourceData = static_cast<CTexture::SSourceData*>(pParser->Get_SourceData());
}

CTextureMgr::~CTextureMgr(void)
{
    
}

IResource* CTextureMgr::LoadDefault(void)
{
    return m_pDefault;
}

IResource* CTextureMgr::LoadSync(const std::string &_sName)
{
    CTexture* pTexture = nullptr;
    if(m_lContainer.find(_sName) != m_lContainer.end())
    {
        pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
        pTexture->IncRefCount();
    }
    else
    {
        CParser_PVR* pParser = new CParser_PVR();
        pParser->Load(_sName.c_str());
        if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
        {
            pTexture = new CTexture();
            pParser->Commit();
            pTexture->Set_SourceData(pParser->Get_SourceData());
            m_lContainer[_sName] = pTexture;
        }
        else
        {
            pTexture = m_pDefault;
        }
        SAFE_DELETE(pParser);
    }
    return pTexture;
}

void CTextureMgr::LoadAsync(const std::string &_sName, const IResource::EventSignature &_pListener)
{
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        CTexture*  pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
        pTexture->IncRefCount();
        _pListener(pTexture);
    }
    else
    {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            CParser_PVR* pParser = new CParser_PVR();
            pParser->Load(_sName.c_str());
            dispatch_async(dispatch_get_main_queue(), ^{
                if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
                {
                    CTexture* pTexture = new CTexture();
                    pParser->Commit();
                    pTexture->Set_SourceData(pParser->Get_SourceData());
                    m_lContainer[_sName] = pTexture;
                    _pListener(pTexture);
                }
            });
        });
    }
}

IResource* CTextureMgr::Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams)
{
    CTexture* pTexture = NULL;
    
    if(_eThread == IResource::E_THREAD_SYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
        }
        else
        {
            pTexture = new CTexture();
            pTexture->Set_SourceData(m_pDefaultTextureSourceData);
            CParser_PVR* pParser = new CParser_PVR();
            pParser->Load(_sName.c_str());
            pParser->Set_Params(_lParams);
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pParser->Commit();
                pTexture->Set_SourceData(pParser->Get_SourceData());
            }
            delete pParser;
            m_lContainer[_sName] = pTexture;
        }
    }
    else if(_eThread == IResource::E_THREAD_ASYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_PVR();
                m_lTaskPool[_sName]->Set_Params(_lParams);
            }
            pTexture = new CTexture();
            pTexture->Set_SourceData(m_pDefaultTextureSourceData);
            pTexture->Set_Name(_sName);
            pTexture->Add_DelegateOwner(_pDelegate);
            m_lContainer[_sName] = pTexture;
        }
    }

    return pTexture;
}

void CTextureMgr::Unload(const std::string& _sName)
{
    CTexture* pTexture = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
        pTexture->DecRefCount();
        
        if(pTexture->Get_RefCount() == 0 && pTexture->Get_Handle() != m_pDefaultTextureSourceData->m_hTextureHanlde)
        {
            delete pTexture;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}



