/* 
 * File:   CParser_PNG.cpp
 * Author: void
 * 
 * Created on August 18, 2012, 10:45 PM
 */

#include <sys/syslog.h>

#include "CParser_PNG.h"

#include <Common.h>
#include <Logger.h>

#include <libpng/png.h> // use irrlicht included lib png
#include <libpng/pngstruct.h>

static void png_cpexcept_error(png_structp png_ptr, png_const_charp msg)
{
	LogMessage(LOG_ERR, "PNG FATAL ERROR " <<  msg);
	longjmp(png_ptr->longjmp_buffer, 1);
}

// PNG function for file reading
void PNGAPI user_read_data_fcn(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_size_t check;

	// changed by zola {
	FILE* file=static_cast<FILE*>(png_ptr->io_ptr);

	check=(png_size_t) fread((void*)data, 1, (unsigned int)length, file);
	// }

	if (check != length)
		png_error(png_ptr, "Read Error");
}

void* CParser_PNG::Get_SourceData(void)
{
    return m_pSourceData.get();
}

static unsigned int RGBAtoARGB( unsigned int rgba )
{
        unsigned int argb = rgba &0xFFFFFF00;
        argb += (rgba &0x000000FF) << 24;
        return argb;
}

void CParser_PNG::Load(const std::string& _sName)
{
    FILE* file = fopen(_sName.c_str(), "rb");

    unsigned char** RowPointers = 0;

    m_pSourceData.reset(new SDescription());

	png_byte buffer[8];

    // Read the first few bytes of the PNG file
    if (fread(buffer, 1, 8, file) != 8)
    {
        LogMessage(LOG_ERR, "LOAD PNG: can't read file " << _sName);
        return;
    }

    // Check if it really is a PNG file
	if( png_sig_cmp(buffer, 0, 8) )
    {
        LogMessage(LOG_ERR, "LOAD PNG: not really a png " << _sName);
        return;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                                 NULL, (png_error_ptr)png_cpexcept_error, NULL);
	if (!png_ptr)
	{
		LogMessage(LOG_ERR, "LOAD PNG: Internal PNG create read struct failure " << _sName);
		return;
	}

    // Allocate the png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		LogMessage(LOG_ERR, "LOAD PNG: Internal PNG create info struct failure " << _sName);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return;
	}

    // for proper error handling
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		if (RowPointers)
			delete [] RowPointers;
		return;
	}

    // changed by zola so we don't need to have public FILE pointers
	png_set_read_fn(png_ptr, file, user_read_data_fcn);

	png_set_sig_bytes(png_ptr, 8); // Tell png that we read the signature

	png_read_info(png_ptr, info_ptr); // Read the info section of the png file

    unsigned int Width;
	unsigned int Height;
	int BitDepth;
	int ColorType;
	{
		// Use temporary variables to avoid passing casted pointers
		png_uint_32 w,h;
		// Extract info
		png_get_IHDR(png_ptr, info_ptr,
			&w, &h,
			&BitDepth, &ColorType, NULL, NULL, NULL);
		Width=w;
		Height=h;
	}

    // Convert palette color to true color
	if (ColorType==PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);

    // Convert low bit colors to 8 bit colors
	if (BitDepth < 8)
	{
		if (ColorType==PNG_COLOR_TYPE_GRAY || ColorType==PNG_COLOR_TYPE_GRAY_ALPHA)
#if (PNG_LIBPNG_VER_MAJOR > 1) || (PNG_LIBPNG_VER_MINOR > 3)
			png_set_expand_gray_1_2_4_to_8(png_ptr);
#else
			png_set_gray_1_2_4_to_8(png_ptr);
#endif
		else
			png_set_packing(png_ptr);
	}

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	// Convert high bit colors to 8 bit colors
	if (BitDepth == 16)
		png_set_strip_16(png_ptr);

	// Convert gray color to true color
	if (ColorType==PNG_COLOR_TYPE_GRAY || ColorType==PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	int intent;
	const double screen_gamma = 2.2;

	if (png_get_sRGB(png_ptr, info_ptr, &intent))
		png_set_gamma(png_ptr, screen_gamma, 0.45455);
	else
	{
		double image_gamma;
		if (png_get_gAMA(png_ptr, info_ptr, &image_gamma))
			png_set_gamma(png_ptr, screen_gamma, image_gamma);
		else
			png_set_gamma(png_ptr, screen_gamma, 0.45455);
	}


    // Update the changes in between, as we need to get the new color type
	// for proper processing of the RGBA type
	png_read_update_info(png_ptr, info_ptr);
	{
		// Use temporary variables to avoid passing casted pointers
		png_uint_32 w,h;
		// Extract info
		png_get_IHDR(png_ptr, info_ptr,
			&w, &h,
			&BitDepth, &ColorType, NULL, NULL, NULL);
		Width=w;
		Height=h;
	}

	// Convert RGBA to BGRA
	if (ColorType==PNG_COLOR_TYPE_RGB_ALPHA)
	{
#ifdef __BIG_ENDIAN__
		png_set_swap_alpha(png_ptr);
#else
		png_set_bgr(png_ptr);
#endif
	}

    // Create the image structure to be filled by png data
    
	if (ColorType==PNG_COLOR_TYPE_RGB_ALPHA)
    {
        m_pSourceData->m_glFormat = GL_RGBA; //GL_ABGR
        m_pSourceData->m_uiBPP = 32;
        m_pSourceData->m_vSize = glm::vec2(Width, Height);
        m_pSourceData->m_glType = GL_UNSIGNED_BYTE;
    }
	else
    {
        //image = new CImage(ECF_R8G8B8, core::dimension2d<u32>(Width, Height));
    }
}

void CParser_PNG::Commit(void)
{
    
}

CParser_PNG::CParser_PNG(): m_pSourceData(nullptr) { }

CParser_PNG::CParser_PNG(const CParser_PNG& orig) { }

CParser_PNG::~CParser_PNG()
{
}

