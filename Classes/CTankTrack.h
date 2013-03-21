//
//  ITankTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef CTankTrack_h
#define CTankTrack_h

#include "ITankPart.h"

class CTankTrack : public ITankPart
{
private:

protected:
    
    CShape3d* m_pLeftTrackPrefab;
    CShape3d* m_pRightTrackPrefab;
    
    glm::vec3 m_vLeftTrackMaxBound;
    glm::vec3 m_vLeftTrackMinBound;
    glm::vec3 m_vLeftTrackCenter;
    
    glm::vec3 m_vRightTrackMaxBound;
    glm::vec3 m_vRightTrackMinBound;
    glm::vec3 m_vRightTrackCenter;
    
public:
    
    CTankTrack(void);
    virtual ~CTankTrack(void);

    void Load(IRoot* _root, ITankSettings* _settings);

    void Set_Position(const glm::vec3& _position);
    void Set_Rotation(const glm::vec3& _rotation);
    
    inline glm::vec3 Get_LeftTrackTowerMaxBound(void)
    {
        return m_vLeftTrackMaxBound;
    };
    
    inline glm::vec3 Get_LeftTrackTowerMinBound(void)
    {
        return m_vLeftTrackMinBound;
    };
    
    inline glm::vec3 Get_LeftTrackTowerCenterBound(void)
    {
        return m_vLeftTrackCenter;
    };
    
    inline glm::vec3 Get_RightTrackTowerMaxBound(void)
    {
        return m_vRightTrackMaxBound;
    };
    
    inline glm::vec3 Get_RightTrackTowerMinBound(void)
    {
        return m_vRightTrackMinBound;
    };
    
    inline glm::vec3 Get_RightTrackTowerCenterBound(void)
    {
        return m_vRightTrackCenter;
    };
};

#endif /* defined(__iGaia__ITankTrack__) */
