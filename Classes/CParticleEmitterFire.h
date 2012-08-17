//
//  CParticleEmmiterFire.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CParticleEmitterFire__
#define __iGaia__CParticleEmitterFire__

#include <iostream>
#include "CParticleEmitter.h"

class CParticleEmitterFire : public CParticleEmitter
{
protected:
    constexpr static float k_RANDOM_MODIFICATOR = 256.0f;
    constexpr static float k_PARTICLE_START_OFFSET_X = 0.33f;
    constexpr static float k_PARTICLE_START_OFFSET_Z = 0.33f;
    constexpr static float k_PARTICLE_MIN_MOVE_SPEED = 0.0f;
    constexpr static float k_PARTICLE_MAX_MOVE_SPEED = 0.25f;
    float m_fMoveSpeed;
public:
    CParticleEmitterFire(void);
    ~CParticleEmitterFire(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    
    void Start(void);
    void Stop(void);
    
    void Reset(void);
};


#endif /* defined(__iGaia__CParticleEmitterFire__) */
