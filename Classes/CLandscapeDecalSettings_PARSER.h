//
//  CLandscapeDecalSettings_PARSER.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#ifndef CLandscapeDecalSettings_PARSER_h
#define CLandscapeDecalSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CLandscapeDecalSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CLandscapeDecalSettings_PARSER(void) = default;
    ~CLandscapeDecalSettings_PARSER(void) = default;

    SLandscapeDecalSettings* Deserialize(const std::string& _name);
    
};

#endif 
