//
//  CMeshComposite.h
//  iGaia
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMeshComposite_h
#define iGaia_CMeshComposite_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CMesh.h"

class CMeshComposite
{
private:
    static CMeshComposite* m_pInstance;
protected:
    std::map<IResource::E_STANDART_MODEL, CMesh*> m_lContainer;
public:
    CMeshComposite(void);
    ~CMeshComposite(void);
    static CMeshComposite* Instance(void);
    CMesh* Get_Mesh(IResource::E_STANDART_MODEL _eModel);
};

#endif
