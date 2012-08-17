//
//  CParticleEmitterExplosion.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CParticleEmitterExplosion.h"
#include "CTimer.h"

CParticleEmitterExplosion::CParticleEmitterExplosion(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterExplosion::~CParticleEmitterExplosion(void)
{
    std::cout<<"[CParticleEmitterExplosion::CParticleEmitterExplosion] delete"<<std::endl;
}

void CParticleEmitterExplosion::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        vPosition.x = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X , k_PARTICLE_START_OFFSET_X);
        vPosition.z = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z , k_PARTICLE_START_OFFSET_Z);
        vPosition.y = 0.0f;
        m_pParticles[i].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[i].m_vVelocity = glm::vec3(0.0f, 1.0f, 0.0f);
    }
}

void CParticleEmitterExplosion::Start(void)
{
    CParticleEmitter::Start();
    CTimer::CTime cCurrentTimeStamp = CTimer::CClock::now();
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        m_pParticles[i].m_cTimeStamp = cCurrentTimeStamp;
    }
}

void CParticleEmitterExplosion::Stop(void)
{
    CParticleEmitter::Stop();
}

void CParticleEmitterExplosion::Reset(void)
{
    m_bIsDead = false;
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition;
        vPosition.x = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X , k_PARTICLE_START_OFFSET_X);
        vPosition.z = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z , k_PARTICLE_START_OFFSET_Z);
        vPosition.y = 0.0f;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vSize = m_vMinSize;
        m_pParticles[i].m_vColor.a = 255;
        m_pParticles[i].m_bIsDead = false;
    }
}

void CParticleEmitterExplosion::Update(void)
{
    if(m_bIsDead)
    {
        return;
    }
    
    for(unsigned short i = 0; i < m_iNumParticles; i += 6)
    {
        glm::vec3 vPosition = m_pParticles[i + 0].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.x += m_fMoveSpeed;
        m_pParticles[i + 0].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 1].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.x -= m_fMoveSpeed;
        m_pParticles[i + 1].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 2].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.y += m_fMoveSpeed;
        m_pParticles[i + 2].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 3].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.y -= m_fMoveSpeed;
        m_pParticles[i + 3].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 4].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.z += m_fMoveSpeed;
        m_pParticles[i + 4].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 5].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(k_PARTICLE_MIN_MOVE_SPEED * k_RANDOM_MODIFICATOR, k_PARTICLE_MAX_MOVE_SPEED * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
        vPosition.z -= m_fMoveSpeed;
        m_pParticles[i + 5].m_vPosition = vPosition;
        
        for(unsigned short j = i; j < (i + 6); ++j)
        {
            if(m_pParticles[j].m_vSize.x < m_vMaxSize.x && m_pParticles[i].m_vSize.y < m_vMaxSize.y)
            {
                m_pParticles[j].m_vSize += m_vMinSize;
            }
            
            CTimer::CTime cCurrentTimeStamp = CTimer::CClock::now();
            int iTimeStampDelta = CTimer::Get_TimeInterval(cCurrentTimeStamp, m_pParticles[j].m_cTimeStamp); 
            float iLifeDelta = static_cast<float>(iTimeStampDelta) / static_cast<float>(m_pParticles[j].m_iLifeTime);
            if(iLifeDelta <= 1)
            {
                m_pParticles[j].m_vColor.a = (1 - iLifeDelta) * 255;
            }
            else if(!m_bIsRepeat || m_bIsStop)
            {
                m_pParticles[j].m_bIsDead = true;
            }
            else
            {
                glm::vec3 vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
                vPosition.x = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_X * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
                vPosition.z = _Get_RandomFromRange(-k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR, k_PARTICLE_START_OFFSET_Z * k_RANDOM_MODIFICATOR) / k_RANDOM_MODIFICATOR;
                vPosition.y = 0.0f;
                m_pParticles[j].m_vPosition = vPosition;
                m_pParticles[j].m_vSize = m_vMinSize;
                m_pParticles[j].m_vColor.a = 255;
                m_pParticles[j].m_bIsDead = false;
                m_pParticles[j].m_cTimeStamp = CTimer::CClock::now();
            }
        }
    }
    CParticleEmitter::Update();
}





