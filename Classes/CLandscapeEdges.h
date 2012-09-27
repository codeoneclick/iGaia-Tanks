//
//  CLandscapeEdges.h
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#ifndef __iGaia__CLandscapeEdges__
#define __iGaia__CLandscapeEdges__

#include "INode.h"

class CLandscapeEdges : public INode
{
protected:
    static CLandscapeEdges* m_pInstance;
    void _Load(void* data);
    unsigned int m_iWidth;
    unsigned int m_iHeight;
    glm::vec2 m_vHeight;
public:
    CLandscapeEdges(void);
    ~CLandscapeEdges(void);
    static CLandscapeEdges* Instance(void);
    void Load(const std::string& _sName, IResource::E_THREAD _eThread) { LOG("LandscapeEdges can not create manualy"); }
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    //void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CLandscapeEdges__) */
