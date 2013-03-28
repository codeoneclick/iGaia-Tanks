
#ifndef CUIShellRenderMgr_h
#define CUIShellRenderMgr_h

#include "HCommon.h"
#include "CShaderComposite.h"
#include "CResourceMgrsFacade.h"
#include "CMaterial.h"

struct SUIElement
{
	SUIElement(CMesh* _mesh, CTexture* _texture)
	{
		m_mesh = _mesh;
		m_texture = _texture;
	};

	CMesh* m_mesh;
	CTexture* m_texture;
};

class CUIShellRenderMgr_INTERFACE : public Rocket::Core::RenderInterface
{
private:

protected:

	CShaderComposite* m_shaderComposite;
	CResourceMgrsFacade* m_resourceMgrsFacade;

	CMaterial* m_guiMaterial;
	CMaterial* Get_Material(void);

    void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
	Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
	void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
	void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
	void EnableScissorRegion(bool enable);
	void SetScissorRegion(int x, int y, int width, int height);
	bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
	bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
	void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
    
public:
    
	CUIShellRenderMgr_INTERFACE(void);
    ~CUIShellRenderMgr_INTERFACE(void) {};

	inline void Set_ShaderComposite(CShaderComposite* _shaderComposite)
    {
        m_shaderComposite = _shaderComposite;
    };

	inline void Set_ResourceMgrFacade(CResourceMgrsFacade* _resourceMgrsFacade)
	{
		m_resourceMgrsFacade = _resourceMgrsFacade;
	};
};

#endif
