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
    
    m_sColliderIdStr = "building_collider";
}

CBuilding::~CBuilding(void)
{
    CSceneMgr::Instance()->Get_CollisionMgr()->Remove_CollisionListener(this);
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
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_REFLECTION, true);
    m_pModel->Set_RenderMode(CShader::E_RENDER_MODE_REFRACTION, true);
    
    m_vMaxBound = m_pModel->Get_BoundingBox()->Get_MaxBound();
    m_vMinBound = m_pModel->Get_BoundingBox()->Get_MinBound();
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Add_CollisionListener(this, true);
}

void CBuilding::Set_Position(const glm::vec3& _vPosition)
{
    if(m_pModel != NULL)
    {
        m_pModel->Set_Position(_vPosition);
    }
    Set_OriginPosition(_vPosition);
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

void CBuilding::OnCollision(ICollisionDelegate *_pCollider)
{
    
}

void CBuilding::OnOriginPositionChanged(const glm::vec3& _vPosition)
{
    Set_Position(glm::vec3(_vPosition.x, m_vPosition.y, _vPosition.z));
}

void CBuilding::OnOriginRotationChanged(float _fAngleY)
{
    Set_Rotation(m_vRotation);
}

