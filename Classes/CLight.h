//
//  CLight.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CLight_h
#define CLight_h

#include "HCommon.h"

class CLight
{
private:

protected:

    glm::vec3 m_position;

public:

    CLight(void);
    ~CLight(void) {};

    inline void Set_Position(const glm::vec3& _position)
    {
        m_position = _position;
    };

    inline glm::vec3 Get_Position(void)
    {
        return m_position;
    };
};

#endif 
