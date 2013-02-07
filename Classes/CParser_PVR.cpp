//
//  CPVRLoader.cpp
//  iGaia
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CParser_PVR.h"
#include "CCommon_IOS.h"
#include "CTexture.h"

CParser_PVR::CParser_PVR(void)
{

}

CParser_PVR::~CParser_PVR(void)
{

}

E_PARSER_STATUS CParser_PVR::Read(const std::string& _sName, IResource* _resource)
{
    std::string sPath = Get_BundlePath();

    std::ifstream tStream;
    tStream.open(sPath.c_str(), std::ios::binary);
    tStream.seekg(0, std::ios::end);
    i32 iLenght = tStream.tellg();
    tStream.seekg(0, std::ios::beg);
    i8* pData = new i8[iLenght];
    tStream.read((char*)pData, iLenght);
    tStream.close();

    GLenum eFormat = 0;
    i32 iBytesPerPixel = 0;
    glm::vec2 vSize = glm::vec2(0.0f, 0.0f);
    bool bCompressed = false;
    ui32 iHeaderSize = 0;

    if(*(PVRTuint32*)pData != PVRTEX3_IDENT)
	{
        PVR_Texture_Header* pHeader;
        pHeader = (PVR_Texture_Header*)pData;
        switch (pHeader->dwpfFlags & PVRTEX_PIXELTYPE)
        {
            case OGL_PVRTC2:
                if(pHeader->dwAlphaBitMask)
                {
                    iBytesPerPixel = 2;
                    eFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
                }
                else
                {
                    iBytesPerPixel = 2;
                    eFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
                }
                break;
            case OGL_PVRTC4:
                if(pHeader->dwAlphaBitMask)
                {
                    iBytesPerPixel = 4;
                    eFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
                }
                else
                {
                    iBytesPerPixel = 4;
                    eFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
                }
                break;
            default:
                return E_PARSER_STATUS_ERROR;
        }
        vSize.x = pHeader->dwWidth;
        vSize.y = pHeader->dwHeight;
        bCompressed = true;
        iHeaderSize = pHeader->dwHeaderSize;
    }
    else
    {
        PVRTextureHeaderV3* header = (PVRTextureHeaderV3*)pData;
        PVRTuint64 pixelFormat = header->u64PixelFormat;
        switch (pixelFormat)
		{
            case 0:
            {
                iBytesPerPixel = 2;
                m_tFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            }
                break;
            case 1:
            {
                iBytesPerPixel = 2;
                m_tFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
            }
                break;
            case 2:
            {
                iBytesPerPixel = 4;
                m_tFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
            }
            case 3:
            {
                iBytesPerPixel = 4;
                m_tFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            }
                break;
            default:
                m_eStatus = E_PARSER_STATUS_ERROR;
                return;
        }
        vSize.x = header->u32Width;
        vSize.y = header->u32Height;
        bCompressed = true;
        iHeaderSize = PVRTEX3_HEADERSIZE + header->u32MetaDataSize;
        m_eStatus = E_PARSER_STATUS_DONE;
    }
}

void CParser_PVR::CommitToVRAM(void)
{
    i32 width  = m_vSize.x;
    i32 height = m_vSize.y;
    i8* data = m_pData + m_iHeaderSize;

    ui32 handle = 0;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    for (ui32 level = 0; width > 0 && height > 0; ++level)
    {
        GLsizei size = std::max(32, width * height * m_iBytesPerPixel / 8);
        glCompressedTexImage2D(GL_TEXTURE_2D, level, m_tFormat, width, height, 0, size, data);
        data += size;
        width >>= 1; height >>= 1;
    }

    

}


