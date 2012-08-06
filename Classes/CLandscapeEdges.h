//
//  CLandscapeEdges.h
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#ifndef __iGaia__CLandscapeEdges__
#define __iGaia__CLandscapeEdges__

#include <iostream>
#include "INode.h"

class CLandscapeEdges : public INode
{
protected:
    int m_iWidth;
    int m_iHeight;
    glm::vec2 m_vHeight;
public:
    CLandscapeEdges(void);
    ~CLandscapeEdges(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif /* defined(__iGaia__CLandscapeEdges__) */
