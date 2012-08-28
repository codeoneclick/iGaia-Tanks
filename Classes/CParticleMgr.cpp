//
//  CParticleMgr.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleMgr.h"

CParticleMgr::CParticleMgr(void)
{

}


CParticleMgr::~CParticleMgr(void)
{
    
}

CParticleEmitterFire* CParticleMgr::Add_ParticleEmitterFire(unsigned int _iNumParticles,const glm::vec2& _vMinSize,const glm::vec2& _vMaxSize, int _iLifeTime, bool _bIsRepeat)
{
    CParticleEmitterFire* pParticleEmitter = new CParticleEmitterFire();
    pParticleEmitter->Set_NumParticles(_iNumParticles);
    pParticleEmitter->Set_MinSize(_vMinSize);
    pParticleEmitter->Set_MaxSize(_vMaxSize);
    pParticleEmitter->Set_LifeTime(_iLifeTime);
    pParticleEmitter->Set_IsRepeat(_bIsRepeat);
    m_lEmitterContainer.push_back(pParticleEmitter);
    pParticleEmitter->Load("emitter", IResource::E_THREAD_ASYNC);
    return pParticleEmitter;
}

CParticleEmitterExplosion* CParticleMgr::Add_ParticleEmitterExplosion(unsigned int _iNumParticles, const glm::vec2 &_vMinSize, const glm::vec2 &_vMaxSize, int _iLifeTime, bool _bIsRepeat)
{
    CParticleEmitterExplosion* pParticleEmitter = new CParticleEmitterExplosion();
    pParticleEmitter->Set_NumParticles(_iNumParticles);
    pParticleEmitter->Set_MinSize(_vMinSize);
    pParticleEmitter->Set_MaxSize(_vMaxSize);
    pParticleEmitter->Set_LifeTime(_iLifeTime);
    pParticleEmitter->Set_IsRepeat(_bIsRepeat);
    m_lEmitterContainer.push_back(pParticleEmitter);
    pParticleEmitter->Load("emitter", IResource::E_THREAD_ASYNC);
    return pParticleEmitter;
}

CParticleEmitterTrail* CParticleMgr::Add_ParticleEmitterTrail(unsigned int _iNumParticles, const glm::vec2 &_vMinSize, const glm::vec2 &_vMaxSize, int _iLifeTime, bool _bIsRepeat)
{
    CParticleEmitterTrail* pParticleEmitter = new CParticleEmitterTrail();
    pParticleEmitter->Set_NumParticles(_iNumParticles);
    pParticleEmitter->Set_MinSize(_vMinSize);
    pParticleEmitter->Set_MaxSize(_vMaxSize);
    pParticleEmitter->Set_LifeTime(_iLifeTime);
    pParticleEmitter->Set_IsRepeat(_bIsRepeat);
    m_lEmitterContainer.push_back(pParticleEmitter);
    pParticleEmitter->Load("emitter", IResource::E_THREAD_ASYNC);
    return pParticleEmitter;
}

void CParticleMgr::Remove_ParticleEmitter(CParticleEmitter *_pParticleEmitter)
{
    for(size_t index = 0; index < m_lEmitterContainer.size(); ++index)
    {
        if(m_lEmitterContainer[index] == _pParticleEmitter)
        {
            SAFE_DELETE(m_lEmitterContainer[index]);
            m_lEmitterContainer.erase(m_lEmitterContainer.begin() + index);
        }
    }
}

void CParticleMgr::Remove_Effect(INode *_pEffect)
{
    
}

void CParticleMgr::Update(void)
{
    for(size_t index = 0; index < m_lEmitterContainer.size(); ++index)
    {
        m_lEmitterContainer[index]->Update();
    }
}

void CParticleMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    for(size_t index = 0; index < m_lEmitterContainer.size(); ++index)
    {
        m_lEmitterContainer[index]->Render(_eMode);
    }
}






