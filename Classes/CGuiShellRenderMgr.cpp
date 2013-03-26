

#include <CGuiShellRenderMgr.h>
#include <Rocket/Core.h>
#include "CCommon.h"
#include "CMesh.h"

CGuiShellRenderMgr_INTERFACE::CGuiShellRenderMgr_INTERFACE(void)
{
}

void CGuiShellRenderMgr_INTERFACE::RenderGeometry(Rocket::Core::Vertex* vertices, int ROCKET_UNUSED(num_vertices), int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{

}
	
Rocket::Core::CompiledGeometryHandle CGuiShellRenderMgr_INTERFACE::CompileGeometry(Rocket::Core::Vertex* _vertexData, i32 _numVertexes, i32* _indexData, i32 _numIndexes, const Rocket::Core::TextureHandle _textureHandle)
{
    CVertexBuffer* vertexBuffer = new CVertexBuffer(_numVertexes, GL_STATIC_DRAW);
    SVertex* vertexData = vertexBuffer->Lock();

    for(ui32 i = 0; i < _numVertexes; ++i)
    {
        vertexData[i].m_position = glm::vec3(_vertexData[i].position.x, _vertexData[i].position.y, 0.0f);
        vertexData[i].m_texcoord = glm::vec2(_vertexData[i].tex_coord.x, _vertexData[i].tex_coord.y);
        vertexData[i].m_color = glm::u8vec4(_vertexData[i].colour.red, _vertexData[i].colour.green, _vertexData[i].colour.blue, _vertexData[i].colour.alpha);
    }

    vertexBuffer->Unlock();

    CIndexBuffer* indexBuffer = new CIndexBuffer(_numIndexes, GL_STATIC_DRAW);
    ui16* indexData = indexBuffer->Lock();

    for(ui32 i = 0; i < _numIndexes; ++i)
    {
        indexData[i] = _indexData[i];
    }

    indexBuffer->Unlock();
    CMesh* mesh = new CMesh(vertexBuffer, indexBuffer);

	return (Rocket::Core::CompiledGeometryHandle) mesh;
}
	
void CGuiShellRenderMgr_INTERFACE::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry), const Rocket::Core::Vector2f& ROCKET_UNUSED(translation))
{
    
}
	
void CGuiShellRenderMgr_INTERFACE::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry))
{
    
}
	
void CGuiShellRenderMgr_INTERFACE::EnableScissorRegion(bool enable)
{
	if (enable)
    {
		glEnable(GL_SCISSOR_TEST);
    }
	else
    {
		glDisable(GL_SCISSOR_TEST);
    }
}

void CGuiShellRenderMgr_INTERFACE::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, Get_ScreenHeight() - (y + height), width, height);
}

bool CGuiShellRenderMgr_INTERFACE::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
    return true;
}

bool CGuiShellRenderMgr_INTERFACE::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
    return true;
}
	
void CGuiShellRenderMgr_INTERFACE::ReleaseTexture(Rocket::Core::TextureHandle _textureHandle)
{
	glDeleteTextures(1, (GLuint*)&_textureHandle);
}

