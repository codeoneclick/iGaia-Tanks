//
//  CParticleEmitterFireTrail.h
//  iGaia
//
//  Created by sergey sergeev on 6/12/12.
//
//

#ifndef __iGaia__CParticleEmitterFireTrail__
#define __iGaia__CParticleEmitterFireTrail__

#include <iostream>
#include "CParticleEmitter.h"

#define k_RANDOM_MODIFICATOR 256.0f

#define k_PARTICLE_START_OFFSET_X 0.15f
#define k_PARTICLE_START_OFFSET_Z 0.15f

#define k_PARTICLE_MIN_MOVE_SPEED 0.0f
#define k_PARTICLE_MAX_MOVE_SPEED 0.25f

class CParticleEmitterFireTrail : public CParticleEmitter
{
protected:
    float m_fMoveSpeed;
public:
    CParticleEmitterFireTrail(void);
    ~CParticleEmitterFireTrail(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    
    void Start(void);
    void Stop(void);
    
    void Reset(void);
};

#endif /* defined(__iGaia__CParticleEmitterFireTrail__) */
