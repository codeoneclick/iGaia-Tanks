//
//  CParticleEmitterSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CParticleEmitterSettings_PARSER_h
#define CParticleEmitterSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CParticleEmitterSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CParticleEmitterSettings_PARSER(void) {};
    ~CParticleEmitterSettings_PARSER(void) {};

    SParticleEmitterSettings* Deserialize(const std::string& _name);
};


#endif
