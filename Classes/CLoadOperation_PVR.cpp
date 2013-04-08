//
//  CLoadOperation_PVR.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "CLoadOperation_PVR.h"
#include "CCommon.h"
#include "CTexture.h"

CLoadOperation_PVR::CLoadOperation_PVR(void)
{
    m_status = E_PARSER_STATUS_UNKNOWN;
}

CLoadOperation_PVR::~CLoadOperation_PVR(void)
{

}

void CLoadOperation_PVR::Load(const std::string& _filename)
{
    m_status = E_PARSER_STATUS_PROCESS;
    m_name = _filename;

    std::string path(Get_BundlePath());
    path.append(m_name);

    std::ifstream stream;
    stream.open(path.c_str(), std::ios::binary);
    if (!stream.is_open())
    {
        m_status = E_PARSER_STATUS_ERROR;
        return;
    }
    stream.seekg(0, std::ios::end);
    i32 lenght = stream.tellg();
    stream.seekg(0, std::ios::beg);
    m_data = new ui8[lenght];
    stream.read((char*)m_data, lenght);
    stream.close();

    if(*(PVRTuint32*)m_data != PVRTEX3_IDENT)
	{
        PVR_Texture_Header* header;
        header = (PVR_Texture_Header*)m_data;
        switch (header->dwpfFlags & PVRTEX_PIXELTYPE)
        {
            case OGL_PVRTC2:
                if(header->dwAlphaBitMask)
                {
                    m_bpp = 2;
                    m_format = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
					m_compressed = true;
                }
                else
                {
                    m_bpp = 2;
                    m_format = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
					m_compressed = true;
                }
                break;
            case OGL_PVRTC4:
                if(header->dwAlphaBitMask)
                {
                    m_bpp = 4;
                    m_format = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
					m_compressed = true;
                }
                else
                {
                    m_bpp = 4;
                    m_format = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
					m_compressed = true;
                }
                break;
			case OGL_RGBA_8888:
				m_bpp = 32;
				m_format = GL_RGBA;
				m_compressed = false;
				break;
            default:
            {
                 m_status = E_PARSER_STATUS_ERROR;
            }
                break;
        }
        m_width = header->dwWidth;
        m_height = header->dwHeight;
        m_headerOffset = header->dwHeaderSize;
		m_mipCount = header->dwMipMapCount;
        m_status = E_PARSER_STATUS_DONE;
    }
    else
    {
        PVRTextureHeaderV3* header = (PVRTextureHeaderV3*)m_data;
        PVRTuint64 pixelFormat = header->u64PixelFormat;
		PVRTuint64 pixelFormatPartHigh = pixelFormat & PVRTEX_PFHIGHMASK;
		if (pixelFormatPartHigh==0)
		{
			switch (pixelFormat)
			{
			case 0:
				{
					m_bpp = 2;
					m_format = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
					m_compressed = true;
				}
				break;
			case 1:
				{
					m_bpp = 2;
					m_format = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
					m_compressed = true;
				}
				break;
			case 2:
				{
					m_bpp = 4;
					m_format = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
					m_compressed = true;
				}
			case 3:
				{
					m_bpp = 4;
					m_format = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
					m_compressed = true;
				}
				break;
			default:
				{
					m_status = E_PARSER_STATUS_ERROR;
				}
				break;
			}
		}
		else
		{
			EPVRTVariableType channelType = (EPVRTVariableType)header->u32ChannelType;
			if(channelType == ePVRTVarTypeUnsignedByteNorm)
			{
				m_bpp = 32;
				m_format = GL_RGBA;
				m_compressed = false;
			}
			else
			{
				m_status = E_PARSER_STATUS_ERROR;
			}
		}
        m_width = header->u32Width;
        m_height = header->u32Height;
        m_headerOffset = PVRTEX3_HEADERSIZE + header->u32MetaDataSize;
		m_mipCount = header->u32MIPMapCount;
        m_status = E_PARSER_STATUS_DONE;
    }
}

IResource_INTERFACE* CLoadOperation_PVR::Build(void)
{
    ui8* data = m_data + m_headerOffset;

    ui32 handle = 0;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ui32 width = m_width;
	ui32 height = m_height;


	if (m_compressed)
	{
		for (ui32 level = 0; level < m_mipCount && width > 0 && height > 0; ++level)
		{
			GLsizei size = MAX_VALUE(32, static_cast<i32>(width) * static_cast<i32>(height) * m_bpp / 8);
			glCompressedTexImage2D(GL_TEXTURE_2D, level, m_format, width, height, 0, size, data);
			data += size;
			width >>= 1; height >>= 1;
		}
	}
	else
	{
		for (ui32 level = 0; level < m_mipCount && width > 0 && height > 0; ++level)
		{
			GLsizei size = MAX_VALUE(32, static_cast<i32>(width) * static_cast<i32>(height) * m_bpp / 8);
			glTexImage2D(GL_TEXTURE_2D, level, m_format, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);
			data += size;
			width >>= 1; height >>= 1;
		}
	}

    CTexture* texture = new CTexture();
    texture->Link(handle, m_width, m_height);
    Register(texture);
    return texture;
}
