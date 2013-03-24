//
//  ITankPart.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef ISpare_h
#define ISpare_h

#include "IRoot.h"
#include "HGameSettings_DTO.h"

class ISpare
{
private:
    
protected:
    
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    
public:
    
    ISpare(void);
    virtual ~ISpare(void);

    virtual void Load(IRoot* _root, IPanzerSpareSettings* _settings) = 0;
    
    virtual void Set_Position(const glm::vec3& _position) = 0;
    virtual void Set_Rotation(const glm::vec3& _rotation) = 0;
};

#endif 
