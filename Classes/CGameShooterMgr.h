//
//  CShootMgr.h
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#ifndef __iGaia__CShootMgr__
#define __iGaia__CShootMgr__

#include <iostream>
#include "CBullet.h"

#define k_MAX_NUM_BULLETS 16

class CGameShooterMgr
{
protected:
    std::vector<CBullet*> m_lUsedBulletsContainer;
    std::vector<CBullet*> m_lUnUsedBulletsContainer;
public:
    CGameShooterMgr(void);
    ~CGameShooterMgr(void);
    
    void Update(void);
    void CreateBullet(const glm::vec3& _vPosition, const glm::vec3& _vDirection);
};

#endif /* defined(__iGaia__CShootMgr__) */
