//
//  CSkyBox.h
//  iGaia
//
//  Created by sergey sergeev on 4/26/12.
//
//

#ifndef __iGaia__CSkyBox__
#define __iGaia__CSkyBox__

#include "INode.h"

class CSkyBox : public INode
{
protected:
    static CSkyBox* m_pInstance;
    void _Load(void* data);
public:
    CSkyBox(void);
    ~CSkyBox(void);
    static CSkyBox* Instance(void);
    void Load(const std::string& _sName, IResource::E_THREAD _eThread){ LOG("SkyBox can not create manualy"); } 
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    //void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CSkyBox__) */
