//
//  ICharacter.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#ifndef ICharacter_h
#define ICharacter_h

#include "HCommon.h"

class ICharacter
{
private:

protected:

    glm::vec3 m_position;
    glm::vec3 m_rotation;

public:

    ICharacter(void);
    virtual ~ICharacter(void);

    virtual void Set_Position(const glm::vec3& _position) = 0;
    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };

    virtual void Set_Rotation(const glm::vec3& _rotation) = 0;
    inline glm::vec3 Get_Rotation(void)
    {
        return m_rotation;
    };
};

#endif 
