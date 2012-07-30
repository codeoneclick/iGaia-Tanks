//
//  CParser_MDL.h
//  iGaia
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CParser_MDL_h
#define iGaia_CParser_MDL_h

#include "stdlib.h"
#include <string>
#include "CMesh.h"
#include "IParser.h"

class CParser_MDL : public IParser
{
private:
    CMesh::SSourceData* m_pSourceData;
    char* m_pData;
public:
    CParser_MDL(void);
    virtual ~CParser_MDL(void);
    
    virtual void  Load(const std::string& _sName);
    virtual void* Get_SourceData() { return m_pSourceData; }
    virtual void  Commit(void);
};


#endif
