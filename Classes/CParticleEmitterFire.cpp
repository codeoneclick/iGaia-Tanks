//
//  ~CParticleEmitterFire.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CParticleEmitterFire.h"
#include "CTimer.h"

CParticleEmitterFire::CParticleEmitterFire(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterFire::~CParticleEmitterFire(void)
{
    std::cout<<"[CParticleEmitterFire::~CParticleEmitterFire] delete"<<std::endl;
}

void CParticleEmitterFire::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        vPosition.x = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.z = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vVelocity = glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

void CParticleEmitterFire::Start(void)
{
    CParticleEmitter::Start();
}

void CParticleEmitterFire::Stop(void)
{
    CParticleEmitter::Stop();
}

void CParticleEmitterFire::Reset(void)
{
    CParticleEmitter::Reset();
}

void CParticleEmitterFire::Update(void)
{
    if(m_bIsDead)
    {
        return;
    }
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        m_pParticles[i].m_vVelocity = glm::vec3(0.0f, m_fMoveSpeed, 0.0f);
        m_pParticles[i].m_vPosition += m_pParticles[i].m_vVelocity;
        
        if(m_pParticles[i].m_vSize.x < m_vMaxSize.x && m_pParticles[i].m_vSize.y < m_vMaxSize.y)
        {
            m_pParticles[i].m_vSize += m_vMinSize;
        }
        
        int iCurrentTimeStamp = CTimer::Instance()->Get_TickCount();
        int iTimeStampDelta = iCurrentTimeStamp - m_pParticles[i].m_iTimeStamp;
        float iLifeDelta = static_cast<float>(iTimeStampDelta) / static_cast<float>(m_pParticles[i].m_iLifeTime);
        if(iLifeDelta <= 1)
        {
            m_pParticles[i].m_vColor.a = (1 - iLifeDelta) * 255;
        }
        else if(!m_bIsRepeat || m_bIsStop)
        {
            m_pParticles[i].m_bIsDead = true;
        }
        else
        {
            glm::vec3 vPosition;
            vPosition.x = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
            vPosition.z = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
            vPosition.y = 0.0f;
            m_pParticles[i].m_vPosition = vPosition;
            m_pParticles[i].m_vSize = m_vMinSize;
            m_pParticles[i].m_vColor.a = 255;
            m_pParticles[i].m_bIsDead = false;
            m_pParticles[i].m_iTimeStamp = iCurrentTimeStamp;
        }
    }
    CParticleEmitter::Update();
}





