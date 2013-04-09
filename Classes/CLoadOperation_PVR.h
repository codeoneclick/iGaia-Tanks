//
//  CLoadOperation_PVR.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#ifndef CLoadOperation_PVR_h
#define CLoadOperation_PVR_h

#include "ILoadOperation.h"

class CLoadOperation_PVR : public ILoadOperation_INTERFACE
{
private:

protected:

    GLenum m_format;
    i32 m_bpp;
	ui32 m_mipCount;
    bool m_compressed;

	ui32 m_width;
    ui32 m_height;

	std::unique_ptr<ui8> m_filedata;
	ui8* m_texturedata;

public:
    
    CLoadOperation_PVR(void);
    ~CLoadOperation_PVR(void);

    void Load(const std::string& _filename);
    IResource_INTERFACE* Link(void);
};

#endif 