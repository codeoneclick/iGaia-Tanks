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
    
}

CParser_PVR::~CParser_PVR(void)
{
}

void CParser_PVR::Load(const std::string& _name)
{
    m_status = E_STATUS_LOAD;
    
    std::ifstream stream;
    stream.open(Get_ResourceFileName(_name).c_str(), std::ios::binary);
    stream.seekg(0, std::ios::end);
    int lenght = stream.tellg();
    stream.seekg(0, std::ios::beg);
    m_dataSource = new char[lenght];
    stream.read(m_dataSource, lenght);
    stream.close();
   
    if(*(PVRTuint32*)m_dataSource != PVRTEX3_IDENT)
	{
        std::cout<<"[CParser_PVR::Load] OLD PVR format"<<std::endl;
        PVR_Texture_Header* header = (PVR_Texture_Header*)m_dataSource;
        switch (header->dwpfFlags & PVRTEX_PIXELTYPE) 
        {
            case OGL_PVRTC2:
                if(header->dwAlphaBitMask)
                {
                    m_bytesPerPixel = 2;
                    m_format = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
                }
                else
                {
                    m_bytesPerPixel = 2;
                    m_format = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
                }
                break;
            case OGL_PVRTC4:
                if(header->dwAlphaBitMask)
                {
                    m_bytesPerPixel = 4;
                    m_format = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
                }
                else
                {
                    m_bytesPerPixel = 4;
                    m_format = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
                }
                break;
            default:
                std::cout<<"[CParser_PVR::Load] Unsupported format for Texture Name : "<<_name<<"\n";
                m_status = E_STATUS_ERROR;
                return;
        }
        m_size = glm::vec2(header->dwWidth, header->dwHeight);
        m_headerOffset = header->dwHeaderSize;
    }
    else
    {
        std::cout<<"[CParser_PVR::Load] NEW PVR format"<<std::endl;
        PVRTextureHeaderV3* header = (PVRTextureHeaderV3*)m_dataSource;
        PVRTuint64 pixelFormat = header->u64PixelFormat;
        
        switch (pixelFormat)
		{
            case 0:
			 {
                 m_bytesPerPixel = 2;
				 m_format = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
			 }
                break;
            case 1:
			 {
                 m_bytesPerPixel = 2;
				 m_format = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			 }
                break;
            case 2:
			 {
                m_bytesPerPixel = 4;
                m_format = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
			 }
            case 3:
			 {
                m_bytesPerPixel = 4;
                m_format = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			 }
                break;
            default:
                std::cout<<"[CParser_PVR::Load] Unsupported format for Texture Name : "<<_name<<"\n";
                m_status = E_STATUS_ERROR;
                return;
        }
        m_size = glm::vec2(header->u32Width, header->u32Height);
        m_headerOffset = PVRTEX3_HEADERSIZE + header->u32MetaDataSize;
    }
    m_status = E_STATUS_DONE;
}

IResource* CParser_PVR::Commit(void)
{
    int width  = m_size.x;
    int height = m_size.y;
    char* dataSource = m_dataSource + m_headerOffset;
    
    unsigned int handle = 0;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (int level = 0; width > 0 && height > 0; ++level)
    {
        GLsizei dataSize = std::max(32, width * height * m_bytesPerPixel / 8);
        glCompressedTexImage2D(GL_TEXTURE_2D, level, m_format, width, height, 0, dataSize, dataSource);
        dataSource += dataSize;
        width >>= 1; height >>= 1;
    }
    
    CTexture* texture = new CTexture(handle, m_size.x, m_size.y);
    return texture;
}


