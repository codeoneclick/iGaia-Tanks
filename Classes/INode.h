//
//  INode.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_INode_h
#define iGaia_INode_h

#include "CCommon.h"

#include "CMaterial.h"
#include "CMesh.h"
#include "CBoundingBox.h"
#include "ILight.h"

#include "CResourceMgr.h"
#include "CShaderComposite.h"

#include "CMathHelper.h"

class INode
{
protected:
// -- Block for transform matrix -- //
    glm::mat4x4 m_mScale;
    glm::mat4x4 m_mRotation;
    glm::mat4x4 m_mTranslation;
    glm::mat4x4 m_mWorld;
    glm::mat4x4 m_mWVP;
// -- -- //
    
// -- Block for transform vectors -- //
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vScale;
// -- -- //
    
// -- Transform mesh texture coord -- //
    glm::vec2 m_vTexCoordOffset;
// --  -- //

// -- Render material states -- //
    CMaterial* m_pMaterial;
// -- -- //

// -- Mesh which contain index and vertex buffers -- //
    CMesh* m_pMesh;
// -- -- //

// -- Bound box for current mesh -- //
    CBoundingBox* m_pBoundingBox;
// -- -- //

// -- Varible for enable/disable render -- //
    bool m_bIsVisible;
// -- -- //
    IResource::EventSignature m_pLoadBlock;
    
public:
    INode(void);
    virtual ~INode(void);
    
// -- Load resource function for the mesh loading. Can use background thread for preloading. Overwrite for all nodes -- //
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread) = 0;
// -- -- //
    
// --  Update for main loop. Overwrite for all nodes -- //
    virtual void Update(void);
// -- -- //
    
// -- Render mesh which can use material by enum value. Overwrite for all nodes -- //
    virtual void Render(CShader::E_RENDER_MODE _eMode);
// -- -- //
    
// -- Getters block for recieve main varibles for current node -- //
    CShader*  Get_Shader(CShader::E_RENDER_MODE _eRenderMode);
    CTexture* Get_Texture(unsigned int index);
    inline CMesh* Get_Mesh(void) { return m_pMesh; }
// -- -- //
    
// -- Setters for texture by index. For preload/load texture. Can use background thread for preloading  -- //
    void Set_Texture(CTexture* _pTexture, int index, CTexture::E_WRAP_MODE _eWrap);
    void Set_Texture(const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread = IResource::E_THREAD_SYNC);
// -- -- //

// -- Setter for shader. Use render mode to set shader to the current material and render state -- //
    void Set_Shader(CShader::E_RENDER_MODE _eRenderMode, IResource::E_SHADER _eShader);
// -- -- //
    
// -- Getter to receive bound box for current mesh -- //
    inline CBoundingBox* Get_BoundingBox(void) { return m_pBoundingBox; }
// -- -- //
    
// -- Block with getters/setters to receive main transform vectors -- //
    void Set_Position(const glm::vec3& _vPosition) { m_vPosition = _vPosition; }
    glm::vec3 Get_Position(void) { return m_vPosition; }
    void Set_Rotation(const glm::vec3& _vRotation);
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    void Set_Scale(const glm::vec3& _vScale) { m_vScale = _vScale; }
    glm::vec3 Get_Scale(void) { return m_vScale; }
// -- -- //
    
// -- Getter to receive current world matrix scale*rotation*position -- //
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
// -- -- //
    
// -- Setters/Getters for manipulation texture coord -- //
    void Set_TexCoordOffset(glm::vec2 _vOffset) { m_vTexCoordOffset = _vOffset; }
    glm::vec2 Get_TexCoordOffset(void) { return m_vTexCoordOffset; }
// -- -- //
    
// -- Block for enable/disable and get current render mode. Use for the different materials -- //
    void Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value);
    bool Get_RenderMode(CShader::E_RENDER_MODE _eMode);
// -- -- //
    
// -- Block for the set/check visibility of object -- //
    inline bool Get_Visible(void) { return m_bIsVisible; }
    inline void Set_Visible(bool _bIsVisible) { m_bIsVisible = _bIsVisible; }
// -- -- //
};

#endif










