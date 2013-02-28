//
//  CMaterial.h
//  iGaia
//
//  Created by sergey sergeev on 6/25/12.
//
//

#ifndef CMaterial_h
#define CMaterial_h

#include "CTexture.h"
#include "CShader.h"

class CMaterial
{
private:
    
protected:
    
    CShader* m_shader;
    GLenum m_cullFaceMode;
    GLenum m_blendFunctionSource;
    GLenum m_blendFunctionDest;
    glm::vec4 m_clipping;
    CTexture* m_textures[E_TEXTURE_SLOT_MAX];
    bool m_states[E_RENDER_STATE_MAX];
    
public:
    
    CMaterial(CShader* _shader);
    ~CMaterial(void);
    
    void Set_CullFaceMode(GLenum _mode);
    void Set_BlendFunctionSource(GLenum _blendFunction);
    void Set_BlendFunctionDest(GLenum _blendFunction);
    void Set_RenderState(E_RENDER_STATE _state, bool _value);
    
    CShader* Get_Shader(void);
    
    void Set_Clipping(const glm::vec4& _clipping);
    glm::vec4 Get_Clipping(void);
    
    void Set_Texture(CTexture* _texture, E_TEXTURE_SLOT _slot);
    
    void Bind(void);
    void Unbind(void);
};

#endif 
