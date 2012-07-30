//
//  CMaterial.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/25/12.
//
//

#include "CMaterial.h"
#include "CResourceMgr.h"
#include "INode.h"

bool CMaterial::m_pStatesCommited[CMaterial::E_RENDER_STATE_MAX];
GLenum CMaterial::m_eCullFaceCommited;
GLenum CMaterial::m_eBlendFuncSourceCommited;
GLenum CMaterial::m_eBlendFuncDestCommited;
GLuint CMaterial::m_hShaderHandleCommited;

void CMaterial::InitStates(void)
{
    glEnable(GL_DEPTH_TEST);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_TEST] = true;
    glEnable(GL_CULL_FACE);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_CULL_MODE] = true;
    glCullFace(GL_FRONT);
    m_eCullFaceCommited = GL_FRONT;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_eBlendFuncSourceCommited = GL_SRC_ALPHA;
    m_eBlendFuncDestCommited = GL_ONE_MINUS_SRC_ALPHA;
    glEnable(GL_BLEND);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_BLEND_MODE] = true;
    glDepthMask(GL_TRUE);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_MASK] = true;
    
    m_hShaderHandleCommited = 0;
}

void CMaterial::ScreenStates(void)
{
    glDisable(GL_DEPTH_TEST);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_TEST] = false;
    glDisable(GL_CULL_FACE);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_CULL_MODE] = false;
    glDisable(GL_BLEND);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_BLEND_MODE] = false;
    glDepthMask(GL_TRUE);
    m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_MASK] = true;
}

CMaterial::CMaterial(void)
{
    m_pTextures = new CTexture*[k_TEXTURES_MAX_COUNT];
    for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; ++i)
    {
        m_pTextures[i] = NULL;
    }
    
    m_pShaders = new CShader*[CShader::E_RENDER_MODE_MAX];
    for(unsigned int i = 0; i < CShader::E_RENDER_MODE_MAX; ++i)
    {
        m_pShaders[i] = NULL;
    }
    m_pModes[CShader::E_RENDER_MODE_SIMPLE] = true;
    m_pModes[CShader::E_RENDER_MODE_REFLECTION] = false;
    m_pModes[CShader::E_RENDER_MODE_REFRACTION] = false;
    m_pModes[CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP] = false;
    
    m_pStates[CMaterial::E_RENDER_STATE_BLEND_MODE] = false;
    m_pStates[CMaterial::E_RENDER_STATE_CULL_MODE] = true;
    m_pStates[CMaterial::E_RENDER_STATE_DEPTH_TEST] = true;
    m_pStates[CMaterial::E_RENDER_STATE_DEPTH_MASK] = true;
    m_eCullFace = GL_FRONT;
}

CMaterial::~CMaterial(void)
{
    SAFE_DELETE_ARRAY(m_pTextures);
    SAFE_DELETE_ARRAY(m_pShaders);
}

void CMaterial::Set_Texture(CTexture *_pTexture, int _index, CTexture::E_WRAP_MODE _eWrap)
{
    if(_index >= k_TEXTURES_MAX_COUNT )
    {
        std::cout<<"[INode] Critical index for the texture.";
        return;
    }
    if( m_pTextures[_index] != NULL )
    {
        // TODO: unload
    }
    m_pTextures[_index] = _pTexture;
}

void CMaterial::Set_Texture(INode* _pNodeRef, const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread )
{
    if(_index >= k_TEXTURES_MAX_COUNT)
    {
        std::cout<<"[INode] Critical index for the texture.";
        return;
    }
    if( m_pTextures[_index] != NULL )
    {
        // TODO: unload
    }
    std::map<std::string, std::string> lParams;
    if(_eWrap == CTexture::E_WRAP_MODE_REPEAT)
    {
        lParams["WRAP"] = "REPEAT";
    }
    else if(_eWrap == CTexture::E_WRAP_MODE_CLAMP)
    {
        lParams["WRAP"] = "CLAMP";
    }
    m_pTextures[_index] = static_cast<CTexture*>(CResourceMgr::Instance()->Load(_sName, IResource::E_MGR_TEXTURE, _eThread, static_cast<IDelegate*>(_pNodeRef), &lParams));
}

void CMaterial::Set_Shader(INode* _pNodeRef, CShader::E_RENDER_MODE _eMode, IResource::E_SHADER _eShader)
{
    m_pShaders[_eMode] = CShaderComposite::Instance()->Get_Shader(_eShader);
    if(_pNodeRef->Get_Mesh() != NULL)
    {
        _pNodeRef->Get_Mesh()->Get_VertexBufferRef()->Add_ShaderRef(_eMode, m_pShaders[_eMode]);
    }
}

CShader* CMaterial::Get_Shader(CShader::E_RENDER_MODE _eMode)
{
    return m_pShaders[_eMode];
}

CTexture* CMaterial::Get_Texture(unsigned int _index)
{
    if(_index >= k_TEXTURES_MAX_COUNT)
    {
        std::cout<<"[INode] Critical index for the texture.";
        return NULL;
    }
    return m_pTextures[_index];
}

void CMaterial::Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value)
{
    m_pModes[_eMode] = _value;
}

bool CMaterial::Get_RenderMode(CShader::E_RENDER_MODE _eMode)
{
    return m_pModes[_eMode];
}

void CMaterial::Set_RenderState(CMaterial::E_RENDER_STATE _eState, bool _value)
{
    m_pStates[_eState] = _value;
}

bool CMaterial::Get_RenderState(CMaterial::E_RENDER_STATE _eState)
{
    return m_pStates[_eState];
}

void CMaterial::Set_CullFace(GLenum _eCullFace)
{
    m_eCullFace = _eCullFace;
}

void CMaterial::Set_BlendFunc(GLenum _eFuncSource, GLenum _eFuncDest)
{
    m_eBlendFuncSource = _eFuncSource;
    m_eBlendFuncDest = _eFuncDest;
}

void CMaterial::Commit(CShader::E_RENDER_MODE _eMode)
{
    if(m_pShaders[_eMode] == NULL)
    {
        std::cout<<"[CMaterial::Commit] Shader is not valid"<<std::endl;
        return;
    }
    
    if(m_hShaderHandleCommited != m_pShaders[_eMode]->Get_Handle())
    {
        m_pShaders[_eMode]->Enable();
        m_hShaderHandleCommited = m_pShaders[_eMode]->Get_Handle();
    }
    
    if(m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_TEST] != m_pStates[CMaterial::E_RENDER_STATE_DEPTH_TEST])
    {
        if(m_pStates[CMaterial::E_RENDER_STATE_DEPTH_TEST])
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
        m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_TEST] = m_pStates[CMaterial::E_RENDER_STATE_DEPTH_TEST];
    }
    
    if(m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_MASK] != m_pStates[CMaterial::E_RENDER_STATE_DEPTH_MASK])
    {
        if(m_pStates[CMaterial::E_RENDER_STATE_DEPTH_MASK])
        {
            glDepthMask(GL_TRUE);
        }
        else
        {
            glDepthMask(GL_FALSE);
        }
        m_pStatesCommited[CMaterial::E_RENDER_STATE_DEPTH_MASK] = m_pStates[CMaterial::E_RENDER_STATE_DEPTH_MASK];
    }
    
    if(m_pStatesCommited[CMaterial::E_RENDER_STATE_CULL_MODE] != m_pStates[CMaterial::E_RENDER_STATE_CULL_MODE])
    {
        if(m_pStates[CMaterial::E_RENDER_STATE_CULL_MODE])
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
        m_pStatesCommited[CMaterial::E_RENDER_STATE_CULL_MODE] = m_pStates[CMaterial::E_RENDER_STATE_CULL_MODE];
    }
    
    if(m_pStatesCommited[CMaterial::E_RENDER_STATE_BLEND_MODE] != m_pStates[CMaterial::E_RENDER_STATE_BLEND_MODE])
    {
        if(m_pStates[CMaterial::E_RENDER_STATE_BLEND_MODE])
        {
            glEnable(GL_BLEND);
        }
        else
        {
            glDisable(GL_BLEND);
        }
        m_pStatesCommited[CMaterial::E_RENDER_STATE_BLEND_MODE] = m_pStates[CMaterial::E_RENDER_STATE_BLEND_MODE];
    }
    
    if(m_pStates[CMaterial::E_RENDER_STATE_CULL_MODE] && m_eCullFace != m_eCullFaceCommited)
    {
        glCullFace(m_eCullFace);
        m_eCullFaceCommited = m_eCullFace;
    }
    
    if(m_pStates[CMaterial::E_RENDER_STATE_BLEND_MODE] && (m_eBlendFuncSourceCommited != m_eBlendFuncSource || m_eBlendFuncDestCommited != m_eBlendFuncDest))
    {
        glBlendFunc(m_eBlendFuncSource, m_eBlendFuncDest);
        m_eBlendFuncSourceCommited = m_eBlendFuncSource;
        m_eBlendFuncDestCommited = m_eBlendFuncDest;
    }
}






