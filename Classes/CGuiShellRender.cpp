

#include <CGuiShellRender.h>
#include <Rocket/Core.h>
#include "CCommon.h"

CGuiShellRender_INTERFACE::CGuiShellRender_INTERFACE(void)
{
}

void CGuiShellRender_INTERFACE::RenderGeometry(Rocket::Core::Vertex* vertices, int ROCKET_UNUSED(num_vertices), int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{

}
	
Rocket::Core::CompiledGeometryHandle CGuiShellRender_INTERFACE::CompileGeometry(Rocket::Core::Vertex* ROCKET_UNUSED(vertices), int ROCKET_UNUSED(num_vertices), int* ROCKET_UNUSED(indices), int ROCKET_UNUSED(num_indices), const Rocket::Core::TextureHandle ROCKET_UNUSED(texture))
{
	return (Rocket::Core::CompiledGeometryHandle) nullptr;
}
	
void CGuiShellRender_INTERFACE::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry), const Rocket::Core::Vector2f& ROCKET_UNUSED(translation))
{
    
}
	
void CGuiShellRender_INTERFACE::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry))
{
    
}
	
void CGuiShellRender_INTERFACE::EnableScissorRegion(bool enable)
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

void CGuiShellRender_INTERFACE::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, Get_ScreenHeight() - (y + height), width, height);
}

bool CGuiShellRender_INTERFACE::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
    return true;
}

bool CGuiShellRender_INTERFACE::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
    return true;
}
	
void CGuiShellRender_INTERFACE::ReleaseTexture(Rocket::Core::TextureHandle _textureHandle)
{
	glDeleteTextures(1, (GLuint*)&_textureHandle);
}

