//
//  CRenderOperationScreenSpace.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "CRenderOperationScreenSpace.h"

CRenderOperationScreenSpace::CRenderOperationScreenSpace(ui32 _frameWidth, ui32 _frameHeight, E_RENDER_MODE_SCREEN_SPACE _mode, CMaterial* _material, const std::string& _name)
{
    m_frameWidth = _frameWidth;
    m_frameHeight = _frameHeight;

    ui32 textureHandle;
    glGenTextures(1, &textureHandle);
    glGenFramebuffers(1, &m_frameBufferHandle);
    glGenRenderbuffers(1, &m_depthBufferHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_frameWidth, m_frameHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_frameWidth, m_frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);

    m_operatingTexture = new CTexture(textureHandle, m_frameWidth, m_frameHeight);
    m_operatingTexture->Set_WrapMode(GL_CLAMP_TO_EDGE);

    CVertexBuffer* vertexBuffer = new CVertexBuffer(4, GL_STATIC_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();
    vertexData[0].m_position = glm::vec3(-1.0f,-1.0f,0.0f);
    vertexData[0].m_texcoord = glm::vec2(0.0f,0.0f);
    vertexData[1].m_position = glm::vec3(-1.0f,1.0f,0.0f);
    vertexData[1].m_texcoord = glm::vec2(0.0f,1.0f);
    vertexData[2].m_position = glm::vec3(1.0f,-1.0f,0.0f);
    vertexData[2].m_texcoord = glm::vec2(1.0f,0.0f);
    vertexData[3].m_position = glm::vec3(1.0f,1.0f,0.0f);
    vertexData[3].m_texcoord = glm::vec2(1.0f,1.0f);
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

CRenderOperationScreenSpace::~CRenderOperationScreenSpace(void)
{
    
}

void CRenderOperationScreenSpace::Bind(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, m_frameWidth, m_frameHeight);
    glClearColor(0, 0, 0, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_material->Bind();
    m_mesh->Bind(m_material->Get_Shader()->Get_VertexSlots());
}

void CRenderOperationScreenSpace::Unbind(void)
{
    m_mesh->Unbind(m_material->Get_Shader()->Get_VertexSlots());
    m_material->Unbind();
}

void CRenderOperationScreenSpace::Draw(void)
{
    m_mesh->Draw();
}