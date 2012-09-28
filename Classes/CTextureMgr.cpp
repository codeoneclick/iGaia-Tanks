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
    CParser_PVR* parser = new CParser_PVR();
    parser->Load("stub.pvr");
    if(parser->Get_Status() != IParser::E_STATUS_ERROR)
    {
        m_stub = static_cast<CTexture*>(parser->Commit());
    }
}

CTextureMgr::~CTextureMgr(void)
{
    
}

IResource* CTextureMgr::LoadSync(const std::string &_name)
{
    CTexture* texture = nullptr;
    if(m_resources.find(_name) != m_resources.end())
    {
        texture = static_cast<CTexture*>(m_resources[_name]);
        texture->IncReferenceCount();
    }
    else
    {
        CParser_PVR* parser = new CParser_PVR();
        parser->Load(_name.c_str());
        if(parser->Get_Status() != IParser::E_STATUS_ERROR)
        {
            texture = static_cast<CTexture*>(parser->Commit());
            texture->Set_Name(_name);
            m_resources[_name] = texture;
        }
        else
        {
            texture = new CTexture(*m_stub);
            texture->Set_Name(_name);
            texture->IncReferenceCount();
            m_resources[_name] = texture;
        }
        SAFE_DELETE(parser);
    }
    return texture;
}

IResource* CTextureMgr::LoadAsync(const std::string &_name)
{
    CTexture* texture = nullptr;
    if( m_resources.find(_name) != m_resources.end())
    {
        texture = static_cast<CTexture*>(m_resources[_name]);
        texture->IncReferenceCount();
    }
    else
    {
        texture = new CTexture(*m_stub);
        texture->Set_Name(_name);
        texture->IncReferenceCount();
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            CParser_PVR* parser = new CParser_PVR();
            parser->Load(_name.c_str());
            dispatch_async(dispatch_get_main_queue(), ^{
                if(parser->Get_Status() != IParser::E_STATUS_ERROR)
                {
                    texture->PutInstance(parser->Commit());
                    m_resources[_name] = texture;
                }
            });
        });
    }
    return texture;
}

void CTextureMgr::Unload(const std::string& _name)
{
    CTexture* texture = nullptr;
    if( m_resources.find(_name) != m_resources.end())
    {
        texture = static_cast<CTexture*>(m_resources[_name]);
        texture->DecReferenceCount();
        
        if(texture->Get_ReferenceCount() == 0)
        {
            SAFE_DELETE(texture);
            std::map<std::string, IResource*>::iterator iterator = m_resources.find(_name);
            m_resources.erase(iterator);
        }
    }
}



