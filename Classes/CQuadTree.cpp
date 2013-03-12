//
//  CQuadTree.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/3/13.
//
//

#include "CQuadTree.h"


CQuadTree::CQuadTree(void)
{
    m_parent = nullptr;
    m_childs = nullptr;
    m_indexes = nullptr;
    m_numIndexes = 0;
}

CQuadTree::~CQuadTree(void)
{

}

bool CQuadTree::IsPointInBoundBox(glm::vec3 _point, glm::vec3 _minBound, glm::vec3 _maxBound)
{
    if(_point.x >= _minBound.x &&
       _point.x <= _maxBound.x &&
       _point.y >= _minBound.y &&
       _point.y <= _maxBound.y &&
       _point.z >= _minBound.z &&
       _point.z <= _maxBound.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CQuadTree::BuildRoot(CVertexBuffer *_vertexBuffer, CIndexBuffer *_indexBuffer, glm::vec3 _maxBound, glm::vec3 _minBound, f32 _depth, ui32 _size)
{
    m_indexBuffer = _indexBuffer;
    m_parent = nullptr;
    m_maxBound = _maxBound;
    m_minBound = _minBound;
    m_numIndexes = _indexBuffer->Get_NumIndexes();
    m_indexes = static_cast<ui16*>(malloc(m_numIndexes * sizeof(ui16)));
    m_indexesIds = static_cast<ui16*>(malloc(m_numIndexes * sizeof(ui16)));
    ui16* indexData = _indexBuffer->Lock();
    memcpy(m_indexes , indexData, m_numIndexes * sizeof(ui16));
    memset(m_indexesIds, 0x0, m_numIndexes * sizeof(ui16));
    m_vertexes = _vertexBuffer->Lock();
    BuildQuadTreeNode(_size, _depth, this);
}

void CQuadTree::BuildQuadTreeNode(i32 _size, i32 _depth, CQuadTree* _root)
{
    if(_size <= _depth)
    {
        return;
    }

    _root->m_childs = new CQuadTree*[k_MAX_QUAD_TREE_CHILDS];

    _root->m_childs[0] = new CQuadTree();
    _root->m_childs[0]->m_parent = _root;
    _root->m_childs[0]->m_minBound = glm::vec3(_root->m_minBound.x, _root->m_minBound.y, _root->m_minBound.z );
    _root->m_childs[0]->m_maxBound = glm::vec3(_root->m_minBound.x + (_root->m_maxBound.x - _root->m_minBound.x) / 2.0f, _root->m_maxBound.y, _root->m_minBound.z + (_root->m_maxBound.z - _root->m_minBound.z) / 2.0f);
    _root->m_childs[0]->m_vertexes = m_vertexes;
    CreateIndexBufferForQuadTreeNode(_root->m_childs[0]);

    _root->m_childs[1] = new CQuadTree();
    _root->m_childs[1]->m_parent = _root;
    _root->m_childs[1]->m_minBound = glm::vec3(_root->m_minBound.x, _root->m_minBound.y, _root->m_minBound.z + (_root->m_maxBound.z - _root->m_minBound.z) / 2.0f);
    _root->m_childs[1]->m_maxBound = glm::vec3(_root->m_minBound.x + (_root->m_maxBound.x - _root->m_minBound.x) / 2.0f, _root->m_maxBound.y, _root->m_maxBound.z);
    _root->m_childs[1]->m_vertexes = m_vertexes;
    CreateIndexBufferForQuadTreeNode(_root->m_childs[1]);

    _root->m_childs[2] = new CQuadTree();
    _root->m_childs[2]->m_parent = _root;
    _root->m_childs[2]->m_minBound = glm::vec3(_root->m_minBound.x + (_root->m_maxBound.x - _root->m_minBound.x) / 2.0f, _root->m_minBound.y, _root->m_minBound.z + (_root->m_maxBound.z - _root->m_minBound.z) / 2.0f);
    _root->m_childs[2]->m_maxBound = glm::vec3(_root->m_maxBound.x, _root->m_maxBound.y, _root->m_maxBound.z);
    _root->m_childs[2]->m_vertexes = m_vertexes;
    CreateIndexBufferForQuadTreeNode(_root->m_childs[2]);

    _root->m_childs[3] = new CQuadTree();
    _root->m_childs[3]->m_parent = _root;
    _root->m_childs[3]->m_minBound = glm::vec3(_root->m_minBound.x + (_root->m_maxBound.x - _root->m_minBound.x) / 2.0f, _root->m_minBound.y, _root->m_minBound.z);
    _root->m_childs[3]->m_maxBound = glm::vec3(_root->m_maxBound.x, _root->m_maxBound.y, _root->m_minBound.z + (_root->m_maxBound.z - _root->m_minBound.z) / 2.0f);
    _root->m_childs[3]->m_vertexes = m_vertexes;
    CreateIndexBufferForQuadTreeNode(_root->m_childs[3]);

    BuildQuadTreeNode(_size / 2, _depth, _root->m_childs[0]);
    BuildQuadTreeNode(_size / 2, _depth, _root->m_childs[1]);
    BuildQuadTreeNode(_size / 2, _depth, _root->m_childs[2]);
    BuildQuadTreeNode(_size / 2, _depth, _root->m_childs[3]);
}

void CQuadTree::CreateIndexBufferForQuadTreeNode(CQuadTree *_node)
{
    ui32 parentNumIndexes = _node->m_parent->m_numIndexes;
    _node->m_indexes = static_cast<ui16*>(malloc(sizeof(ui16)));
    f32 maxY = -4096.0f;
    f32 minY =  4096.0f;

    ui32 quadTreeNodeId = 0;
    CQuadTree* parentNode = _node->m_parent;
    while (parentNode != nullptr)
    {
        quadTreeNodeId++;
        parentNode = parentNode->m_parent;
    }

    for(ui32 i = 0; i < parentNumIndexes; i += 3)
    {
        if(IsPointInBoundBox(glm::vec3(m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.x, m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.y, m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.z) , _node->m_minBound, _node->m_maxBound) ||
           IsPointInBoundBox(glm::vec3(m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.x, m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.y, m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.z), _node->m_minBound, _node->m_maxBound) ||
           IsPointInBoundBox(glm::vec3(m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.x, m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.y, m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.z), _node->m_minBound, _node->m_maxBound))
        {

            if(_node->m_parent->m_indexesIds[i + 0] == quadTreeNodeId ||
               _node->m_parent->m_indexesIds[i + 1] == quadTreeNodeId ||
               _node->m_parent->m_indexesIds[i + 2] == quadTreeNodeId)
            {
                continue;
            }

            _node->m_numIndexes += 3;
            _node->m_indexes = static_cast<ui16*>(realloc(_node->m_indexes, sizeof(ui16) * _node->m_numIndexes));

            _node->m_indexes[_node->m_numIndexes - 3] = _node->m_parent->m_indexes[i + 0];
            _node->m_indexes[_node->m_numIndexes - 2] = _node->m_parent->m_indexes[i + 1];
            _node->m_indexes[_node->m_numIndexes - 1] = _node->m_parent->m_indexes[i + 2];

            _node->m_parent->m_indexesIds[i + 0] = quadTreeNodeId;
            _node->m_parent->m_indexesIds[i + 1] = quadTreeNodeId;
            _node->m_parent->m_indexesIds[i + 2] = quadTreeNodeId;

            if(m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.y > maxY)
            {
                maxY = m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.y;
            }

            if(m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.y > maxY)
            {
                maxY = m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.y;
            }

            if(m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.y > maxY)
            {
                maxY = m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.y;
            }

            if(m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.y < minY)
            {
                minY = m_vertexes[_node->m_parent->m_indexes[i + 0]].m_position.y;
            }

            if(m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.y < minY)
            {
                minY = m_vertexes[_node->m_parent->m_indexes[i + 1]].m_position.y;
            }

            if(m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.y < minY)
            {
                minY = m_vertexes[_node->m_parent->m_indexes[i + 2]].m_position.y;
            }
        }
    }
    _node->m_indexesIds = static_cast<ui16*>(malloc(_node->m_numIndexes * sizeof(ui16)));
    memset(_node->m_indexesIds, 0x0, _node->m_numIndexes * sizeof(ui16));
    _node->m_maxBound.y = maxY;
    _node->m_minBound.y = minY;
}

void CQuadTree::RebuildQuadTreeNode(CFrustum *_frustum, CQuadTree *_root, ui16* _indexes, ui32 &_numIndexes)
{
    if(_root->m_childs == nullptr)
    {
        return;
    }

    for(ui32 i = 0; i < k_MAX_QUAD_TREE_CHILDS; i++)
    {
        i32 result =  _frustum->IsBoundBoxInFrustum(_root->m_childs[i]->m_maxBound, _root->m_childs[i]->m_minBound);
        if(result == E_FRUSTUM_BOUND_RESULT_INSIDE)
        {
            memcpy(&_indexes[_numIndexes], _root->m_childs[i]->m_indexes, sizeof(ui16) * _root->m_childs[i]->m_numIndexes);
            _numIndexes += _root->m_childs[i]->m_numIndexes;
        }
        else if(result == E_FRUSTUM_BOUND_RESULT_INTERSECT)
        {
            if(_root->m_childs[i]->m_childs == nullptr)
            {
                memcpy(&_indexes[_numIndexes], _root->m_childs[i]->m_indexes, sizeof(ui16) * _root->m_childs[i]->m_numIndexes);
                _numIndexes += _root->m_childs[i]->m_numIndexes;
            }
            else
            {
                RebuildQuadTreeNode(_frustum, _root->m_childs[i], _indexes, _numIndexes);
            }
        }
    }
}

void CQuadTree::OnUpdate(CFrustum *_frustum)
{
    ui16* indexes = m_indexBuffer->Lock();
    ui32 numIndexes = 0;
    RebuildQuadTreeNode(_frustum, this, indexes, numIndexes);

    m_indexBuffer->Set_NumIndexes(numIndexes);
    m_indexBuffer->Unlock();
}
