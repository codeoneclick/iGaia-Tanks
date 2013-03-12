//
//  CRenderOperationScreenOutput.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/28/13.
//
//

#include "CRenderOperationScreenOutput.h"

CRenderOperationScreenOutput::CRenderOperationScreenOutput(ui32 _frameWidth, ui32 _frameHeight, CMaterial* _material, ui32 _frameBufferHandle, ui32 _renderBufferHandle, const std::string& _name)
{
    m_frameWidth = _frameWidth;
    m_frameHeight = -_frameHeight;
    
    m_frameBufferHandle = _frameBufferHandle;
    m_renderBufferHandle = _renderBufferHandle;

    m_material = _material;
    
    CVertexBuffer* vertexBuffer = new CVertexBuffer(4, GL_STATIC_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();
    vertexData[0].m_position = glm::vec3(-1.0f, -1.0f, 0.0f);
    vertexData[0].m_texcoord = glm::vec2(0.0f, 0.0f);
    vertexData[1].m_position = glm::vec3(-1.0f, 1.0f, 0.0f);
    vertexData[1].m_texcoord = glm::vec2(0.0f, 1.0f);
    vertexData[2].m_position = glm::vec3(1.0f, -1.0f, 0.0f);
    vertexData[2].m_texcoord = glm::vec2(1.0f, 0.0f);
    vertexData[3].m_position = glm::vec3(1.0f, 1.0f, 0.0f);
    vertexData[3].m_texcoord = glm::vec2(1.0f, 1.0f);
    vertexBuffer->Unlock();
    
    CIndexBuffer* indexBuffer = new CIndexBuffer(6, GL_STATIC_DRAW);
    ui16* indexData = indexBuffer->Lock();
    indexData[0] = 0;
    indexData[1] = 1;
    indexData[2] = 2;
    indexData[3] = 1;
    indexData[4] = 2;
    indexData[5] = 3;
    indexBuffer->Unlock();
    
    m_material->Set_RenderState(E_RENDER_STATE_CULL_MODE, false);
    m_material->Set_RenderState(E_RENDER_STATE_DEPTH_MASK, true);
    m_material->Set_RenderState(E_RENDER_STATE_DEPTH_TEST, false);
    m_material->Set_RenderState(E_RENDER_STATE_BLEND_MODE, false);
    
    m_material->Set_CullFaceMode(GL_FRONT);
    m_material->Set_BlendFunctionSource(GL_SRC_ALPHA);
    m_material->Set_BlendFunctionDest(GL_ONE_MINUS_SRC_ALPHA);
    
    m_mesh = new CMesh(vertexBuffer, indexBuffer);
}

CRenderOperationScreenOutput::~CRenderOperationScreenOutput(void)
{
    
}

void CRenderOperationScreenOutput::Bind(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferHandle);
    glViewport(0, 0, m_frameWidth, m_frameHeight);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    m_material->Bind();
    m_mesh->Bind(m_material->Get_Shader()->Get_VertexSlots());
}

void CRenderOperationScreenOutput::Unbind(void)
{
    m_mesh->Unbind(m_material->Get_Shader()->Get_VertexSlots());
    m_material->Unbind();
}

void CRenderOperationScreenOutput::Draw(void)
{
    m_mesh->Draw();
}