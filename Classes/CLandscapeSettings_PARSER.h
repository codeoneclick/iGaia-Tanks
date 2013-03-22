//
//  CLandscapeSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CLandscapeSettings_PARSER_h
#define CLandscapeSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CLandscapeSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CLandscapeSettings_PARSER(void) {};
    ~CLandscapeSettings_PARSER(void) {};

    SLandscapeSettings* Deserialize(const std::string& _name);
};

#endif 
