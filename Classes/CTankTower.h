//
//  ITankTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef CTankTower_h
#define CTankTower_h

#include "ITankPart.h"

class CTankTower : public ITankPart
{
private:

protected:

    CShape3d* m_towerPrefab;

    glm::vec3 m_towerMaxBound;
    glm::vec3 m_towerMinBound;
    glm::vec3 m_towerCenter;

public:

    CTankTower(void);
    virtual ~CTankTower(void);

    void Load(IRoot* _root, ITankSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);

    inline glm::vec3 Get_TowerMaxBound(void)
    {
        return m_towerMaxBound;
    };

    inline glm::vec3 Get_TowerMinBound(void)
    {
        return m_towerMinBound;
    };
    inline glm::vec3 Get_TowerCenter(void)
    {
        return m_towerCenter;
    };
};

#endif 
