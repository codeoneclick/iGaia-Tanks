//
//  CTankSettings_PARSER.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/22/13.
//
//

#ifndef CPanzerSettings_PARSER_h
#define CPanzerSettings_PARSER_h

#include "HGameSettings_DTO.h"

class CPanzerSettings_PARSER
{
private:

protected:

public:

    CPanzerSettings_PARSER(void) {};
    ~CPanzerSettings_PARSER(void) {};

    SPanzerSettings* Deserialize(const std::string& _filename);
};

#endif