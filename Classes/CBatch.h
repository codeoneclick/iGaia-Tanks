//
//  CBatch.h
//  iGaia
//
//  Created by sergey sergeev on 6/21/12.
//
//

#ifndef __iGaia__CBatch__
#define __iGaia__CBatch__

#include <iostream>
#include "INode.h"

#define k_MAX_VERTEXES 4096
#define k_MAX_INDEXES 8192

class CBatch
{
public:
    enum E_BATCH_MODE { E_BATCH_MODE_MODEL = 0, E_BATCH_MODE_PARTICLE_EMITTER, E_BATCH_MODE_SPRITE, E_BATCH_MODE_SPRITE_CROSS };
protected:
    std::vector<INode*> m_lContainer;
    E_BATCH_MODE m_eMode;
    glm::mat4x4 m_mWorld;
    
    CShader** m_pShaders;
    CTexture** m_pTextures;
    CMesh* m_pMesh;
    
    unsigned int m_iNumVertexes;
    unsigned int m_iNumIndexes;
    
    void _RenderBatchModeModel(CShader::E_RENDER_MODE _eMode);
    void _RenderBatchModeParticleEmitter(CShader::E_RENDER_MODE _eMode);
    void _RenderBatchModeSprite(CShader::E_RENDER_MODE _eMode);
    void _RenderBatchModeSpriteCross(CShader::E_RENDER_MODE _eMode);

public:
    CBatch(E_BATCH_MODE _eMode);
    ~CBatch(void);
    
    void Reset_MeshRef(void);
    void Push_MeshRef(INode* _pNode);
    
    unsigned int Get_NumIndexes(void) { return m_iNumIndexes; }
    unsigned int Get_NumVertexes(void) { return m_iNumVertexes; }
    
    void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CBatch__) */
