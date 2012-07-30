//
//  CMaterial.h
//  iGaia
//
//  Created by sergey sergeev on 6/25/12.
//
//

#ifndef __iGaia__CMaterial__
#define __iGaia__CMaterial__

#include <iostream>
#include "CShader.h"
#include "CTexture.h"

static const unsigned int k_TEXTURES_MAX_COUNT = 8;

class INode;
class CMaterial
{
public:
    enum E_RENDER_STATE { E_RENDER_STATE_CULL_MODE = 0, E_RENDER_STATE_BLEND_MODE, E_RENDER_STATE_DEPTH_TEST, E_RENDER_STATE_DEPTH_MASK, E_RENDER_STATE_MAX };
protected:
    CShader** m_pShaders;
    CTexture** m_pTextures;
    bool m_pModes[CShader::E_RENDER_MODE_MAX];
    bool m_pStates[E_RENDER_STATE_MAX];
    GLenum m_eCullFace;
    GLenum m_eBlendFuncSource;
    GLenum m_eBlendFuncDest;
    static bool m_pStatesCommited[E_RENDER_STATE_MAX];
    static GLenum m_eCullFaceCommited;
    static GLenum m_eBlendFuncSourceCommited;
    static GLenum m_eBlendFuncDestCommited;
    static GLuint m_hShaderHandleCommited;
public:
    CMaterial(void);
    ~CMaterial(void);
    
    static void InitStates(void);
    static void ScreenStates(void);
    
    CShader*  Get_Shader(CShader::E_RENDER_MODE _eMode);
    CTexture* Get_Texture(unsigned int _index);
    CTexture** Get_Textures(void) { return m_pTextures; }
    
    void Set_Texture(CTexture* _pTexture, int _index, CTexture::E_WRAP_MODE _eWrap);
    void Set_Texture(INode* _pNodeRef, const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    
    void Set_Shader(INode* _pNodeRef, CShader::E_RENDER_MODE _eMode, IResource::E_SHADER _eShader);
    
    void Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value);
    bool Get_RenderMode(CShader::E_RENDER_MODE _eMode);
    
    bool Get_RenderState(CMaterial::E_RENDER_STATE _eState);
    void Set_RenderState(CMaterial::E_RENDER_STATE _eState, bool _value);
    
    void Set_CullFace(GLenum _eCullFace);
    
    void Set_BlendFunc(GLenum _eFuncSource, GLenum _eFuncDest);

    void Commit(CShader::E_RENDER_MODE _eMode);
    
    bool Check_RenderMode(CShader::E_RENDER_MODE _eMode) { if(m_pShaders[_eMode] != NULL) return true; else return false; }
    static void Set_ExtCommitedShaderRef(CShader* _pShaderRef) { m_hShaderHandleCommited = _pShaderRef->Get_Handle(); _pShaderRef->Enable(); }
};

#endif /* defined(__iGaia__CMaterial__) */
