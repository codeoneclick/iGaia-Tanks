//
//  CParticleEmitterExplosion.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CParticleEmitterExplosion__
#define __iGaia__CParticleEmitterExplosion__
#include <iostream>
#include "CParticleEmitter.h"
class CParticleEmitterExplosion : public CParticleEmitter
{
protected:
    float m_fMoveSpeed;
public:
    CParticleEmitterExplosion(void);
    ~CParticleEmitterExplosion(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    
    void Reset(void) { };
};

#endif /* defined(__iGaia__CParticleEmitterExplosion__) */
