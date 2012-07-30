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

IResource* CTextureMgr::Load(const std::string& _sName, IResource::E_THREAD _eThread, IDelegate* _pDelegate, const std::map<std::string, std::string>* _lParams)
{
    CTexture* pTexture = NULL;
    
    if(_eThread == IResource::E_THREAD_MAIN)
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
    else if(_eThread == IResource::E_THREAD_BACKGROUND)
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



