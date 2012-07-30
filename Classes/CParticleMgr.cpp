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
    pParticleEmitter->Load("emitter", IResource::E_THREAD_MAIN);
    return pParticleEmitter;
}

CParticleEmitterFireTrail* CParticleMgr::Add_ParticleEmitterFireTrail(unsigned int _iNumParticles, const glm::vec2 &_vMinSize, const glm::vec2 &_vMaxSize, int _iLifeTime, bool _bIsRepeat)
{
    CParticleEmitterFireTrail* pParticleEmitter = new CParticleEmitterFireTrail();
    pParticleEmitter->Set_NumParticles(_iNumParticles);
    pParticleEmitter->Set_MinSize(_vMinSize);
    pParticleEmitter->Set_MaxSize(_vMaxSize);
    pParticleEmitter->Set_LifeTime(_iLifeTime);
    pParticleEmitter->Set_IsRepeat(_bIsRepeat);
    m_lEmitterContainer.push_back(pParticleEmitter);
    pParticleEmitter->Load("emitter", IResource::E_THREAD_MAIN);
    return pParticleEmitter;
}

void CParticleMgr::Remove_ParticleEmitter(CParticleEmitter *_pParticleEmitter)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        if((*pBeginEmitterIterator) == _pParticleEmitter)
        {
            m_lEmitterContainer.erase(pBeginEmitterIterator);
            delete _pParticleEmitter;
            _pParticleEmitter = NULL;
            break;
        }
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Remove_Effect(INode *_pEffect)
{
    
}

void CParticleMgr::Update(void)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Update();
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Render(_eMode);
        ++pBeginEmitterIterator;
    }
}

