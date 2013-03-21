//
//  ITankBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef ITankBody_h
#define ITankBody_h

#include "ITankPart.h"

class CTankBody : public ITankPart
{
private:
    
protected:
    
    CShape3d* m_bodyPrefab;
    
    glm::vec3 m_bodyMaxBound;
    glm::vec3 m_bodyMinBound;
    glm::vec3 m_bodyCenter;
    
public:
    
    CTankBody(void);
    virtual ~CTankBody(void);
    
    void Load(IRoot* _root, ITankSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
    
    inline glm::vec3 Get_BodyMaxBound(void)
    {
        return m_bodyMaxBound;
    };
    
    inline glm::vec3 Get_BodyMinBound(void)
    {
        return m_bodyMinBound;
    };
    inline glm::vec3 Get_BodyCenter(void)
    {
        return m_bodyCenter;
    };
};

#endif 
