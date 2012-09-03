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
#include <future>

CTextureMgr::CTextureMgr(void)
{
    CParser_PVR* pParser = new CParser_PVR();
    pParser->Load("default.pvr");
    pParser->Commit();
    m_pDefaultTextureSourceData = static_cast<CTexture::SSourceData*>(pParser->Get_SourceData());
}

CTexture* Load_Texture(const std::string& _sName)
{
    CTexture* pTexture = new CTexture();
    return pTexture;
}

CTextureMgr::~CTextureMgr(void)
{
    /*
    std::future<CTexture*> pTextureAsyncTask = std::async(std::launch::async, Load_Texture, "default.pvr");
    CTexture* pTexture = pTextureAsyncTask.get();
    */
/*#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        dispatch_async(dispatch_get_main_queue(), ^{
        });
    });
#endif*/
}

IResource::EventHandle CTextureMgr::AddEventListener(const std::string &_sName, IResource::E_THREAD _eThread, const IResource::EventSignature &_pListener, const std::map<std::string, std::string> *_lParams)
{
    IResource::EventHandle iEventHandle = 0;
    if(_eThread == IResource::E_THREAD_SYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            CTexture* pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
            _pListener(pTexture, iEventHandle);
        }
        else
        {
            CParser_PVR* pParser = new CParser_PVR();
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pParser->Commit();
                CTexture*  pTexture = new CTexture();
                pTexture->Set_Name(_sName);
                pTexture->IncRefCount();
                pTexture->Set_SourceData(pParser->Get_SourceData());
                m_lContainer[_sName] = pTexture;
                _pListener(pTexture, iEventHandle);
            }
            SAFE_DELETE(pParser);
        }
    }
    else if(_eThread == IResource::E_THREAD_ASYNC)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            CTexture*  pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
            _pListener(pTexture, iEventHandle);
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_PVR();
            }
            CTexture* pTexture = new CTexture();
            pTexture->Set_Name(_sName);
            iEventHandle = pTexture->AddEventListener(_pListener);
            m_lContainer[_sName] = pTexture;
        }
    }
    return iEventHandle;
}

/*void CTextureMgr::Unload(const std::string& _sName)
{
    std::unordered_map<std::string, IResource*>::iterator pTexture = m_lContainer.find(_sName);
    if(pTexture != m_lContainer.end())
    {
        static_cast<CTexture*>(pTexture->second)->DecRefCount();
        if(static_cast<CTexture*>(pTexture->second)->Get_RefCount() == 0 && static_cast<CTexture*>(pTexture->second)->Get_Handle() != m_pDefaultTextureSourceData->m_hTextureHanlde)
        {
            SAFE_DELETE(pTexture->second);
            m_lContainer.erase(pTexture);
        }
    }
}*/



