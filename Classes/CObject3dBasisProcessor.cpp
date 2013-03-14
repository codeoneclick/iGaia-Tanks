//
//  CObject3dBasisProcessor.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/14/13.
//
//

#include "CObject3dBasisProcessor.h"

void CObject3dBasisProcessor::ProcessNormals(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer)
{
    SVertex* vertexData = _vertexBuffer->Lock();
    ui16* indexData = _indexBuffer->Lock();
    ui32 numIndexes = _indexBuffer->Get_NumIndexes();
    for(ui32 index = 0; index < numIndexes; index += 3)
    {
        glm::vec3 point_01 = vertexData[indexData[index + 0]].m_position;
        glm::vec3 point_02 = vertexData[indexData[index + 1]].m_position;
        glm::vec3 point_03 = vertexData[indexData[index + 2]].m_position;

        glm::vec3 edge_01 = point_02 - point_01;
        glm::vec3 edge_02 = point_03 - point_01;

        glm::vec3 normal = glm::cross(edge_01, edge_02);
        normal = glm::normalize(normal);
        glm::u8vec4 byteNormal = CVertexBuffer::CompressVec3(normal);
        vertexData[indexData[index + 0]].m_normal = byteNormal;
        vertexData[indexData[index + 1]].m_normal = byteNormal;
        vertexData[indexData[index + 2]].m_normal = byteNormal;
    }
    _vertexBuffer->Unlock();
    _indexBuffer->Unlock();
}

void CObject3dBasisProcessor::ProcessTangentsAndBinormals(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer)
{
	register ui32 i, j;
    std::vector<glm::vec3> tangents, binormals;

	ui32 numIndexes = _indexBuffer->Get_NumIndexes();

    SVertex* vertexData = _vertexBuffer->Lock();
    ui16* indexData = _indexBuffer->Lock();

    for (i = 0; i < numIndexes; i += 3)
	{
        glm::vec3 v1 = vertexData[indexData[i + 0]].m_position;
		glm::vec3 v2 = vertexData[indexData[i + 1]].m_position;
		glm::vec3 v3 = vertexData[indexData[i + 2]].m_position;

		f32 s1 = vertexData[indexData[i + 0]].m_texcoord.x;
		f32 t1 = vertexData[indexData[i + 0]].m_texcoord.y;
		f32 s2 = vertexData[indexData[i + 1]].m_texcoord.x;
		f32 t2 = vertexData[indexData[i + 1]].m_texcoord.y;
		f32 s3 = vertexData[indexData[i + 2]].m_texcoord.x;
		f32 t3 = vertexData[indexData[i + 2]].m_texcoord.y;

		glm::vec3  t, b;
		ProcessTriangleBasis(v1, v2, v3, s1, t1, s2, t2, s3, t3, t, b);
		tangents.push_back(t);
		binormals.push_back(b);
	}

    ui32 numVertexes = _vertexBuffer->Get_NumVertexes();
	for (i = 0; i < numVertexes; i++)
	{
        std::vector<glm::vec3> lrt, lrb;
		for (j = 0; j < numVertexes; j += 3)
		{
			if ((indexData[j + 0]) == i || (indexData[j + 1]) == i || (indexData[j + 2]) == i)
			{
				lrt.push_back(tangents[i]);
				lrb.push_back(binormals[i]);
			}
		}

        glm::vec3 tangent(0.0f, 0.0f, 0.0f);
        glm::vec3 binormal(0.0f, 0.0f, 0.0f);
		for (j = 0; j < lrt.size(); j++)
		{
			tangent += lrt[j];
			binormal += lrb[j];
		}
		tangent /= float(lrt.size());
		binormal /= float(lrb.size());

        glm::vec3 normal = CVertexBuffer::UncompressU8Vec4(vertexData[i].m_normal);
		tangent = Ortogonalize(normal, tangent);
		binormal = Ortogonalize(normal, binormal);

        vertexData[i].m_tangent = CVertexBuffer::CompressVec3(tangent);
	}
}


void CObject3dBasisProcessor::ProcessTriangleBasis(const glm::vec3& E, const glm::vec3& F, const glm::vec3& G, f32 sE, f32 tE, f32 sF, f32 tF, f32 sG, f32 tG, glm::vec3& tangentX, glm::vec3& tangentY)
{
    glm::vec3 P = F - E;
    glm::vec3 Q = G - E;
	f32 s1 = sF - sE;
	f32 t1 = tF - tE;
	f32 s2 = sG - sE;
	f32 t2 = tG - tE;
	f32 pqMatrix[2][3];
	pqMatrix[0][0] = P[0];
	pqMatrix[0][1] = P[1];
	pqMatrix[0][2] = P[2];
	pqMatrix[1][0] = Q[0];
	pqMatrix[1][1] = Q[1];
	pqMatrix[1][2] = Q[2];
	f32 temp = 1.0f / ( s1 * t2 - s2 * t1);
	f32 stMatrix[2][2];
	stMatrix[0][0] =  t2 * temp;
	stMatrix[0][1] = -t1 * temp;
	stMatrix[1][0] = -s2 * temp;
	stMatrix[1][1] =  s1 * temp;
	f32 tbMatrix[2][3];
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

glm::vec3 CObject3dBasisProcessor::ClosestPointOnLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p)
{
    glm::vec3 c = p - a;
    glm::vec3 V = b - a;
	f32 d = V.length();
	V = glm::normalize(V);
	f32 t = glm::dot( V, c );

	if ( t < 0.0f )
		return a;
	if ( t > d )
		return b;

	V *= t;
	return ( a + V );
}

glm::vec3 CObject3dBasisProcessor::Ortogonalize(const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 v2ProjV1 = ClosestPointOnLine( v1, -v1, v2 );
	glm::vec3 res = v2 - v2ProjV1;
	res = glm::normalize(res);
	return res;
}
