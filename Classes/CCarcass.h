//
//  ITankBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef CCarcass_h
#define CCarcass_h

#include "ISpare.h"

class CCarcass : public ISpare
{
private:
    
protected:
    
    CShape3d* m_carcassShape;
    
    glm::vec3 m_carcassMaxBound;
    glm::vec3 m_carcassMinBound;
    glm::vec3 m_carcassCenter;
    
public:
    
    CCarcass(void);
    ~CCarcass(void);
    
    void Load(IRoot* _root, IPanzerSpareSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
    
    inline glm::vec3 Get_CarcassMaxBound(void)
    {
        return m_carcassMaxBound;
    };
    
    inline glm::vec3 Get_CarcassMinBound(void)
    {
        return m_carcassMinBound;
    };
    inline glm::vec3 Get_CarcassCenter(void)
    {
        return m_carcassCenter;
    };
};

#endif 
