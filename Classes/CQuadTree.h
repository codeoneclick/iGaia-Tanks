//
//  CQuadTree.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#ifndef CQuadTree_h
#define CQuadTree_h

#define k_MAX_QUAD_TREE_CHILDS 4

#include "HCommon.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CFrustum.h"

class CQuadTree
{
private:
    
    CQuadTree* m_parent;
    CQuadTree** m_childs;

    glm::vec3 m_maxBound;
    glm::vec3 m_minBound;

    ui16* m_indexes;
    ui16* m_indexesIds;
    ui32 m_numIndexes;

    SVertex* m_vertexes;
    CIndexBuffer* m_indexBuffer;

    void BuildQuadTreeNode(i32 _size, i32 _depth, CQuadTree* _root);
    void CreateIndexBufferForQuadTreeNode(CQuadTree *_node);
    bool IsPointInBoundBox(glm::vec3 _point, glm::vec3 _minBound, glm::vec3 _maxBound);
    void RebuildQuadTreeNode(CFrustum* _frustum, CQuadTree* _root, ui16* _indexes, ui32& _numIndexes);

protected:

public:
    
    CQuadTree(void);
    ~CQuadTree(void);

    void BuildRoot(CVertexBuffer* _vertexBuffer, CIndexBuffer* _indexBuffer, glm::vec3 _maxBound, glm::vec3 _minBound, f32 _depth, ui32 _size);
    void OnUpdate(CFrustum* _frustum);
};


#endif
