//
//  CParticleEmitterTrail.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/12/12.
//
//

#include "CParticleEmitterTrail.h"
#include "CTimer.h"
#include "CSceneMgr.h"

CParticleEmitterTrail::CParticleEmitterTrail(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterTrail::~CParticleEmitterTrail(void)
{
    std::cout<<"[CParticleEmitterTrail::~CParticleEmitterTrail] delete"<<std::endl;
}

void CParticleEmitterTrail::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_vPosition;
        vPosition.x += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.z += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vSize = m_vMinSize;
        m_pParticles[i].m_vColor.a = 255;
        m_pParticles[i].m_bIsDead = false;
        m_pParticles[i].m_cTimeStamp = CTimer::CClock::now();
    }
}

void CParticleEmitterTrail::Start(void)
{
    CParticleEmitter::Start();
}

void CParticleEmitterTrail::Stop(void)
{
    CParticleEmitter::Stop();
}

void CParticleEmitterTrail::Reset(void)
{
    m_bIsDead = false;
    for(unsigned int i = 0; i < m_iNumParticles; ++i)
    {
        glm::vec3 vPosition = m_vPosition;
        vPosition.x += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.z += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vSize = m_vMinSize;
        m_pParticles[i].m_vColor.a = 255;
        m_pParticles[i].m_bIsDead = false;
        m_pParticles[i].m_cTimeStamp = CTimer::CClock::now();
    }
}

void CParticleEmitterTrail::Update(void)
{
    if(m_bIsDead)
    {
        return;
    }
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        m_pParticles[i].m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[i].m_vPosition += m_pParticles[i].m_vVelocity;
        
        if(m_pParticles[i].m_vSize.x < m_vMaxSize.x && m_pParticles[i].m_vSize.y < m_vMaxSize.y)
        {
            m_pParticles[i].m_vSize += m_vMinSize;
        }
        
        CTimer::CTime cCurrentTimeStamp = CTimer::CClock::now();
        int iTimeStampDelta = CTimer::Get_TimeInterval(cCurrentTimeStamp, m_pParticles[i].m_cTimeStamp);
        float fLifeDelta = static_cast<float>(iTimeStampDelta) / static_cast<float>(m_pParticles[i].m_iLifeTime);
        if(fLifeDelta <= 1)
        {
            m_pParticles[i].m_vColor.a = (1 - fLifeDelta) * 255;
        }
        else if(!m_bIsRepeat || m_bIsStop)
        {
            m_pParticles[i].m_bIsDead = true;
        }
        else
        {
            glm::vec3 vPosition = m_vPosition;
            vPosition.x += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
            vPosition.z += _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
            m_pParticles[i].m_vPosition = vPosition;
            m_pParticles[i].m_vSize = m_vMinSize;
            m_pParticles[i].m_vColor.a = 255;
            m_pParticles[i].m_bIsDead = false;
            m_pParticles[i].m_cTimeStamp = CTimer::CClock::now();
        }
    }
    
    CVertexBufferPositionTexcoordColor::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordColor::SVertex*>(m_pMesh->Get_VertexBufferRef()->Lock());
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    
    m_iNumDeadParticles = 0;
    
    for(unsigned int index = 0; index < m_iNumParticles; index++)
    {
        if(m_pParticles[index].m_bIsDead)
        {
            m_iNumDeadParticles++;
            continue;
        }
        
        glm::mat4x4 mWorld = pCamera->Get_BillboardSphericalMatrix(m_pParticles[index].m_vPosition);
        
        glm::vec4 vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 0].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, -m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 1].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 2].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        vTransform = glm::vec4(-m_pParticles[index].m_vSize.x, m_pParticles[index].m_vSize.y, 0.0f, 1.0f);
        vTransform = mWorld * vTransform;
        pVertexBufferData[index * 4 + 3].m_vPosition = glm::vec3(vTransform.x, vTransform.y, vTransform.z);
        
        pVertexBufferData[index * 4 + 0].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 1].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 2].m_vColor = m_pParticles[index].m_vColor;
        pVertexBufferData[index * 4 + 3].m_vColor = m_pParticles[index].m_vColor;
    }
    m_pMesh->Get_VertexBufferRef()->Commit();
    
    if(m_iNumDeadParticles == m_iNumParticles && !m_bIsRepeat && !m_bIsStop)
    {
        m_bIsDead = true;
    }

}



