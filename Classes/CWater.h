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

class CWater: public INode
{
protected:
    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;
    
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    float m_fWaterHeight;
    
public:
    CWater(void);
    ~CWater(void);
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
