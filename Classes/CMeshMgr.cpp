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
    CParser_MDL* parser = new CParser_MDL();
    parser->Load("base_model.mdl");
    if(parser->Get_Status() != IParser::E_STATUS_ERROR)
    {
        m_stub = static_cast<CMesh*>(parser->Commit());
    }
}

CMeshMgr::~CMeshMgr(void)
{
    
}

IResource* CMeshMgr::LoadSync(const std::string &_name)
{
    CMesh* mesh = nullptr;
    if(m_resources.find(_name) != m_resources.end())
    {
        mesh = static_cast<CMesh*>(m_resources[_name]);
        mesh->IncReferenceCount();
    }
    else
    {
        CParser_MDL* parser = new CParser_MDL();
        parser->Load(_name.c_str());
        if(parser->Get_Status() != IParser::E_STATUS_ERROR)
        {
            mesh = static_cast<CMesh*>(parser->Commit());
            mesh->Set_Name(_name);
            m_resources[_name] = mesh;
        }
        else
        {
            mesh = new CMesh(*m_stub);
            mesh->Set_Name(_name);
            mesh->IncReferenceCount();
            m_resources[_name] = mesh;
        }
        SAFE_DELETE(parser);
    }
    return mesh;
}

IResource* CMeshMgr::LoadAsync(const std::string &_name)
{
    CMesh* mesh = nullptr;
    if( m_resources.find(_name) != m_resources.end())
    {
        mesh = static_cast<CMesh*>(m_resources[_name]);
        mesh->IncReferenceCount();
    }
    else
    {
        mesh = new CMesh(*m_stub);
        mesh->Set_Name(_name);
        mesh->IncReferenceCount();
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            CParser_MDL* parser = new CParser_MDL();
            parser->Load(_name.c_str());
            dispatch_async(dispatch_get_main_queue(), ^{
                if(parser->Get_Status() != IParser::E_STATUS_ERROR)
                {
                    mesh->PutInstance(parser->Commit());
                    m_resources[_name] = mesh;
                }
            });
        });
    }
    return mesh;
}

void CMeshMgr::Unload(const std::string& _name)
{
    CMesh* mesh = nullptr;
    if( m_resources.find(_name) != m_resources.end())
    {
        mesh = static_cast<CMesh*>(m_resources[_name]);
        mesh->DecReferenceCount();

        if(mesh->Get_ReferenceCount() == 0)
        {
            SAFE_DELETE(mesh);
            std::map<std::string, IResource*>::iterator iterator = m_resources.find(_name);
            m_resources.erase(iterator);
        }
    }
}
