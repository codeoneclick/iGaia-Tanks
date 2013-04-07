//
//  CGameSettingsMgr.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#ifndef CGameSettingsMgr_h
#define CGameSettingsMgr_h

#include "HGameSettings_DTO.h"

class CGameSettingsMgr
{
private:

protected:

    std::map<std::string, IGameSettings*> m_settingsContainer;

    IGameSettings* Get_CachedSettings(const std::string& _filename);

public:

    CGameSettingsMgr(void);
    ~CGameSettingsMgr(void);

    SPanzerSettings* Get_PanzerSettings(const std::string& _filename);
    SBuildingSettings* Get_BuildingSettigns(const std::string& _filename);
};

#endif 
