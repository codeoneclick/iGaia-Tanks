//
//  CParticleEmitter.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticleEmitter__
#define __iGaia__CParticleEmitter__

#include <iostream>
#include "INode.h"

#define k_DEFAULT_NUM_PARTICLES 64
#define k_PARTICLE_LIFE_TIME_OFFSET 500

class CParticleEmitter : public INode
{
protected:
    struct SParticle
    {
        glm::vec3 m_vPosition;
        glm::vec3 m_vRotation;
        glm::vec2 m_vSize;
        glm::vec3 m_vVelocity;
        glm::u8vec4 m_vColor;
        int m_iLifeTime;
        int m_iTimeStamp;
        bool m_bIsDead;
    };
    SParticle* m_pParticles;
     
    unsigned int m_iNumParticles;
    unsigned int m_iNumDeadParticles;
    glm::vec2 m_vMinSize;
    glm::vec2 m_vMaxSize;

    int m_iMinLifeTime;
    int m_iMaxLifeTime;

    bool m_bIsRepeat;
    bool m_bIsDead;
    bool m_bIsStop;

    float _Get_RandomFromRange(float _fMin, float _fMax);
public:
    CParticleEmitter(void);
    virtual ~CParticleEmitter(void);
    
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    
    virtual void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);

    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);

    void Set_NumParticles(unsigned int _iNumParticles) { m_iNumParticles = _iNumParticles; }
    void Set_MinSize(glm::vec2 _vSize) { m_vMinSize = _vSize; }
    void Set_MaxSize(glm::vec2 _vSize) { m_vMaxSize = _vSize; }

    void Set_LifeTime(int _iValue) { m_iMinLifeTime = _iValue; m_iMaxLifeTime = _iValue + k_PARTICLE_LIFE_TIME_OFFSET; }

    void Set_IsRepeat(bool _bValue) { m_bIsRepeat = _bValue; }
    bool Get_IsDead(void) { return m_bIsDead; }

    virtual void Start(void) { m_bIsStop = false; }
    virtual void Stop(void) { m_bIsStop = true; }

    virtual void Reset(void);

};

#endif /* defined(__iGaia__CParticleEmitter__) */
