//
//  CGrassSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CGrassSettings_PARSER_h
#define CGrassSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CGrassSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CGrassSettings_PARSER(void) {};
    ~CGrassSettings_PARSER(void) {};

    SGrassSettings* Deserialize(const std::string& _name);
};

#endif 
