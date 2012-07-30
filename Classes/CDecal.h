//
//  CDecal.h
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#ifndef __iGaia__CDecal__
#define __iGaia__CDecal__

#include <iostream>
#include "INode.h"

class CDecal : public INode
{
protected:
    glm::vec4 m_vColor;
    static glm::mat3x3 m_mTextureTranslation;
    static glm::mat3x3 m_mTextureScale;
    glm::mat3x3 m_mTextureRotation;
    glm::mat3x3 m_mTexture;
public:
    CDecal(void);
    ~CDecal(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void Set_Color(const glm::vec4& _vColor) { m_vColor = _vColor; }
    glm::vec4 Get_Color(void) { return m_vColor; }
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif /* defined(__iGaia__CDecal__) */
