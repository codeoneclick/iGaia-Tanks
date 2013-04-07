//
//  HTankSettings_DTO.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/21/13.
//
//

#ifndef HGameSettings_DTO_h
#define HGameSettings_DTO_h

#include "HCommon.h"

struct IGameSettings
{

};

struct IPanzerSpareSettings
{

};

struct SCarcassSettings : public IPanzerSpareSettings
{
    std::string m_carcassSettingsFilename;
};

struct STurretSettings : public IPanzerSpareSettings
{
    std::string m_turretSettingsFilename;
};

struct SChassisSettings : public IPanzerSpareSettings
{
    std::string m_leftChassisSettingsFilename;
    std::string m_rightChassisSettingsFilename;
};

struct SPanzerSettings : public IGameSettings
{
    SCarcassSettings m_carcassSettings;
    STurretSettings m_turretSettings;
    SChassisSettings m_chassisSettings;
};

struct SBuildingSettings : public IGameSettings
{
    std::string m_shapeSettingsFilename;
};

#endif
