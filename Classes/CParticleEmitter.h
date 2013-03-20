//
//  CParticleEmitter.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CParticleEmitter_h
#define CParticleEmitter_h

#include "CGameObject3d.h"

struct SParticle
{
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec2 m_size;
    glm::u8vec4 m_color;
    f32 m_timestamp;
};

class CParticleEmitter : public CGameObject3d
{
private:

    SParticleEmitterSettings* m_settings;
    SParticle* m_particles;
    f32 m_lastEmittTimestamp;
    f32 m_lastParticleEmittTime;

    void CreateParticle(ui32 _index);

protected:

    void OnResourceDidLoad(IResource_INTERFACE* _resource);

    void OnUpdate(f32 _deltatime);

    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);

public:
    
    CParticleEmitter(void);
    ~CParticleEmitter(void);

    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename);
};

#endif 
