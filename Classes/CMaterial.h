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

class CMaterial
{
public:
    enum E_RENDER_STATE
    {
        E_RENDER_STATE_CULL_MODE = 0,
        E_RENDER_STATE_BLEND_MODE,
        E_RENDER_STATE_DEPTH_TEST,
        E_RENDER_STATE_DEPTH_MASK, E_RENDER_STATE_MAX
    };
protected:
    CShader** m_shaders;
    CTexture** m_textures;
    bool m_renderModes[CShader::E_RENDER_MODE_WORLD_SPACE_MAX + CShader::E_RENDER_MODE_SCREEN_SPACE_MAX];
    bool m_renderState[E_RENDER_STATE_MAX];
    GLenum m_cullFaceMode;
    GLenum m_blendFuncSource;
    GLenum m_blendFuncDest;
    static bool m_renderStateCached[E_RENDER_STATE_MAX];
    static GLenum m_cullFaceModeCached;
    static GLenum m_blendFuncSourceCached;
    static GLenum m_blendFuncDestCached;
    static GLuint m_shaderHandleCached;
public:
    CMaterial(void);
    ~CMaterial(void);
    
    static void InitStates(void);
    static void ScreenStates(void);
    
    void Set_Texture(CTexture* _texture, int _index, CTexture::E_WRAP_MODE _wrap);
    void Set_Texture(const std::string &_name, int _index, CTexture::E_WRAP_MODE _wrap, IResource::E_THREAD _thread = IResource::E_THREAD_SYNC);
    void Set_Shader(unsigned int _renderMode, CShader::E_SHADER _shader);

    void BindRenderMode(unsigned int _renderMode, bool _value);
    bool CheckRenderMode(unsigned int _renderMode);

    void BindRenderState(CMaterial::E_RENDER_STATE _renderState, bool _value);
    bool CheckRenderState(CMaterial::E_RENDER_STATE _renderState);
    
    void Set_CullFaceMode(GLenum _cullFaceMode);
    
    void Set_BlendFunc(GLenum _blendFuncSource, GLenum _blendFuncDest);

    void Commit(unsigned int _renderMode);
};

#endif /* defined(__iGaia__CMaterial__) */
