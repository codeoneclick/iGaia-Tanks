//
//  CBillboard.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CBillboard.h"

CBillboard::CBillboard(void)
{
    
}

CBillboard::~CBillboard(void)
{
    
}

void CBillboard::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    
}

void CBillboard::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CBillboard::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    
}

void CBillboard::Update(void)
{
    INode::Update();
}

void CBillboard::Render(CShader::E_RENDER_MODE _eMode)
{
    
}