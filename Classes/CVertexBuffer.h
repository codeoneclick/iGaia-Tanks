//
//  CVertexBuffer.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/26/13.
//
//

#ifndef CVertexBuffer_h
#define CVertexBuffer_h

#include "HCommon.h"

#define K_NUM_REPLACEMENT_VERTEX_BUFFERS 3

struct SVertex
{
    glm::vec3 m_position;
    glm::vec2 m_texcoord;
    glm::u8vec4 m_normal;
    glm::u8vec4 m_tangent;
    glm::u8vec4 m_color;
};

class CVertexBuffer
{
private:

protected:

    ui32 m_numVertexes;
    i32 m_currentHandleIndex;
    ui32 m_handles[K_NUM_REPLACEMENT_VERTEX_BUFFERS];
    SVertex* m_data;
    GLenum m_mode;

public:

    CVertexBuffer(ui32 _numVertexes, GLenum _mode);
    ~CVertexBuffer(void);

    inline ui32 Get_NumVertexes(void)
    {
        assert(m_numVertexes != 0);
        return m_numVertexes;
    };

    static glm::u8vec4 CompressVec3(const glm::vec3& _uncompressed);
    static glm::vec3 UncompressU8Vec4(const glm::u8vec4& _compressed);

    inline SVertex* Lock(void)
    {
        assert(m_data != nullptr);
        return m_data;
    };
    
    void Unlock(void);

    void Bind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots);
    void Unbind(const std::map<E_SHADER_VERTEX_SLOT, i32>& _slots);
};

#endif 
