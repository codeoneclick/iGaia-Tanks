//
//  CGameObjectSettings.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/6/13.
//
//

#ifndef CGameObjectSettings_PARSER_h
#define CGameObjectSettings_PARSER_h

#include "HCommon.h"
#include "HSettings_DTO.h"

class CGameObjectSettings_PARSER
{
private:

    static std::map<std::string, GLenum> m_glEnumContainer;

protected:

public:

    CGameObjectSettings_PARSER(void);
    ~CGameObjectSettings_PARSER(void) {};

    std::vector<const SMaterialSettings*> Deserialize(pugi::xml_node const& _settingsNode);
};

#endif
