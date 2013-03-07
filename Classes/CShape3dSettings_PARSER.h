//
//  CShape3dSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CShape3dSettings_PARSER_h
#define CShape3dSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"
#include "CGameObjectSettings_PARSER.h"

class CShape3dSettings_PARSER
{
private:

protected:

    CGameObjectSettings_PARSER m_gameObjectSettings;

public:

    CShape3dSettings_PARSER(void) = default;
    ~CShape3dSettings_PARSER(void) = default;

    SShape3dSettings* Deserialize(const std::string& _name);
};

#endif
