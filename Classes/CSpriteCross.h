//
//  CSpriteCross.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CSpriteCross__
#define __iGaia__CSpriteCross__

#include <iostream>
#include "INode.h"

class CSpriteCross : public INode
{
protected:
    struct SFrame
    {
        glm::vec2 m_vTexcoord[4];
    };

    static const int k_ELEMENT_NUM_INDEXES;
    static const int k_ELEMENT_NUM_VERTEXES;

    glm::vec2 m_vSizeFrame;
    glm::vec2 m_vSizeAtlas;

    glm::vec2 m_vSize;

    glm::vec2 m_vTexcoordOffset;
    glm::vec2 m_vTexcoordRepeat;

    unsigned int m_iNumFrames;
    unsigned int m_iCurrentFrame;

    bool m_bIsEnable;

    SFrame* m_pSequence;
public:
    CSpriteCross(void);
    ~CSpriteCross(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
    
    inline void Set_NumFrames(unsigned int _iNumFrames) { m_iNumFrames = _iNumFrames; }
    inline void Set_SizeFrame(const glm::vec2& _vSize) { m_vSizeFrame = _vSize; }
    inline void Set_SizeAtlas(const glm::vec2& _vSize) { m_vSizeAtlas = _vSize; }

    inline void Inc_Frame(void) { ++m_iCurrentFrame; if(m_iCurrentFrame >= m_iNumFrames) m_iCurrentFrame = 0; }
    inline void Dec_Frame(void) { if(m_iCurrentFrame != 0) --m_iCurrentFrame; else m_iCurrentFrame = m_iNumFrames - 1; };
    inline void Set_Frame(unsigned int _iFrame) { if(_iFrame < m_iNumFrames) m_iCurrentFrame = _iFrame; }

    inline void Set_Size(const glm::vec2& _vSize) { m_vScale = glm::vec3(_vSize.x, _vSize.y, 1.0f); }

    inline void Set_TexcoordOffset(const glm::vec2& _vOffset) { m_vTexcoordOffset = _vOffset; }
    inline void Set_TexcoordRepeat(const glm::vec2& _vRepeat) { m_vTexcoordRepeat = _vRepeat; }

    void Enable(void);
    void Disable(void);
};


#endif /* defined(__iGaia__CSpriteCross__) */
