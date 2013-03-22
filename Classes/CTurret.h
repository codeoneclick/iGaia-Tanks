//
//  ITankTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef CTurret_h
#define CTurret_h

#include "ISpare.h"

class CTurret : public ISpare
{
private:

protected:

    CShape3d* m_turretShape;

    glm::vec3 m_turretMaxBound;
    glm::vec3 m_turretMinBound;
    glm::vec3 m_turretCenter;

public:

    CTurret(void);
    ~CTurret(void);

    void Load(IRoot* _root, IPanzerSpareSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);

    inline glm::vec3 Get_TurretMaxBound(void)
    {
        return m_turretMaxBound;
    };

    inline glm::vec3 Get_TurretMinBound(void)
    {
        return m_turretMinBound;
    };
    inline glm::vec3 Get_TurretCenter(void)
    {
        return m_turretCenter;
    };
};

#endif 
