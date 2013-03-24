//
//  CLoadOperation_MDL.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "CLoadOperation_MDL.h"
#include "CCommon.h"
#include "CMesh.h"

CLoadOperation_MDL::CLoadOperation_MDL(void)
{
    m_status = E_PARSER_STATUS_UNKNOWN;
}

CLoadOperation_MDL::~CLoadOperation_MDL(void)
{

}

void CLoadOperation_MDL::Load(const std::string& _filename)
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
    stream.read((char*)&m_numVertexes, sizeof(ui32));
    stream.read((char*)&m_numIndexes, sizeof(ui32));

    m_vertexData = new SVertex[m_numVertexes];

    m_maxBound = glm::vec3( -4096.0f, -4096.0f, -4096.0f );
    m_minBound = glm::vec3(  4096.0f,  4096.0f,  4096.0f );

    for(ui32 i = 0; i < m_numVertexes; ++i)
    {
        glm::vec3 position;
        stream.read((char*)&position, sizeof(glm::vec3));
        glm::vec3 normal;
        stream.read((char*)&normal, sizeof(glm::vec3));
        glm::vec3 tangent;
        stream.read((char*)&tangent, sizeof(glm::vec3));
        glm::vec2 texcoord;
        stream.read((char*)&texcoord, sizeof(glm::vec2));

        m_vertexData[i].m_position = position;
        m_vertexData[i].m_texcoord = texcoord;
        m_vertexData[i].m_normal = CVertexBuffer::CompressVec3(normal);
        m_vertexData[i].m_tangent = CVertexBuffer::CompressVec3(tangent);

        if(m_vertexData[i].m_position.x > m_maxBound.x)
        {
            m_maxBound.x = m_vertexData[i].m_position.x;
        }
        if(m_vertexData[i].m_position.y > m_maxBound.y)
        {
            m_maxBound.y = m_vertexData[i].m_position.y;
        }
        if(m_vertexData[i].m_position.z > m_maxBound.z)
        {
            m_maxBound.z = m_vertexData[i].m_position.z;
        }
        if(m_vertexData[i].m_position.x < m_minBound.x)
        {
            m_minBound.x = m_vertexData[i].m_position.x;
        }
        if(m_vertexData[i].m_position.y < m_minBound.y)
        {
            m_minBound.y = m_vertexData[i].m_position.y;
        }
        if(m_vertexData[i].m_position.z < m_minBound.z)
        {
            m_minBound.z = m_vertexData[i].m_position.z;
        }
    }

    m_indexData = new ui16[m_numIndexes];

    for(ui32 i = 0; i < m_numIndexes; ++i)
    {
        stream.read((char*)&m_indexData[i], sizeof(ui16));
    }

    for(ui32 i = 0; i < m_numIndexes; i += 3)
    {
        ui16 index = m_indexData[i + 1];
        m_indexData[i + 1] = m_indexData[i + 2];
        m_indexData[i + 2] = index;
    }

    stream.close();
    m_status = E_PARSER_STATUS_DONE;
}

IResource_INTERFACE* CLoadOperation_MDL::Build(void)
{
    CVertexBuffer* vertexBuffer = new CVertexBuffer(m_numVertexes, GL_STATIC_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();
    memcpy(vertexData, m_vertexData , sizeof(SVertex) * m_numVertexes);
    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer(m_numIndexes, GL_STATIC_DRAW);
    ui16* indexData = indexBuffer->Lock();
    memcpy(indexData, m_indexData, sizeof(ui16) * m_numIndexes);
    indexBuffer->Unlock();

    CMesh* mesh = new CMesh(vertexBuffer, indexBuffer, m_maxBound, m_minBound);
    Register(mesh);
    return mesh;
}
