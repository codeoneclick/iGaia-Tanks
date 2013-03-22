//
//  CSkyDomeSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CSkyDomeSettings_PARSER_h
#define CSkyDomeSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CSkyDomeSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CSkyDomeSettings_PARSER(void) {};
    ~CSkyDomeSettings_PARSER(void) {};

    SSkyDomeSettings* Deserialize(const std::string& _name);
};

#endif
