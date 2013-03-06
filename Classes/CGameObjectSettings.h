//
//  CGameObjectSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CGameObjectSettings_h
#define CGameObjectSettings_h

#include "HCommon.h"
#include "HSettings_DTO.h"

class CGameObjectSettings
{
private:

protected:

public:

    CGameObjectSettings(void);
    ~CGameObjectSettings(void);

    std::vector<const SMaterialSettings*> DeserializeSettings(pugi::xml_node const& _settingsNode);
};

#endif
