//
//  HTankSettings_DTO.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/21/13.
//
//

#ifndef HTankSettings_DTO_h
#define HTankSettings_DTO_h

#include "HCommon.h"

struct ITankSettings
{

};

struct STankBodySettings : public ITankSettings
{
    std::string m_tankBodyFilename;
};

struct STankTowerSettings : public ITankSettings
{
    std::string m_tankTowerFilename;
};

struct STankTrackSettings : public ITankSettings
{
    std::string m_tankLeftTrackFilename;
    std::string m_tankRightTrackFilename;
};

struct STankSettings
{
    STankBodySettings m_tankBodySettings;
    STankTowerSettings m_tankTowerSettings;
    STankTrackSettings m_tankTrackSettings;
};



#endif
