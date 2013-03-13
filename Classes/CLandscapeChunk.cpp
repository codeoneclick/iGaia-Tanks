//
//  CLandscapeChunk.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/14/13.
//
//

#include "CLandscapeChunk.h"

CLandscapeChunk::CLandscapeChunk(void)
{
    
}

CLandscapeChunk::~CLandscapeChunk(void)
{
    
}

void CLandscapeChunk::Load(CMesh *_mesh, CMaterial **_materials, ui32 _width, ui32 _height)
{
    assert(_mesh != nullptr);
    assert(m_materials != nullptr);

    m_mesh = _mesh;
    
    for(ui32 i = 0; i < E_RENDER_MODE_WORLD_SPACE_MAX; ++i)
    {
        m_materials[i] = _materials[i];
    }
    
    m_quadTree = new CQuadTree();
    m_quadTree->BuildRoot(m_mesh->Get_VertexBuffer(), m_mesh->Get_IndexBuffer(), m_mesh->Get_MaxBound(), m_mesh->Get_MinBound(), 8, _width);    
}

void CLandscapeChunk::OnResourceDidLoad(IResource_INTERFACE* _resource)
{
    CGameObject3d::OnResourceDidLoad(_resource);
}

void CLandscapeChunk::OnUpdate(f32 _deltatime)
{
    assert(m_quadTree != nullptr);
    assert(m_camera != nullptr);
    assert(m_camera->Get_Frustum() != nullptr);
    //m_quadTree->OnUpdate(m_camera->Get_Frustum());
    CGameObject3d::OnUpdate(_deltatime);
}

ui32 CLandscapeChunk::OnDrawIndex(void)
{
    return 1;
}

void CLandscapeChunk::OnBind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnBind(_mode);
}

void CLandscapeChunk::OnDraw(E_RENDER_MODE_WORLD_SPACE _mode)
{
    assert(m_materials[_mode] != nullptr);
    assert(m_camera != nullptr);
    assert(m_light != nullptr);
    
    switch (_mode)
    {
        case E_RENDER_MODE_WORLD_SPACE_COMMON:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);
            
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFLECTION:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewReflectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);
            
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector4(m_materials[_mode]->Get_Clipping(), E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        case E_RENDER_MODE_WORLD_SPACE_REFRACTION:
        {
            assert(m_materials[_mode]->Get_Shader() != nullptr);
            
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_matrixWorld, E_SHADER_ATTRIBUTE_MATRIX_WORLD);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ProjectionMatrix(), E_SHADER_ATTRIBUTE_MATRIX_PROJECTION);
            m_materials[_mode]->Get_Shader()->Set_Matrix4x4(m_camera->Get_ViewMatrix(), E_SHADER_ATTRIBUTE_MATRIX_VIEW);
            
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_camera->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector3(m_light->Get_Position(), E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            m_materials[_mode]->Get_Shader()->Set_Vector4(glm::vec4(m_materials[_mode]->Get_Clipping().x, m_materials[_mode]->Get_Clipping().y * -1.0f, m_materials[_mode]->Get_Clipping().z, m_materials[_mode]->Get_Clipping().w), E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE);
        }
            break;
        default:
            break;
    }
    
    CGameObject3d::OnDraw(_mode);
}

void CLandscapeChunk::OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode)
{
    CGameObject3d::OnUnbind(_mode);
}
