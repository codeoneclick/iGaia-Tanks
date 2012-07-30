//
//  CLightPoint.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLightPoint.h"
#include "CShaderComposite.h"
#include "CSceneMgr.h"

const glm::vec3 CLightPoint::k_Size = glm::vec3(0.2f, 0.2f, 0.2f);

CLightPoint::CLightPoint()
{
    /*m_vDistanceToLightAt = glm::vec2( 16.0f, 16.0f);
    
    m_mWorld = glm::mat4x4(1.0f);
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    
    m_vMax = glm::vec3(k_Size.x / 2.0f, k_Size.y / 2.0f, k_Size.z / 2.0f);
    m_vMin = glm::vec3(-k_Size.x / 2.0f, -k_Size.y / 2.0f, -k_Size.z / 2.0f);
    
    pPositionData[0] = glm::vec3( m_vMin.x,  m_vMin.y, m_vMax.z);
    pPositionData[1] = glm::vec3( m_vMax.x,  m_vMin.y, m_vMax.z);
    pPositionData[2] = glm::vec3( m_vMax.x,  m_vMax.y, m_vMax.z);
    pPositionData[3] = glm::vec3( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pPositionData[4] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[5] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[6] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[7] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pPositionData[8] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pPositionData[9] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[10] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[11] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pPositionData[12] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[13] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[14] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pPositionData[15] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pPositionData[16] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pPositionData[17] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pPositionData[18] = glm::vec3( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pPositionData[19] = glm::vec3( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pPositionData[20] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pPositionData[21] = glm::vec3( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pPositionData[22] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pPositionData[23] = glm::vec3( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIndexBuffer->Get_Data();
    
    // Front
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 0;
    pIBData[4] = 2;
    pIBData[5] = 3;
    // Back
    pIBData[6] = 4;
    pIBData[7] = 5;
    pIBData[8] = 6;
    pIBData[9] = 4;
    pIBData[10] = 6;
    pIBData[11] = 7;
    // Left
    pIBData[12] = 8;
    pIBData[13] = 9;
    pIBData[14] = 10;
    pIBData[15] = 8;
    pIBData[16] = 10;
    pIBData[17] = 11;
    // Right
    pIBData[18] = 12;
    pIBData[19] = 13;
    pIBData[20] = 14;
    pIBData[21] = 12;
    pIBData[22] = 14;
    pIBData[23] = 15;
    // Top
    pIBData[24] = 16;
    pIBData[25] = 17;
    pIBData[26] = 18;
    pIBData[27] = 16;
    pIBData[28] = 18;
    pIBData[29] = 19;
    // Bottom
    pIBData[30] = 20;
    pIBData[31] = 21;
    pIBData[32] = 22;
    pIBData[33] = 20;
    pIBData[34] = 22;
    pIBData[35] = 23;
    
    glm::u8vec4* pColorData = pSource->m_pVertexBuffer->CreateOrReUse_ColorData();
    
    for(unsigned int index = 0; index < pSource->m_iNumVertexes; ++index)
    {
        pColorData[index] = glm::u8vec4( 255, 255, 255, 255 );
    }
    
    pSource->m_pVertexBuffer->CommitToRAM();
    pSource->m_pVertexBuffer->CommitFromRAMToVRAM();
    pSource->m_pIndexBuffer->CommitFromRAMToVRAM();
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShader->Get_ProgramHandle());*/
}

CLightPoint::~CLightPoint()
{
    
}

void CLightPoint::Update(void)
{
    ILight::Update();
    //m_vPosition.x = 16.0f;
    //m_vPosition.z = 16.0f;
    m_vPosition.x = m_vLightAt.x + cosf(m_vRotation.y) * m_vDistanceToLightAt.x;
    m_vPosition.z = m_vLightAt.z + sinf(m_vRotation.y) * m_vDistanceToLightAt.y;
    //m_vPosition.y = sinf(m_vRotation.y) * 16.0f;
}

void CLightPoint::Render()
{
    /*if(m_bIsVisible)
    {
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pMesh->Get_VertexBufferRef()->Enable();
        m_pMesh->Get_IndexBufferRef()->Enable();
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
        m_pMesh->Get_IndexBufferRef()->Disable();
        m_pMesh->Get_VertexBufferRef()->Disable();
        m_pShader->Disable();
    }*/
}
