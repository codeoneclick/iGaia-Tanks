//
//  CIndexBuffer.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#ifndef CIndexBuffer_h
#define CIndexBuffer_h

#include "HCommon.h"

#define K_NUM_REPLACEMENT_INDEX_BUFFERS 3

class CIndexBuffer
{
private:

protected:
    
    ui32 m_handles[K_NUM_REPLACEMENT_INDEX_BUFFERS];
    i32 m_currentHandleIndex;
	std::unique_ptr<ui16> m_data;
    GLenum m_mode;
    ui32 m_maxNumIndexes;
    ui32 m_numIndexes;
    
public:

    CIndexBuffer(ui32 _numIndexes, GLenum _mode);
    ~CIndexBuffer(void);

    inline ui32 Get_NumIndexes(void)
    {
        return m_numIndexes;
    };

    inline void Set_NumIndexes(ui32 _numIndexes)
    {
        m_numIndexes = _numIndexes;
    };

    inline ui16* Lock(void)
    {
        assert(m_data != nullptr);
		return m_data.get();
    };
    
    void Unlock(void);

    void Bind(void);
    void Unbind(void);

};

#endif 
