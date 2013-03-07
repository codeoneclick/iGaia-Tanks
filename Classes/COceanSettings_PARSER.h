//
//  COceanSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef COceanSettings_PARSER_h
#define COceanSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class COceanSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    COceanSettings_PARSER(void) = default;
    ~COceanSettings_PARSER(void) = default;

    SOceanSettings* Deserialize(const std::string& _name);
};

#endif 
