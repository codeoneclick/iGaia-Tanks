//
//  CHeightMapSetter.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CHeightMapSetter.h"
#include "CSceneMgr.h"
#include "CVertexBufferPositionTexcoordNormalTangent.h"
#include "CVertexBufferPositionTexcoord.h"
#include <algorithm>

#define RGB(r,g,b) (unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))

CHeightMapSetter::CHeightMapSetter(void)
{
    m_pHeightMapData = nullptr;
    m_fXThreshold = 0.0f;
    m_fZThreshold = 0.0f;
    m_pPreRenderScreenQuad = nullptr;
    m_pPreRenderShader = nullptr;
    m_vScaleFactor = glm::vec2(1.0f, 1.0f);
    m_bIsTexturePreRender = false;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    SAFE_DELETE_ARRAY(m_pHeightMapData);
    SAFE_DELETE(m_pPreRenderScreenQuad);
    glDeleteTextures(1, &m_hTextureSplatting);
    glDeleteTextures(1, &m_hTextureEdgesMask);
    glDeleteTextures(1, &m_hTextureHeightmap);
}

void CHeightMapSetter::Load(const std::string _sName, unsigned int _iWidth, unsigned int _iHeight, const glm::vec2& _vScaleFactor)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
    m_vScaleFactor = _vScaleFactor;
    
    m_pHeightMapData = new float[m_iWidth * m_iHeight];
    
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = sin(i * 0.33f) / 2.0f + cos(j * 0.33f) / 2.0f;
            m_pHeightMapData[i + j * m_iWidth] = fHeight;
        }
    }
    
    _Create_TextureSplatting();
    _Create_TextureHeightmap();
    _Create_TextureDetail();
    _Create_TextureEgdesMask();
}

CMesh* CHeightMapSetter::Get_HeightMapMesh(void)
{
    CVertexBufferPositionTexcoordNormalTangent *pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(m_iWidth * m_iHeight, GL_STATIC_DRAW);
    
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(pVertexBuffer->Lock());
    
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iWidth;++i)
    {
        for(unsigned int j = 0; j < m_iHeight;++j)
        {
            pVertexBufferData[index].m_vPosition.x = i;
            pVertexBufferData[index].m_vPosition.y = m_pHeightMapData[i + j * m_iWidth];
            pVertexBufferData[index].m_vPosition.z = j;
            
            pVertexBufferData[index].m_vTexcoord.x = i / static_cast<float>(m_iWidth);
            pVertexBufferData[index].m_vTexcoord.y = j / static_cast<float>(m_iHeight);
            ++index;
        }
    }
    
    CIndexBuffer* pIndexBuffer = new CIndexBuffer((m_iWidth - 1) * (m_iHeight - 1) * 6, GL_STREAM_DRAW);
    unsigned short* pIndexBufferData = pIndexBuffer->Get_SourceData();
    index = 0;
    for(unsigned int i = 0; i < (m_iWidth - 1); ++i)
    {
        for(unsigned int j = 0; j < (m_iHeight - 1); ++j)
        {
            pIndexBufferData[index] = i + j * m_iWidth;
            index++;
            pIndexBufferData[index] = i + (j + 1) * m_iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * m_iWidth;
            index++;
            
            pIndexBufferData[index] = i + (j + 1) * m_iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + (j + 1) * m_iWidth;
            index++;
            pIndexBufferData[index] = i + 1 + j * m_iWidth;
            index++;
        }
    }
    
    _CalculateNormals(pVertexBuffer, pIndexBuffer);
    _CalculateTangentsAndBinormals(pVertexBuffer, pIndexBuffer);
    
    CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    pMesh->Set_VertexBufferRef(pVertexBuffer);
    pMesh->Set_IndexBufferRef(pIndexBuffer);
    pMesh->Get_VertexBufferRef()->Commit();
    pMesh->Get_IndexBufferRef()->Commit();
    return pMesh;
}

void CHeightMapSetter::_Create_TextureEgdesMask(void)
{
    glGenTextures(1, &m_hTextureEdgesMask);
    glBindTexture(GL_TEXTURE_2D, m_hTextureEdgesMask);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    int iTextureEdgesMaskWidth = 128;
    int iTextureEdgesMaskHeight = 512;
    
    float fUpperEdgeMin = 3.0f;
    float fUpperEdgeMax = 4.0f;
    
    unsigned short* pTextureEdgesMask = new unsigned short[iTextureEdgesMaskWidth * iTextureEdgesMaskHeight];
    for(int i = 0; i < iTextureEdgesMaskWidth; i++)
    {
        unsigned int iTextureBlockSize = 0;
        for(int j = 0; j < iTextureEdgesMaskHeight / 4; j++)
        { 
            float fCurrentEdgeHeight = (static_cast<float>(j) - (static_cast<float>(iTextureEdgesMaskWidth) / 2.0f)) / 8.0f;
            float fWidthIndex = static_cast<float>(i) / static_cast<float>(iTextureEdgesMaskWidth);
            int iWidthIndex = fWidthIndex * m_iWidth;
            float fCurrentMapHeight = Get_HeightValue(iWidthIndex * m_vScaleFactor.x, 0);
            
            if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) > fUpperEdgeMax)
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(255, 0, 0);
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) >= fUpperEdgeMin && (fCurrentEdgeHeight - fCurrentMapHeight) <= fUpperEdgeMax)
            {
                glm::vec3 vMixColor = glm::mix(glm::vec3(255.0f, 0.0f, 0.0f), glm::vec3(0.0f, 255.0f, 0.0f), fUpperEdgeMax - (fCurrentEdgeHeight - fCurrentMapHeight));
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(static_cast<unsigned char>(vMixColor.x), static_cast<unsigned char>(vMixColor.y), static_cast<unsigned char>(vMixColor.z));
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight)
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 255, 0);
            }
            else
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 0, 255);
            }
        }
        iTextureBlockSize = iTextureEdgesMaskWidth * (iTextureEdgesMaskHeight / 4);
        for(int j = 0; j < iTextureEdgesMaskHeight / 4; j++)
        {
            float fCurrentEdgeHeight = (static_cast<float>(j) - (static_cast<float>(iTextureEdgesMaskWidth) / 2.0f)) / 8.0f;
            float fWidthIndex = static_cast<float>(i) / static_cast<float>(iTextureEdgesMaskWidth);
            int iWidthIndex = fWidthIndex * m_iWidth;
            float fCurrentMapHeight = Get_HeightValue(iWidthIndex * m_vScaleFactor.x, (m_iWidth - 1) * m_vScaleFactor.y);
            
            if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) > fUpperEdgeMax)
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(255, 0, 0);
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) >= fUpperEdgeMin && (fCurrentEdgeHeight - fCurrentMapHeight) <= fUpperEdgeMax)
            {
                glm::vec3 vMixColor = glm::mix(glm::vec3(255.0f, 0.0f, 0.0f), glm::vec3(0.0f, 255.0f, 0.0f), fUpperEdgeMax - (fCurrentEdgeHeight - fCurrentMapHeight));
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(static_cast<unsigned char>(vMixColor.x), static_cast<unsigned char>(vMixColor.y), static_cast<unsigned char>(vMixColor.z));
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight)
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 255, 0);
            }
            else
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 0, 255);
            }
        }
        iTextureBlockSize = iTextureEdgesMaskWidth * (iTextureEdgesMaskHeight / 4) * 2;
        for(int j = 0; j < iTextureEdgesMaskHeight / 4; j++)
        {
            float fCurrentEdgeHeight = (static_cast<float>(j) - (static_cast<float>(iTextureEdgesMaskWidth) / 2.0f)) / 8.0f;
            float fWidthIndex = static_cast<float>(i) / static_cast<float>(iTextureEdgesMaskWidth);
            int iWidthIndex = fWidthIndex * m_iWidth;
            float fCurrentMapHeight = Get_HeightValue(0, iWidthIndex * m_vScaleFactor.y);
            
            if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) > fUpperEdgeMax)
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(255, 0, 0);
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) >= fUpperEdgeMin && (fCurrentEdgeHeight - fCurrentMapHeight) <= fUpperEdgeMax)
            {
                glm::vec3 vMixColor = glm::mix(glm::vec3(255.0f, 0.0f, 0.0f), glm::vec3(0.0f, 255.0f, 0.0f), fUpperEdgeMax - (fCurrentEdgeHeight - fCurrentMapHeight));
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(static_cast<unsigned char>(vMixColor.x), static_cast<unsigned char>(vMixColor.y), static_cast<unsigned char>(vMixColor.z));
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight)
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 255, 0);
            }
            else
            {
                pTextureEdgesMask[i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 0, 255);
            }
        }
        iTextureBlockSize = iTextureEdgesMaskWidth * (iTextureEdgesMaskHeight / 4) * 3;
        for(int j = 0; j < iTextureEdgesMaskHeight / 4; j++)
        {
            float fCurrentEdgeHeight = (static_cast<float>(j) - (static_cast<float>(iTextureEdgesMaskWidth) / 2.0f)) / 8.0f;
            float fWidthIndex = static_cast<float>(i) / static_cast<float>(iTextureEdgesMaskWidth);
            int iWidthIndex = fWidthIndex * m_iWidth;
            float fCurrentMapHeight = Get_HeightValue((m_iWidth - 1) * m_vScaleFactor.x, iWidthIndex * m_vScaleFactor.y);
            
            if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) > fUpperEdgeMax)
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(255, 0, 0);
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight && (fCurrentEdgeHeight - fCurrentMapHeight) >= fUpperEdgeMin && (fCurrentEdgeHeight - fCurrentMapHeight) <= fUpperEdgeMax)
            {
                glm::vec3 vMixColor = glm::mix(glm::vec3(255.0f, 0.0f, 0.0f), glm::vec3(0.0f, 255.0f, 0.0f), fUpperEdgeMax - (fCurrentEdgeHeight - fCurrentMapHeight));
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(static_cast<unsigned char>(vMixColor.x), static_cast<unsigned char>(vMixColor.y), static_cast<unsigned char>(vMixColor.z));
            }
            else if( fCurrentEdgeHeight >= fCurrentMapHeight)
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 255, 0);
            }
            else
            {
                pTextureEdgesMask[(iTextureEdgesMaskWidth - 1) - i + j * iTextureEdgesMaskWidth + iTextureBlockSize] = RGB(0, 0, 255);
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iTextureEdgesMaskWidth, iTextureEdgesMaskHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pTextureEdgesMask);
}

float CHeightMapSetter::Get_HeightValue(float _x, float _z)
{
    _x /= m_vScaleFactor.x;
    _z /= m_vScaleFactor.y;
    _x -= m_fXThreshold;
    _z -= m_fZThreshold;
    int x = static_cast<int>(floor(_x));
    int z = static_cast<int>(floor(_z));
    float dx = _x - x;
    float dy = _z - z;
    
    if((x < 0) || (z < 0) || (x > (m_iWidth - 1)) || (z > (m_iHeight - 1)))
        return -16.0f;
    
    float fHeight_00 = m_pHeightMapData[x + z * m_iWidth];
    
    float fHeight_01 = m_pHeightMapData[x + z * m_iWidth];
    if(z < (m_iHeight - 1) && z >= 0)
    {
        fHeight_01 = m_pHeightMapData[x + (z + 1) * m_iWidth];
    }
    
    float fHeight_10 = m_pHeightMapData[x + z * m_iWidth];
    if(x < (m_iWidth - 1) && x >= 0)
    {
        fHeight_10 = m_pHeightMapData[x + 1 + z * m_iWidth];
    }
    
    float fHeight_11 = m_pHeightMapData[x + z * m_iWidth];
    if(z < (m_iHeight - 1) && z >= 0 && x < (m_iWidth - 1) && x >= 0)
    {
        fHeight_11 = m_pHeightMapData[x + 1 + (z + 1) * m_iWidth];
    }
    
    float fHeight_0 = fHeight_00 * (1.0f - dy) + fHeight_01 * dy;
    float fHeight_1 = fHeight_10 * (1.0f - dy) + fHeight_11 * dy;
    
    return fHeight_0 * (1.0f - dx) + fHeight_1 * dx;
}

void CHeightMapSetter::_Create_TextureSplatting(void)
{
    glGenTextures(1, &m_hTextureSplatting);
    glBindTexture(GL_TEXTURE_2D, m_hTextureSplatting);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unsigned short* pTextureData = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            pTextureData[i + j * m_iHeight] = RGB(255, 0, 0);
            
            if(Get_HeightValue(i * m_vScaleFactor.x, j * m_vScaleFactor.y) > 1.0f)
            {
                pTextureData[i + j * m_iHeight] = RGB(0, 255, 0);
            }
            if(Get_HeightValue(i * m_vScaleFactor.x, j * m_vScaleFactor.y) < 0.1f)
            {
                pTextureData[i + j * m_iHeight] = RGB(0, 0, 255);
            }
            
            if( i == 0 || j == 0 || i == (m_iWidth - 1) * m_vScaleFactor.x || j == (m_iHeight - 1) * m_vScaleFactor.y)
            {
                 pTextureData[i + j * m_iHeight] = RGB(255, 0, 0);
            }

        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pTextureData);
    SAFE_DELETE_ARRAY(pTextureData);
}

void CHeightMapSetter::_Create_TextureHeightmap(void)
{
    glGenTextures(1, &m_hTextureHeightmap);
    glBindTexture(GL_TEXTURE_2D, m_hTextureHeightmap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unsigned short* pTextureData = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            if(Get_HeightValue(i * m_vScaleFactor.x, j * m_vScaleFactor.y) > 0.0f || Get_HeightValue(i * m_vScaleFactor.x, j * m_vScaleFactor.y) < -1.0f)
            {
                pTextureData[i + j * m_iHeight] = RGB(0, static_cast<unsigned char>(255), 0);
            }
            else
            {
                pTextureData[i + j * m_iHeight] = RGB(static_cast<unsigned char>(fabsf(Get_HeightValue(i * m_vScaleFactor.x, j * m_vScaleFactor.y)) * 255), 0, 0);
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pTextureData);
    SAFE_DELETE_ARRAY(pTextureData);
}

void CHeightMapSetter::_Create_TextureDetail(void)
{
    CVertexBufferPositionTexcoord* pVertexBuffer = new CVertexBufferPositionTexcoord(4, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pVertexBuffer->Lock());
    
    unsigned i = 0;
    pVertexBufferData[i].m_vPosition = glm::vec3(-1.0f,-1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(0.0f,0.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(-1.0f,1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(0.0f,1.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(1.0f,-1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(1.0f,0.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(1.0f,1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(1.0f,1.0f);
    i++;
    
    CIndexBuffer* pIndexBuffer = new CIndexBuffer(6, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pIndexBuffer->Get_SourceData();
    
    i = 0;
    pIndexBufferData[i++] = 0;
    pIndexBufferData[i++] = 1;
    pIndexBufferData[i++] = 2;
    
    pIndexBufferData[i++] = 3; 
    pIndexBufferData[i++] = 2; 
    pIndexBufferData[i++] = 1;
    
    m_pPreRenderScreenQuad = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pPreRenderScreenQuad->Set_VertexBufferRef(pVertexBuffer);
    m_pPreRenderScreenQuad->Set_IndexBufferRef(pIndexBuffer);
    
    m_pPreRenderScreenQuad->Get_VertexBufferRef()->Commit();
    m_pPreRenderScreenQuad->Get_IndexBufferRef()->Commit();
    
    m_pPreRenderShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL);
    m_pPreRenderScreenQuad->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SIMPLE, m_pPreRenderShader);
}

void CHeightMapSetter::Update(void)
{
    if(!m_bIsTexturePreRender)
    {
        CSceneMgr::Instance()->Get_RenderMgr()->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
        
        CMaterial::Set_ExtCommitedShaderRef(m_pPreRenderShader);
        
        CTexture** pTextures = new CTexture*[k_TEXTURES_MAX_COUNT];
        pTextures[0] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_01_diffuse.pvr"));
        pTextures[1] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_01_normal.pvr"));
        pTextures[2] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_02_diffuse.pvr"));
        pTextures[3] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_02_bump.pvr"));
        pTextures[4] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_03_diffuse.pvr"));
        pTextures[5] = static_cast<CTexture*>(CResourceMgr::Instance()->LoadSync(IResource::E_MGR_TEXTURE, "layer_01_normal.pvr"));
        pTextures[6] = nullptr;
        pTextures[7] = nullptr;
        
        unsigned int iTextureIndex = 0;
        for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; i += 2)
        {
            CTexture* pTexture = pTextures[i];
            if(pTexture == nullptr)
            {
                continue;
            }
            m_pPreRenderShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(iTextureIndex));
            iTextureIndex++;
        }
        
        m_pPreRenderShader->Set_Texture(Get_TextureSplatting(), CShader::E_TEXTURE_SLOT_07);
        
        m_pPreRenderScreenQuad->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SIMPLE);
        m_pPreRenderScreenQuad->Get_IndexBufferRef()->Enable();
        glDrawElements(GL_TRIANGLES, m_pPreRenderScreenQuad->Get_IndexBufferRef()->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pPreRenderScreenQuad->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
        m_pPreRenderScreenQuad->Get_IndexBufferRef()->Disable();
        m_pPreRenderScreenQuad->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SIMPLE);
        
        CSceneMgr::Instance()->Get_RenderMgr()->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
        m_iHandleTextureColor = CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
        
        CSceneMgr::Instance()->Get_RenderMgr()->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
        
        CMaterial::Set_ExtCommitedShaderRef(m_pPreRenderShader);
        
        iTextureIndex = 0;
        for(unsigned int i = 1; i < k_TEXTURES_MAX_COUNT; i += 2)
        {
            CTexture* pTexture = pTextures[i];
            if(pTexture == NULL)
            {
                continue;
            }
            m_pPreRenderShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(iTextureIndex));
            iTextureIndex++;
        }
        
        m_pPreRenderShader->Set_Texture(Get_TextureSplatting(), CShader::E_TEXTURE_SLOT_07);
        
        m_pPreRenderScreenQuad->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SIMPLE);
        m_pPreRenderScreenQuad->Get_IndexBufferRef()->Enable();
        glDrawElements(GL_TRIANGLES, m_pPreRenderScreenQuad->Get_IndexBufferRef()->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pPreRenderScreenQuad->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
        m_pPreRenderScreenQuad->Get_IndexBufferRef()->Disable();
        m_pPreRenderScreenQuad->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SIMPLE);
        
        CSceneMgr::Instance()->Get_RenderMgr()->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
        m_iHandleTextureNormal = CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
        
        m_bIsTexturePreRender = true;
    }
}


void CHeightMapSetter::_CalculateNormals(IVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer)
{
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(_pVertexBuffer->Lock());
    unsigned short* pIndexBufferData = _pIndexBuffer->Get_SourceData();
    unsigned int iNumIndexes = _pIndexBuffer->Get_NumIndexes();
    for(unsigned int index = 0; index < iNumIndexes; index += 3)
    {
        glm::vec3 vPoint_01 = pVertexBufferData[pIndexBufferData[index + 0]].m_vPosition;
        glm::vec3 vPoint_02 = pVertexBufferData[pIndexBufferData[index + 1]].m_vPosition;
        glm::vec3 vPoint_03 = pVertexBufferData[pIndexBufferData[index + 2]].m_vPosition;
        
        glm::vec3 vEdge_01 = vPoint_02 - vPoint_01;
        glm::vec3 vEdge_02 = vPoint_03 - vPoint_01;
        glm::vec3 vNormal = glm::cross(vEdge_01, vEdge_02);
        vNormal = glm::normalize(vNormal);
        glm::u8vec4 vByteNormal = IVertexBuffer::CompressVEC3(vNormal);
        pVertexBufferData[pIndexBufferData[index + 0]].m_vNormal = vByteNormal;
        pVertexBufferData[pIndexBufferData[index + 1]].m_vNormal = vByteNormal;
        pVertexBufferData[pIndexBufferData[index + 2]].m_vNormal = vByteNormal;
    }
}

void CHeightMapSetter::_CalculateTangentsAndBinormals(IVertexBuffer* _pVertexBuffer, CIndexBuffer* _pIndexBuffer)
{
	register int i, j;
	std::vector<glm::vec3> lTangents, lBinormals;
    
	int iNumIndexes = _pIndexBuffer->Get_NumIndexes();
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(_pVertexBuffer->Lock());
    unsigned short* pIndexBufferData = _pIndexBuffer->Get_SourceData();
	
    for ( i = 0; i < iNumIndexes; i += 3 )
	{
		glm::vec3 v1 = pVertexBufferData[pIndexBufferData[i + 0]].m_vPosition;
		glm::vec3 v2 = pVertexBufferData[pIndexBufferData[i + 1]].m_vPosition;
		glm::vec3 v3 = pVertexBufferData[pIndexBufferData[i + 2]].m_vPosition;
		float s1 = pVertexBufferData[pIndexBufferData[i + 0]].m_vTexcoord.x;
		float t1 = pVertexBufferData[pIndexBufferData[i + 0]].m_vTexcoord.y;
		float s2 = pVertexBufferData[pIndexBufferData[i + 1]].m_vTexcoord.x;
		float t2 = pVertexBufferData[pIndexBufferData[i + 1]].m_vTexcoord.y;
		float s3 = pVertexBufferData[pIndexBufferData[i + 2]].m_vTexcoord.x;
		float t3 = pVertexBufferData[pIndexBufferData[i + 2]].m_vTexcoord.y;
        
		glm::vec3  t, b;
		_CalculateTriangleBasis(v1, v2, v3, s1, t1, s2, t2, s3, t3, t, b);
		lTangents.push_back(t);
		lBinormals.push_back(b);
	}
    
    int iNumVertexes = _pVertexBuffer->Get_NumVertexes();
	for (i = 0; i < iNumVertexes; i++)
	{
		std::vector<glm::vec3> lrt, lrb;
		for (j = 0; j < iNumIndexes; j += 3)
		{
			if ((pIndexBufferData[j + 0]) == i || (pIndexBufferData[j + 1]) == i || (pIndexBufferData[j + 2]) == i)
			{
				lrt.push_back(lTangents[i]);
				lrb.push_back(lBinormals[i]);
			}
		}
        
        glm::vec3 vTangentRes(0.0f, 0.0f, 0.0f);
        glm::vec3 vBinormalRes(0.0f, 0.0f, 0.0f);
		for (j = 0; j < lrt.size(); j++)
		{
			vTangentRes += lrt[j];
			vBinormalRes += lrb[j];
		}
		vTangentRes /= float(lrt.size());
		vBinormalRes /= float(lrb.size());
        
        glm::vec3 vNormal = IVertexBuffer::UnCompressU8VEC4(pVertexBufferData[i].m_vNormal);
		vTangentRes = _Ortogonalize(vNormal, vTangentRes);
		vBinormalRes = _Ortogonalize(vNormal, vBinormalRes);
        
        pVertexBufferData[i].m_vTangent = IVertexBuffer::CompressVEC3(vTangentRes);
	}
}


void CHeightMapSetter::_CalculateTriangleBasis( const glm::vec3& E, const glm::vec3& F, const glm::vec3& G, float sE,
                                               float tE, float sF, float tF, float sG, float tG, glm::vec3& tangentX,
                                               glm::vec3& tangentY )
{
    glm::vec3 P = F - E;
    glm::vec3 Q = G - E;
	float s1 = sF - sE;
	float t1 = tF - tE;
	float s2 = sG - sE;
	float t2 = tG - tE;
	float pqMatrix[2][3];
	pqMatrix[0][0] = P[0];
	pqMatrix[0][1] = P[1];
	pqMatrix[0][2] = P[2];
	pqMatrix[1][0] = Q[0];
	pqMatrix[1][1] = Q[1];
	pqMatrix[1][2] = Q[2];
	float temp = 1.0f / ( s1 * t2 - s2 * t1);
	float stMatrix[2][2];
	stMatrix[0][0] =  t2 * temp;
	stMatrix[0][1] = -t1 * temp;
	stMatrix[1][0] = -s2 * temp;
	stMatrix[1][1] =  s1 * temp;
	float tbMatrix[2][3];
	tbMatrix[0][0] = stMatrix[0][0] * pqMatrix[0][0] + stMatrix[0][1] * pqMatrix[1][0];
	tbMatrix[0][1] = stMatrix[0][0] * pqMatrix[0][1] + stMatrix[0][1] * pqMatrix[1][1];
	tbMatrix[0][2] = stMatrix[0][0] * pqMatrix[0][2] + stMatrix[0][1] * pqMatrix[1][2];
	tbMatrix[1][0] = stMatrix[1][0] * pqMatrix[0][0] + stMatrix[1][1] * pqMatrix[1][0];
	tbMatrix[1][1] = stMatrix[1][0] * pqMatrix[0][1] + stMatrix[1][1] * pqMatrix[1][1];
	tbMatrix[1][2] = stMatrix[1][0] * pqMatrix[0][2] + stMatrix[1][1] * pqMatrix[1][2];
	tangentX = glm::vec3( tbMatrix[0][0], tbMatrix[0][1], tbMatrix[0][2] );
	tangentY = glm::vec3( tbMatrix[1][0], tbMatrix[1][1], tbMatrix[1][2] );
	tangentX = glm::normalize(tangentX);
	tangentY = glm::normalize(tangentY);
}

glm::vec3 CHeightMapSetter::_ClosestPointOnLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p)
{
    glm::vec3 c = p - a;
    glm::vec3 V = b - a;
	float d = V.length();
	V = glm::normalize(V);
	float t = glm::dot( V, c );
    
	if ( t < 0.0f )
		return a;
	if ( t > d )
		return b;
    
	V *= t;
	return ( a + V );
}

glm::vec3 CHeightMapSetter::_Ortogonalize(const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 v2ProjV1 = _ClosestPointOnLine( v1, -v1, v2 );
	glm::vec3 res = v2 - v2ProjV1;
	res = glm::normalize(res);
	return res;
}


