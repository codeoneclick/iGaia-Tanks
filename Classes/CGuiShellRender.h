
#ifndef CGuiShellRender_h
#define CGuiShellRender_h

#include <Rocket/Core/Platform.h>
#include "Rocket/Core/RenderInterface.h"
#include "HCommon.h"

class CGuiShellRender_INTERFACE : public Rocket::Core::RenderInterface
{
private:

protected:
    
public:
    
	CGuiShellRender_INTERFACE(void);
    ~CGuiShellRender_INTERFACE(void) {};

	void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
	Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
	void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
	void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
	void EnableScissorRegion(bool enable);
	void SetScissorRegion(int x, int y, int width, int height);
	bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
	bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
	void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
};

#endif
