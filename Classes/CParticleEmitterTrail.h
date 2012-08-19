//
//  CParticleEmitterTrail.h
//  iGaia
//
//  Created by sergey sergeev on 6/12/12.
//
//

#ifndef __iGaia__CParticleEmitterTrail__
#define __iGaia__CParticleEmitterTrail__

#include <iostream>
#include "CParticleEmitter.h"

class CParticleEmitterTrail : public CParticleEmitter
{
protected:
    constexpr static float k_RANDOM_MODIFICATOR = 256.0f;
    constexpr static float k_PARTICLE_START_OFFSET_X = 0.15f;
    constexpr static float k_PARTICLE_START_OFFSET_Z = 0.15f;
    constexpr static float k_PARTICLE_MIN_MOVE_SPEED = 0.0f;
    constexpr static float k_PARTICLE_MAX_MOVE_SPEED = 0.25f;
    float m_fMoveSpeed;
public:
    CParticleEmitterTrail(void);
    ~CParticleEmitterTrail(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    
    void Start(void);
    void Stop(void);
    
    void Reset(void);
};

#endif /* defined(__iGaia__CParticleEmitterTrail__) */
