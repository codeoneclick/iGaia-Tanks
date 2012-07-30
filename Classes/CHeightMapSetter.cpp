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

CHeightMapSetter::CHeightMapSetter(void)
{
    m_pDataSource = NULL;
    m_fXThreshold = 0.0f;
    m_fZThreshold = 0.0f;
    m_pTextureSplattingDataSource = NULL;
    m_pPostRenderScreenPlaneMesh = NULL;
    m_pPostRenderScreenPlaneShader = NULL;
    
    m_bIsTextureDetailCreated = false;
}

CHeightMapSetter::~CHeightMapSetter(void)
{
    SAFE_DELETE_ARRAY(m_pDataSource);
    SAFE_DELETE_ARRAY(m_pTextureSplattingDataSource);
    glDeleteTextures(1, &m_hTextureSplatting);
}

CMesh* CHeightMapSetter::Load_DataSource(const std::string _sName, int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
    
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = m_iWidth * m_iHeight;
    pSourceData->m_iNumIndexes  = (m_iWidth - 1) * (m_iHeight - 1) * 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    m_pDataSource = new float[m_iWidth * m_iHeight];
    
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iWidth;++i)
    {
        for(unsigned int j = 0; j < m_iHeight;++j)
        {
            pVertexBufferData[index].m_vPosition.x = i;
            pVertexBufferData[index].m_vPosition.y = sin(i * 0.33f) / 2.0f + cos(j * 0.33f) / 2.0f;
            m_pDataSource[i + j * m_iWidth] = pVertexBufferData[index].m_vPosition.y;
            pVertexBufferData[index].m_vPosition.z = j;
            
            pVertexBufferData[index].m_vTexcoord.x = i / static_cast<float>(m_iWidth);
            pVertexBufferData[index].m_vTexcoord.y = j / static_cast<float>(m_iHeight);
            ++index;
        }
    }
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STREAM_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
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
    
    _CalculateNormals(pSourceData->m_pVertexBuffer, pSourceData->m_pIndexBuffer);
    _CalculateTangentsAndBinormals(pSourceData->m_pVertexBuffer, pSourceData->m_pIndexBuffer);
    CMesh* pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    pMesh->Set_SourceData(pSourceData);
    
    /*CParser_MDL* pParser = new CParser_MDL();
    pParser->Load(_sName);
    pParser->Commit();
    
    CMesh* pMesh = new CMesh();
    if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
    {
        pMesh->Set_SourceData(pParser->Get_SourceData());
    }

    glm::vec3* pPositionData = pMesh->Get_VertexBufferRef()->CreateOrReUse_PositionData();
    m_pDataSource = new float[m_iWidth * m_iHeight];
    for(unsigned int i = 0; i < m_iWidth; ++i)
    {
        for(unsigned int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
            pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y = fHeight;
            m_pDataSource[i + j * m_iHeight] = pPositionData[i + ((m_iWidth - 1) - j) * m_iWidth].y;
        }
    }*/
    
    _Create_TextureSplatting();
    _Create_TextureHeightmap();
    _Create_TextureDetail();
    
    return pMesh;
}

void CHeightMapSetter::_Create_LandscapeEdges(void)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = m_iWidth * 8;
    pSourceData->m_iNumIndexes  = (m_iWidth - 1) * (8 - 1) * 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoordNormalTangent(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    
    CVertexBufferPositionTexcoordNormalTangent::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoordNormalTangent::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iWidth;++i)
    {
        for(unsigned int j = 0; j < 2;++j)
        {
            pVertexBufferData[index].m_vPosition.x = i;
            if(j == 1)
            {
                pVertexBufferData[index].m_vPosition.y = -16.0f;
            }
            else
            {
                pVertexBufferData[index].m_vPosition.y = m_pDataSource[i + 0];
            }
            pVertexBufferData[index].m_vPosition.z = 0.0f;
            
            pVertexBufferData[index].m_vTexcoord.x = i / static_cast<float>(m_iWidth);
            pVertexBufferData[index].m_vTexcoord.y = j;
            ++index;
        }
    }
    
    for(unsigned int i = 0; i < m_iWidth;++i)
    {
        for(unsigned int j = 0; j < 2;++j)
        {
            pVertexBufferData[index].m_vPosition.x = i;
            if(j == 1)
            {
                pVertexBufferData[index].m_vPosition.y = -16.0f;
            }
            else
            {
                pVertexBufferData[index].m_vPosition.y = m_pDataSource[i + (m_iHeight - 1) * m_iWidth];
            }
            pVertexBufferData[index].m_vPosition.z = m_iHeight;
            
            pVertexBufferData[index].m_vTexcoord.x = i / static_cast<float>(m_iWidth);
            pVertexBufferData[index].m_vTexcoord.y = j;
            ++index;
        }
    }
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STREAM_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    memset(pIndexBufferData,0x0, sizeof(unsigned short) * pSourceData->m_iNumIndexes);
    index = 0;
    for(unsigned int i = 0; i < (m_iWidth - 1); ++i)
    {
        for(unsigned int j = 0; j < (2 - 1); ++j)
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
}

float CHeightMapSetter::Get_HeightValue(float _x, float _z)
{
    _x -= m_fXThreshold;
    _z -= m_fZThreshold;
    int x = static_cast<int>(floor(_x));
    int z = static_cast<int>(floor(_z));
    float dx = _x - x;
    float dy = _z - z;
    
    if((x <= 0) || (z <= 0) || (x >= (m_iWidth - 1)) || (z >= (m_iHeight - 1)))
        return -16.0f;
    
    float fHeight_00 = m_pDataSource[x + z * m_iWidth];
    float fHeight_01 = m_pDataSource[x + (z + 1) * m_iWidth];
    float fHeight_10 = m_pDataSource[x + 1 + z * m_iWidth];
    float fHeight_11 = m_pDataSource[x + 1 + (z + 1) * m_iWidth];
    
    float fHeight_0 = fHeight_00 * (1 - dy) + fHeight_01 * dy;
    float fHeight_1 = fHeight_10 * (1 - dy) + fHeight_11 * dy;
    
    return fHeight_0 * (1 - dx) + fHeight_1 * dx;
}
#define RGB(r,g,b) (unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))
void CHeightMapSetter::_Create_TextureSplatting(void)
{
    glGenTextures(1, &m_hTextureSplatting);
    glBindTexture(GL_TEXTURE_2D, m_hTextureSplatting);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    m_pTextureSplattingDataSource = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(255, 0, 0);
            
            if(Get_HeightValue(i, j) > 1.0f)
            {
                m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(0, 255, 0);
            }
            if(Get_HeightValue(i, j) < 0.1f)
            {
                m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(0, 0, 255);
            }
            
            if( i == 0 || j == 0 || i == (m_iWidth - 1) || j == (m_iHeight - 1))
            {
                 m_pTextureSplattingDataSource[i + j * m_iHeight] = RGB(255, 0, 0);
            }

        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, m_pTextureSplattingDataSource);
}

void CHeightMapSetter::_Create_TextureHeightmap(void)
{
    glGenTextures(1, &m_hTextureHeightmap);
    glBindTexture(GL_TEXTURE_2D, m_hTextureHeightmap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unsigned short* m_pTextureData = new unsigned short[m_iWidth * m_iHeight];
    for(int i = 0; i < m_iWidth; i++)
    {
        for(int j = 0; j < m_iHeight; j++)
        {
            if(Get_HeightValue(i, j) > 0.0f || Get_HeightValue(i, j) < -1.0f)
            {
                m_pTextureData[i + j * m_iHeight] = RGB(0, static_cast<unsigned char>(255), 0);
            }
            else
            {
                m_pTextureData[i + j * m_iHeight] = RGB(static_cast<unsigned char>(fabsf(Get_HeightValue(i, j)) * 255), 0, 0);
            }
            //unsigned char iColor = static_cast<unsigned char>((Get_HeightValue(i, j)  + 1.0f) * 0.5f * 255.0f);
            //std::cout<<"[_Create_TextureHeightmap] iColor = "<<static_cast<int>(iColor)<<std::endl;
            //m_pTextureData[i + j * m_iHeight] = RGB(iColor, 0, 0);
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, m_pTextureData);
    delete[] m_pTextureData;
}

void CHeightMapSetter::_Create_TextureDetail(void)
{
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 4;
    pSourceData->m_iNumIndexes  = 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    
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
    
    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes, GL_STATIC_DRAW);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    i = 0;
    pIndexBufferData[i++] = 0;
    pIndexBufferData[i++] = 1;
    pIndexBufferData[i++] = 2;
    
    pIndexBufferData[i++] = 3; 
    pIndexBufferData[i++] = 2; 
    pIndexBufferData[i++] = 1;
    
    m_pPostRenderScreenPlaneMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pPostRenderScreenPlaneMesh->Set_SourceData(pSourceData);
    
    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Commit();
    m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Commit();
    
    m_pPostRenderScreenPlaneShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL);
    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SIMPLE, m_pPostRenderScreenPlaneShader);
}

void CHeightMapSetter::Draw_TextureDetail(void)
{
    CSceneMgr::Instance()->Get_RenderMgr()->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
    
    CMaterial::Set_ExtCommitedShaderRef(m_pPostRenderScreenPlaneShader);
    
    unsigned int iTextureIndex = 0;
    for(unsigned int i = 0; i < k_TEXTURES_MAX_COUNT; i += 2)
    {
        CTexture* pTexture = m_pTexturesDetailLayers[i];
        if(pTexture == NULL)
        {
            continue;
        }
        m_pPostRenderScreenPlaneShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(iTextureIndex));
        iTextureIndex++;
    }
    
    m_pPostRenderScreenPlaneShader->Set_Texture(Get_TextureSplatting(), CShader::E_TEXTURE_SLOT_07);

    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SIMPLE);
    m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pPostRenderScreenPlaneMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Disable();
    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SIMPLE);
    
    
    CSceneMgr::Instance()->Get_RenderMgr()->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
    m_hTextureDetailColor = CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_COLOR);
    
    
    CSceneMgr::Instance()->Get_RenderMgr()->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
    
    CMaterial::Set_ExtCommitedShaderRef(m_pPostRenderScreenPlaneShader);
    
    iTextureIndex = 0;
    for(unsigned int i = 1; i < k_TEXTURES_MAX_COUNT; i += 2)
    {
        CTexture* pTexture = m_pTexturesDetailLayers[i];
        if(pTexture == NULL)
        {
            continue;
        }
        m_pPostRenderScreenPlaneShader->Set_Texture(pTexture->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(iTextureIndex));
        iTextureIndex++;
    }
    
    m_pPostRenderScreenPlaneShader->Set_Texture(Get_TextureSplatting(), CShader::E_TEXTURE_SLOT_07);
    
    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SIMPLE);
    m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pPostRenderScreenPlaneMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pPostRenderScreenPlaneMesh->Get_IndexBufferRef()->Disable();
    m_pPostRenderScreenPlaneMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SIMPLE);
    
    CSceneMgr::Instance()->Get_RenderMgr()->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
    m_hTextureDetailNormal = CSceneMgr::Instance()->Get_RenderMgr()->Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE_LANDSCAPE_DETAIL_NORMAL);
    
    
    m_bIsTextureDetailCreated = true;
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


