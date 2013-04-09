

#include "CUIShellRenderMgr.h"
#include "CCommon.h"
#include "CMesh.h"

CUIShellRenderMgr_INTERFACE::CUIShellRenderMgr_INTERFACE(void)
{
	m_guiMaterial = nullptr;
	m_shaderComposite = nullptr;
	m_resourceMgrsFacade = nullptr;
}

void CUIShellRenderMgr_INTERFACE::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
    assert(false);
}

CMaterial* CUIShellRenderMgr_INTERFACE::Get_Material(void)
{
	if(m_guiMaterial == nullptr)
	{
		assert(m_shaderComposite != nullptr);
		m_guiMaterial = new CMaterial(m_shaderComposite->Get_Shader(E_SHADER_GUI_PLANE));
		m_guiMaterial->Set_RenderState(E_RENDER_STATE_CULL_MODE, false);
		m_guiMaterial->Set_RenderState(E_RENDER_STATE_DEPTH_MASK, true);
		m_guiMaterial->Set_RenderState(E_RENDER_STATE_DEPTH_TEST, false);
		m_guiMaterial->Set_RenderState(E_RENDER_STATE_BLEND_MODE, true);

		m_guiMaterial->Set_CullFaceMode(GL_FRONT);
		m_guiMaterial->Set_BlendFunctionSource(GL_SRC_ALPHA);
		m_guiMaterial->Set_BlendFunctionDest(GL_ONE_MINUS_SRC_ALPHA);
	}
	return m_guiMaterial;
}

Rocket::Core::CompiledGeometryHandle CUIShellRenderMgr_INTERFACE::CompileGeometry(Rocket::Core::Vertex* _vertexData, i32 _numVertexes, i32* _indexData, i32 _numIndexes, const Rocket::Core::TextureHandle _texture)
{
	CTexture* texture = (CTexture*)_texture;
	assert(texture != nullptr);

    std::unique_ptr<CVertexBuffer> vertexBuffer = std::unique_ptr<CVertexBuffer>(new CVertexBuffer(_numVertexes, GL_STATIC_DRAW));
    SVertex* vertexData = vertexBuffer->Lock();

	f32 screenWidth = static_cast<f32>(Get_ScreenWidth());
	f32 screenHeight = static_cast<f32>(Get_ScreenHeight());

    for(ui32 i = 0; i < _numVertexes; ++i)
    {
        vertexData[i].m_position = glm::vec3(_vertexData[i].position.x / (screenWidth * 0.5f) - 1.0f, _vertexData[i].position.y / (screenHeight * 0.5f) - 1.0f, 0.0f);
        vertexData[i].m_position.y *= -1.0f;
        vertexData[i].m_texcoord = glm::vec2(_vertexData[i].tex_coord.x, _vertexData[i].tex_coord.y);
        vertexData[i].m_color = glm::u8vec4(_vertexData[i].colour.red, _vertexData[i].colour.green, _vertexData[i].colour.blue, _vertexData[i].colour.alpha);
    }

    vertexBuffer->Unlock();

    std::unique_ptr<CIndexBuffer> indexBuffer = std::unique_ptr<CIndexBuffer>(new CIndexBuffer(_numIndexes, GL_STATIC_DRAW));
    ui16* indexData = indexBuffer->Lock();

    for(ui32 i = 0; i < _numIndexes; ++i)
    {
        indexData[i] = _indexData[i];
    }

    indexBuffer->Unlock();
    CMesh* mesh = new CMesh();
    mesh->Link(std::move(vertexBuffer), std::move(indexBuffer));

	SUIElement* guiElement = new SUIElement(mesh, texture);

	return (Rocket::Core::CompiledGeometryHandle)guiElement;
}
	
void CUIShellRenderMgr_INTERFACE::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle _guiElement, const Rocket::Core::Vector2f& _translation)
{
	SUIElement* guiElement = (SUIElement*)_guiElement;
	assert(guiElement != nullptr);
	CMesh* mesh = guiElement->m_mesh;
	assert(mesh != nullptr);
	CTexture* texture = guiElement->m_texture;
	assert(texture != nullptr);
	CMaterial* material = Get_Material();
	assert(material != nullptr);

    f32 screenWidth = static_cast<f32>(Get_ScreenWidth());
	f32 screenHeight = static_cast<f32>(Get_ScreenHeight());

	material->Set_Texture(texture, E_TEXTURE_SLOT_01);
	material->Bind();
    material->Get_Shader()->Set_Vector2Custom(glm::vec2(_translation.x / (screenWidth * 0.5f), _translation.y / (screenHeight * -0.5f)), "EXT_VECTOR_Translation");
	mesh->Bind(material->Get_Shader()->Get_VertexSlots());
	mesh->Draw();
	mesh->Unbind(material->Get_Shader()->Get_VertexSlots());
    material->Unbind();
}

void CUIShellRenderMgr_INTERFACE::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle _geometry)
{
    
}
	
void CUIShellRenderMgr_INTERFACE::EnableScissorRegion(bool enable)
{

}

void CUIShellRenderMgr_INTERFACE::SetScissorRegion(int x, int y, int width, int height)
{

}

bool CUIShellRenderMgr_INTERFACE::LoadTexture(Rocket::Core::TextureHandle& _texture, Rocket::Core::Vector2i& _textureDimensions, const Rocket::Core::String& _filename)
{
	std::string filename = _filename.CString();
	filename = filename.substr(filename.find_last_of("\\/") + 1);
	assert(m_resourceMgrsFacade != nullptr);
	CTexture* texture = m_resourceMgrsFacade->LoadTexture(filename).get();
	assert(texture != nullptr);
	_texture = (Rocket::Core::TextureHandle)texture;
	_textureDimensions.x = texture->Get_Width();
	_textureDimensions.y = texture->Get_Height();
    return true;
}

bool CUIShellRenderMgr_INTERFACE::GenerateTexture(Rocket::Core::TextureHandle& _texture, const Rocket::Core::byte* _data, const Rocket::Core::Vector2i& _textureDimensions)
{
	ui32 textureHandle;
	glGenTextures(1, &textureHandle);
	assert(textureHandle != 0);

	glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _textureDimensions.x, _textureDimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	CTexture* texture = new CTexture();
    texture->Link(textureHandle, _textureDimensions.x, _textureDimensions.y);
	_texture = (Rocket::Core::TextureHandle)texture;

    return true;
}
	
void CUIShellRenderMgr_INTERFACE::ReleaseTexture(Rocket::Core::TextureHandle _textureHandle)
{
	
}

