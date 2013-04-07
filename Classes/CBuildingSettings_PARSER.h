//
//  CBuildingSettings_PARSER.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 4/6/13.
//
//

#ifndef CBuildingSettings_PARSER_h
#define CBuildingSettings_PARSER_h

#include "HGameSettings_DTO.h"

class CBuildingSettings_PARSER
{
private:
    
protected:
    
public:
    
    CBuildingSettings_PARSER(void) {};
    ~CBuildingSettings_PARSER(void) {};
    
    SBuildingSettings* Deserialize(const std::string& _filename);
};


#endif
