//
//  CParticleMgr.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticleMgr__
#define __iGaia__CParticleMgr__

#include <iostream>
#include "CParticleEmitter.h"
#include "CParticleEmitterFire.h"
#include "CParticleEmitterFireTrail.h"

class CParticleMgr
{
protected:
    std::vector<CParticleEmitter*> m_lEmitterContainer;
public:
    CParticleMgr(void);
    ~CParticleMgr(void);
    CParticleEmitterFire* Add_ParticleEmitterFire(unsigned int _iNumParticles, const glm::vec2& _vMinSize, const glm::vec2& _vMaxSize, int _iLifeTime, bool _bIsRepeat);
    CParticleEmitterFireTrail* Add_ParticleEmitterFireTrail(unsigned int _iNumParticles, const glm::vec2& _vMinSize, const glm::vec2& _vMaxSize, int _iLifeTime, bool _bIsRepeat);
    void Remove_ParticleEmitter(CParticleEmitter* _pParticleEmitter);
    void Remove_Effect(INode* _pEffect);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CParticleMgr__) */
