//
//  INode.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_INode_h
#define iGaia_INode_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "CMaterial.h"
#include "CVertexBuffer.h"
#include "CMesh.h"

#include "CResourceMgr.h"
#include "CShaderComposite.h"
#include "CMeshComposite.h"

#include "CBoundingBox.h"
#include "ILight.h"

#include "IResourceLoaderDelegate.h"
#include "ITouchDelegate.h"

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

class INode : public ITouchDelegate, public IResourceLoaderDelegate
{
protected:
    glm::mat4x4 m_mScale;
    glm::mat4x4 m_mRotation;
    glm::mat4x4 m_mTranslation;
    glm::mat4x4 m_mWorld;
    glm::mat4x4 m_mWVP;
    
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vScale;
    glm::vec2 m_vTexCoordOffset;
    
    CMaterial* m_pMaterial;
    CMesh* m_pMesh;
    
    CBoundingBox* m_pBoundingBox;
    
    bool m_bIsBatching;
    std::string m_sBatchingName;
    
    std::vector<IDelegate*> m_lDelegateOwners;
    
    float _Get_WrapAngle(float _fValue, float _fMin, float _fMax)
    {
        float fDistance = _fMax - _fMin;
        float fTimes = floorf((_fValue - _fMin) / fDistance);
        return _fValue - (fTimes * fDistance);
    }
    
public:
    INode(void);
    virtual ~INode(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread) = 0;
    virtual void Update(void);
    virtual void Render(CShader::E_RENDER_MODE _eMode);
    
    CShader*  Get_Shader(CShader::E_RENDER_MODE _eRenderMode);
    CTexture* Get_Texture(unsigned int index);
    CMesh*    Get_Mesh(void) { return m_pMesh; }
    
    void Set_Batching(bool _bValue,  const std::string& _sBatchingName) { m_bIsBatching = _bValue; m_sBatchingName = _sBatchingName; }
    std::string Get_BatchingName(void) { return m_sBatchingName; }
    
    void Set_Texture(CTexture* _pTexture, int index, CTexture::E_WRAP_MODE _eWrap);
    void Set_Texture(const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    void Set_Shader(CShader::E_RENDER_MODE _eRenderMode, IResource::E_SHADER _eShader);
    
    CBoundingBox* Get_BoundingBox(void) { return m_pBoundingBox; }
    
    void Set_Position(const glm::vec3& _vPosition) { m_vPosition = _vPosition; }
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation)
    {
        m_vRotation = _vRotation;
        m_vRotation.x = _Get_WrapAngle(m_vRotation.x, 0.0f, 360.0f);
        m_vRotation.y = _Get_WrapAngle(m_vRotation.y, 0.0f, 360.0f);
        m_vRotation.z = _Get_WrapAngle(m_vRotation.z, 0.0f, 360.0f);
    }
    
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    void Set_Scale(const glm::vec3& _vScale) { m_vScale = _vScale; }
    glm::vec3 Get_Scale(void) { return m_vScale; }
    
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
    
    void Set_TexCoordOffset(glm::vec2 _vOffset) { m_vTexCoordOffset = _vOffset; }
    glm::vec2 Get_TexCoordOffset(void) { return m_vTexCoordOffset; }
    
    void Add_DelegateOwner(IDelegate* _pDelegateOwner);
    void Remove_DelegateOwner(IDelegate* _pDelegateOwner);
    
    virtual void Create_BoundingBox(void);
    void Remove_BoundingBox(void);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource) = 0;
    
    void Set_RenderMode(CShader::E_RENDER_MODE _eMode, bool _value);
    bool Get_RenderMode(CShader::E_RENDER_MODE _eMode);
};

#endif










