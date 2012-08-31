//
//  CWater.h
//  iGaia
//
//  Created by sergey.sergeev on 3/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CWater_h
#define iGaia_CWater_h

#include "INode.h"

class COcean: public INode
{
protected:
    static COcean* m_pInstance;
    void _Load(void* data);
    
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    float m_fWaterHeight;
    
public:
    COcean(void);
    ~COcean(void);
    static COcean* Instance(void);
    void Load(const std::string& _sName, IResource::E_THREAD _eThread){ LOG("Ocean can not create manualy"); } 
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif
