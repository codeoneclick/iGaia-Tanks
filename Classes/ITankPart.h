//
//  ITankPart.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef ITankPart_h
#define ITankPart_h

#include "IRoot.h"
#include "HTankSettings_DTO.h"

class ITankPart
{
private:
    
protected:
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    
public:
    
    ITankPart(void);
    virtual ~ITankPart(void);

    virtual void Load(IRoot* _root, ITankSettings* _settings) = 0;
    
    virtual void Set_Position(const glm::vec3& _position) = 0;
    virtual void Set_Rotation(const glm::vec3& _rotation) = 0;
};

#endif 
