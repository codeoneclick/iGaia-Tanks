//
//  CPVRLoader.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_PVR.h"
#include <fstream>
#include <strstream>
#include "CCommon_IOS.h"

CParser_PVR::CParser_PVR(void)
{
    m_pSourceData = NULL;
    m_pData = NULL;
}

CParser_PVR::~CParser_PVR(void)
{
    if(m_pData != NULL)
    {
        delete m_pData;
        m_pData = NULL;
    }
}

void CParser_PVR::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;
    
    std::string sFileName = Get_ResourceFileName(_sName); 
    std::ifstream pStream;
    pStream.open(sFileName.c_str(), std::ios::binary);
    pStream.seekg( 0, std::ios::end );
    int iLength = pStream.tellg();
    pStream.seekg( 0, std::ios::beg );
    m_pData = new char[iLength];
    pStream.read( m_pData, iLength );
    pStream.close();
    
    m_pDescription = new SDescription();
   
    if(*(PVRTuint32*)m_pData != PVRTEX3_IDENT)
	{
        std::cout<<"[CParser_PVR::Load] OLD PVR format"<<std::endl;
        PVR_Texture_Header* pHeader;
        pHeader = (PVR_Texture_Header*)m_pData;
        
        switch (pHeader->dwpfFlags & PVRTEX_PIXELTYPE) 
        {
            case OGL_PVRTC2:
                if(pHeader->dwAlphaBitMask)
                {
                    m_pDescription->m_uiBPP = 2;
                    m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
                }
                else
                {
                    m_pDescription->m_uiBPP = 2;
                    m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
                }
                break;
            case OGL_PVRTC4:
                if(pHeader->dwAlphaBitMask)
                {
                    m_pDescription->m_uiBPP = 4;
                    m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
                }
                else
                {
                    m_pDescription->m_uiBPP = 4;
                    m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
                }
                break;
            default:
                std::cout<<"[CParser_PVR::Load] Unsupported format for Texture Name : "<<_sName<<"\n";
                m_eStatus = E_ERROR_STATUS;
                return;
        }
        m_pDescription->m_vSize.x = pHeader->dwWidth;
        m_pDescription->m_vSize.y = pHeader->dwHeight;
        m_pDescription->m_uiMIP = pHeader->dwMipMapCount ? pHeader->dwMipMapCount : 1;
        m_pDescription->m_bCompressed = true;
        m_pDescription->m_pTextureData = m_pData + pHeader->dwHeaderSize;
        m_pDescription->m_iNumFaces = 1;
    }
    else
    {
        std::cout<<"[CParser_PVR::Load] NEW PVR format"<<std::endl;
        PVRTextureHeaderV3* pHeader = (PVRTextureHeaderV3*)m_pData;
        PVRTuint64 iPixelFormat = pHeader->u64PixelFormat;
        
        switch (iPixelFormat)
		{
            case 0:
			 {
                m_pDescription->m_uiBPP = 2;
				 m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
			 }
                break;
            case 1:
			 {
                m_pDescription->m_uiBPP = 2;
				 m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			 }
                break;
            case 2:
			 {
                m_pDescription->m_uiBPP = 4;
                m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
			 }
            case 3:
			 {
                m_pDescription->m_uiBPP = 4;
                m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			 }
                break;
            default:
                std::cout<<"[CParser_PVR::Load] Unsupported format for Texture Name : "<<_sName<<"\n";
                m_eStatus = E_ERROR_STATUS;
                return;
        }
        m_pDescription->m_vSize.x = pHeader->u32Width;
        m_pDescription->m_vSize.y = pHeader->u32Height;
        m_pDescription->m_uiMIP = pHeader->u32MIPMapCount ? pHeader->u32MIPMapCount : 1;
        m_pDescription->m_bCompressed = true;
        m_pDescription->m_pTextureData = m_pData + PVRTEX3_HEADERSIZE + pHeader->u32MetaDataSize;
        m_pDescription->m_iNumFaces = pHeader->u32NumFaces;
    }

    
    std::cout<<"[CParser_PVR::Load] Texture Name : "<<_sName<<" Texture Width : "<<m_pDescription->m_vSize.x<<" Texture Height : "<<m_pDescription->m_vSize.y<<" Texture MIPS : "<<m_pDescription->m_uiMIP<<"\n";
    m_eStatus = E_DONE_STATUS;
}

void CParser_PVR::Commit(void)
{
    int iWidth  = m_pDescription->m_vSize.x;
    int iHeight = m_pDescription->m_vSize.y;
    char* pData = m_pDescription->m_pTextureData;
    
    m_pSourceData = new CTexture::SSourceData();
    m_pSourceData->m_iWidth  = m_pDescription->m_vSize.x;
    m_pSourceData->m_iHeight = m_pDescription->m_vSize.y;
    
    glGenTextures( 1, &m_pSourceData->m_hTextureHanlde );
    
    GLenum iTextureTarget = GL_TEXTURE_2D;
    
    if(m_pDescription->m_iNumFaces > 1)
    {
        iTextureTarget = GL_TEXTURE_CUBE_MAP;
    }
    
    glBindTexture(iTextureTarget, m_pSourceData->m_hTextureHanlde );
    if(iTextureTarget == GL_TEXTURE_2D)
    {
        GLint iWrap = GL_REPEAT;
        if(m_lParams.find("WRAP") != m_lParams.end())
        {
            if(m_lParams.find("WRAP")->second == "CLAMP")
            {
                iWrap = GL_CLAMP_TO_EDGE;
            }
            else if(m_lParams.find("WRAP")->second == "REPEAT")
            {
                iWrap = GL_REPEAT;
            }    
        }
        glTexParameteri(iTextureTarget, GL_TEXTURE_WRAP_S, iWrap);
        glTexParameteri(iTextureTarget, GL_TEXTURE_WRAP_T, iWrap);
        glTexParameteri(iTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(iTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(iTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(iTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(iTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(iTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_pDescription->m_bCompressed = false;
    }
    
    if(iTextureTarget == GL_TEXTURE_CUBE_MAP)
    {
        iTextureTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    }
    
    for(unsigned int iFaces = 0; iFaces < m_pDescription->m_iNumFaces; iFaces++)
    {
        if (m_pDescription->m_bCompressed)
        {
            for (int level = 0; iWidth > 0 && iHeight > 0; ++level)
            {
                GLsizei iSize = std::max(32, iWidth * iHeight * m_pDescription->m_uiBPP / 8);
                glCompressedTexImage2D(iTextureTarget + iFaces, level, m_pDescription->m_glFormat, iWidth, iHeight, 0, iSize, pData);
                pData += iSize;
                iWidth >>= 1; iHeight >>= 1;
            }
        } 
        else
        {       
            glTexImage2D(iTextureTarget + iFaces, 0, m_pDescription->m_glFormat, iWidth, iHeight, 0, m_pDescription->m_glFormat, m_pDescription->m_glType, pData);
            glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
            glGenerateMipmap(iTextureTarget + iFaces);
        }
    }
}


