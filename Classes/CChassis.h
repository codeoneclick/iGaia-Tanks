//
//  ITankTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef CChassis_h
#define CChassis_h

#include "ISpare.h"

class CChassis : public ISpare
{
private:

protected:
    
    CShape3d* m_leftChassisShape;
    CShape3d* m_rightChassisShape;
    
    glm::vec3 m_leftChassisMaxBound;
    glm::vec3 m_leftChassisMinBound;
    glm::vec3 m_leftChassisCenter;
    
    glm::vec3 m_rightChassisMaxBound;
    glm::vec3 m_rightChassisMinBound;
    glm::vec3 m_rightChassisCenter;
    
public:
    
    CChassis(void);
    ~CChassis(void);

    void Load(IRoot* _root, IPanzerSpareSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
    
    inline glm::vec3 Get_LeftChassisMaxBound(void)
    {
        return m_leftChassisMaxBound;
    };
    
    inline glm::vec3 Get_LeftChassisMinBound(void)
    {
        return m_leftChassisMinBound;
    };
    
    inline glm::vec3 Get_LeftChassisCenterBound(void)
    {
        return m_leftChassisCenter;
    };
    
    inline glm::vec3 Get_RightChassisMaxBound(void)
    {
        return m_rightChassisMaxBound;
    };
    
    inline glm::vec3 Get_RightChassisMinBound(void)
    {
        return m_rightChassisMinBound;
    };
    
    inline glm::vec3 Get_RightChassisCenterBound(void)
    {
        return m_rightChassisCenter;
    };
};

#endif
