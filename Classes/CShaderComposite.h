//
//  CShaderComposite.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CShaderComposite_h
#define iGaia_CShaderComposite_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CShader.h"
#include "CParser_GLSL.h"
#include "IResource.h"

class CShaderComposite
{
private:
    static CShaderComposite* m_instance;
protected:
    std::map<CShader::E_SHADER, CShader*> m_shaders;
public:
    CShaderComposite(void);
    ~CShaderComposite(void);
    static CShaderComposite* Instance();
    CShader* Get_Shader(CShader::E_SHADER _shader);
};

#endif
