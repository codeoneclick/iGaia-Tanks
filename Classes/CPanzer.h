//
//  CTank.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#ifndef CPanzer_h
#define CPanzer_h

#include "ICharacter.h"
#include "CCarcass.h"
#include "CChassis.h"
#include "CTurret.h"
#include "CCollisionCallback.h"

class CPanzer :
public ICharacter
{
private:

protected:

    CCarcass* m_carcass;
    CChassis* m_chassis;
    CTurret* m_turret;
    f32 m_turretRotation;

public:

    CPanzer(void);
    ~CPanzer(void);

    void Load(IRoot* _root, SPanzerSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
};

#endif 
