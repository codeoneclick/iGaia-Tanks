//
//  CShaderComposite.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CShaderComposite_h
#define CShaderComposite_h

#include "CShader.h"

class CShaderComposite
{
private:
    
protected:
    
    std::map<E_SHADER, CShader*> m_shadersContainer;
    
public:
    
    CShaderComposite(void);
    ~CShaderComposite(void);
    
    CShader* Get_Shader(E_SHADER _shader);
};

#endif
