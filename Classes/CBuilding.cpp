//
//  CBuilding.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#include "CBuilding.h"
#include "CModel.h"

CBuilding::CBuilding(void)
{
    m_pModel = NULL;
}

CBuilding::~CBuilding(void)
{
    CSceneMgr::Instance()->Remove_Model(m_pModel);
}   

void CBuilding::Load(const std::string& _sModelName, const std::string& _sTextureName)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->Add_CustomModel(_sModelName, IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture(_sTextureName, 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_REFLECTION, IResource::E_SHADER_MODEL);
    m_pModel->Set_Shader(CShader::E_RENDER_MODE_REFRACTION, IResource::E_SHADER_MODEL);
    m_pModel->Create_BoundingBox();
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_REFLECTION, true);
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_REFRACTION, true);
}

void CBuilding::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pModel != NULL)
    {
        m_pModel->Set_Position(_vPosition);
    }
    m_vPosition = _vPosition;
}

void CBuilding::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pModel != NULL)
    {
        m_pModel->Set_Rotation(_vRotation);
    }
    m_vRotation = _vRotation;
}


void CBuilding::Update(void)
{

}
