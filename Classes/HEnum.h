//
//  HEnum.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#ifndef HEnum_h
#define HEnum_h

enum E_RESOURCE_MGR
{
    E_RESOURCE_MGR_TEXTURE = 0,
    E_RESOURCE_MGR_MESH
};

enum E_RESOURCE_LOAD_THREAD
{
    E_RESOURCE_LOAD_THREAD_SYNC = 0,
    E_RESOURCE_LOAD_THREAD_ASYNC
};

enum E_RESOURCE_TYPE
{
    E_RESOURCE_TYPE_UNKNOWN = 0,
    E_RESOURCE_TYPE_TEXTURE,
    E_RESOURCE_TYPE_MESH,
    E_RESOURCE_TYPE_SHADER,
    E_RESOURCE_TYPE_XML
};

enum E_PARSER_STATUS
{
    E_PARSER_STATUS_UNKNOWN = 0,
    E_PARSER_STATUS_PROCESS,
    E_PARSER_STATUS_ERROR,
    E_PARSER_STATUS_DONE,
};

enum E_SHADER_VERTEX_SLOT
{
    E_SHADER_VERTEX_SLOT_POSITION = 0,
    E_SHADER_VERTEX_SLOT_TEXCOORD,
    E_SHADER_VERTEX_SLOT_NORMAL,
    E_SHADER_VERTEX_SLOT_TANGENT,
    E_SHADER_VERTEX_SLOT_COLOR,
    E_SHADER_VERTEX_SLOT_MAX
};

enum E_SHADER_ATTRIBUTE
{
    E_SHADER_ATTRIBUTE_MATRIX_WORLD = 0,
    E_SHADER_ATTRIBUTE_MATRIX_VIEW,
    E_SHADER_ATTRIBUTE_MATRIX_PROJECTION,
    E_SHADER_ATTRIBUTE_MATRIX_WVP,
    E_SHADER_ATTRIBUTE_VECTOR_CAMERA_POSITION,
    E_SHADER_ATTRIBUTE_VECTOR_LIGHT_POSITION,
    E_SHADER_ATTRIBUTE_VECTOR_CLIP_PLANE,
    E_SHADER_ATTRIBUTE_FLOAT_TIMER,
    E_SHADER_ATTRIBUTE_VECTOR_TEXTURE_DISPLACE,
    E_SHADER_ATTRIBUTE_MAX
};

enum E_TEXTURE_SLOT
{
    E_TEXTURE_SLOT_01 = 0,
    E_TEXTURE_SLOT_02,
    E_TEXTURE_SLOT_03,
    E_TEXTURE_SLOT_04,
    E_TEXTURE_SLOT_05,
    E_TEXTURE_SLOT_06,
    E_TEXTURE_SLOT_07,
    E_TEXTURE_SLOT_08,
    E_TEXTURE_SLOT_MAX
};

enum E_RENDER_MODE_WORLD_SPACE
{
    E_RENDER_MODE_WORLD_SPACE_COMMON = 0,
    E_RENDER_MODE_WORLD_SPACE_REFLECTION,
    E_RENDER_MODE_WORLD_SPACE_REFRACTION,
    E_RENDER_MODE_WORLD_SPACE_MAX 
};

enum E_RENDER_MODE_SCREEN_SPACE
{
    E_RENDER_MODE_SCREEN_SPACE_COMMON = 0,
    E_RENDER_MODE_SCREEN_SPACE_BLOOM_EXTRACT,
    E_RENDER_MODE_SCREEN_SPACE_BLOOM_COMBINE,
    E_RENDER_MODE_SCREEN_SPACE_BLUR,
    E_RENDER_MODE_SCREEN_SPACE_EDGE_DETECT,
    E_RENDER_MODE_SCREEN_SPACE_MAX
};

enum E_RENDER_STATE
{
    E_RENDER_STATE_CULL_MODE = 0,
    E_RENDER_STATE_BLEND_MODE,
    E_RENDER_STATE_DEPTH_TEST,
    E_RENDER_STATE_DEPTH_MASK,
    E_RENDER_STATE_MAX
};

enum E_SHADER
{
    E_SHADER_LANDSCAPE = 0,
    E_SHADER_LANDSCAPE_ND,
    E_SHADER_MODEL,
    E_SHADER_MODEL_ND,
    E_SHADER_GRASS,
    E_SHADER_GRASS_ND,
    E_SHADER_OCEAN,
    E_SHADER_DECAL,
    E_SHADER_PARTICLE,
    E_SHADER_PARTICLE_ND,
    E_SHADER_SKYBOX,
    E_SHADER_LANDSCAPE_EDGES,
    E_SHADER_SCREEN_PLANE,
    E_SHADER_SCREEN_PLANE_BLOOM_EXTRACT,
    E_SHADER_SCREEN_PLANE_BLOOM_COMBINE,
    E_SHADER_SCREEN_PLANE_BLUR,
    E_SHADER_SCREEN_PLANE_EDGE_DETECT,
    E_SHADER_SCREEN_PLANE_LANDSCAPE_DETAIL,
    E_SHADER_MAX
};

enum E_FRUSTUM_BOUND_RESULT
{
    E_FRUSTUM_BOUND_RESULT_OUTSIDE = 0,
    E_FRUSTUM_BOUND_RESULT_INTERSECT,
    E_FRUSTUM_BOUND_RESULT_INSIDE
};

enum E_FRUSTUM_PLANE
{
    E_FRUSTUM_PLANE_TOP = 0,
    E_FRUSTUM_PLANE_BOTTOM,
    E_FRUSTUM_PLANE_LEFT,
    E_FRUSTUM_PLANE_RIGHT,
    E_FRUSTUM_PLANE_NEAR,
    E_FRUSTUM_PLANE_FAR,
    E_FRUSTUM_PLANE_MAX
};


#endif
