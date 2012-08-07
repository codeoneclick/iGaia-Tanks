//
//  CBuilding.h
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#ifndef __iGaia__CBuilding__
#define __iGaia__CBuilding__

#include <iostream>
#include "CSceneMgr.h"

class CBuilding
{
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    INode* m_pModel;
public:
    CBuilding(void);
    ~CBuilding(void);
    void Load(const std::string& _sModelName, const std::string& _sTextureName);
    void Update(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation);
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
};

#endif /* defined(__iGaia__CBuilding__) */
