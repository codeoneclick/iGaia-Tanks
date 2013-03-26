//
//  CRenderMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "CRenderMgr.h"
#include "CCommon.h"

CRenderMgr::CRenderMgr(const IGLContext_INTERFACE* _glContext)
{
    m_glContext = _glContext;

	Rocket::Core::SetRenderInterface(&m_openglRenderInterface);

	CGuiShellSystem_INTERFACE systemInterface;
	Rocket::Core::SetSystemInterface(&m_systemInterface);

    Rocket::Core::Initialise();
    m_guiContext = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(Get_ScreenWidth(), Get_ScreenHeight()));

    Rocket::Debugger::Initialise(m_guiContext);

    Rocket::Core::String fontNames[4];
	fontNames[0] = "Delicious-Roman.otf";
	fontNames[1] = "Delicious-Italic.otf";
	fontNames[2] = "Delicious-Bold.otf";
	fontNames[3] = "Delicious-BoldItalic.otf";

	for (int i = 0; i < sizeof(fontNames) / sizeof(Rocket::Core::String); i++)
	{
		Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String(Get_BundlePath().c_str()) + fontNames[i]);
	}
    
    std::string mainMenuFilename = Get_BundlePath();
    mainMenuFilename.append("mainMenu.rml");
    m_guiDocument = m_guiContext->LoadDocument(mainMenuFilename.c_str());
	if (m_guiDocument != nullptr)
	{
		m_guiDocument->Show();
		m_guiDocument->RemoveReference();
	}
    
    m_shaderComposite = new CShaderComposite();
    
    for(ui32 i = 0; i < E_RENDER_MODE_WORLD_SPACE_MAX; ++i)
    {
        m_worldSpaceOperations[i] = new CRenderOperationWorldSpace(Get_ScreenWidth(), Get_ScreenHeight(), static_cast<E_RENDER_MODE_WORLD_SPACE>(i), "render.mode.worldspace");
    }
    
    for(ui32 i = 0; i < E_RENDER_MODE_SCREEN_SPACE_MAX; ++i)
    {
        m_screenSpaceOperations[i] = nullptr;
    }
    
    CMaterial* screenOutputMaterial = new CMaterial(m_shaderComposite->Get_Shader(E_SHADER_SCREEN_PLANE));
    m_screenOutputOperation = new CRenderOperationScreenOutput(
		Get_ScreenWidth(), 
		Get_ScreenHeight(), 
		screenOutputMaterial,
		m_glContext->Get_FrameBufferHandle(),
		m_glContext->Get_RenderBufferHandle(),
		"render.mode.screenoutput");
}

CRenderMgr::~CRenderMgr(void)
{
    
}

void CRenderMgr::AddRenderEventListener(CRenderCallback_INTERFACE *_listener, E_RENDER_MODE_WORLD_SPACE _mode)
{
    m_worldSpaceOperations[_mode]->AddEventListener(_listener);
}

void CRenderMgr::RemoveRenderEventListener(CRenderCallback_INTERFACE *_listener, E_RENDER_MODE_WORLD_SPACE _mode)
{
    m_worldSpaceOperations[_mode]->RemoveEventListener(_listener);
}

CTexture* CRenderMgr::ProcessCustomScreenSpaceOperation(CMaterial *_material, ui32 _textureWidth, ui32 _textureHeight)
{
    CRenderOperationScreenSpace* operation = new CRenderOperationScreenSpace(_textureWidth, _textureHeight, E_RENDER_MODE_SCREEN_SPACE_COMMON, _material, "render.mode.custom");
    m_customScreenSpaceOperationsQueue.push(operation);
    return operation->Get_OperatingTexture();
}

void CRenderMgr::OnUpdate(f32 _deltatime)
{    
    for(i32 i = (E_RENDER_MODE_WORLD_SPACE_MAX - 1); i >= 0; --i)
    {
        assert(m_worldSpaceOperations[i] != nullptr);
        m_worldSpaceOperations[i]->Bind();
        m_worldSpaceOperations[i]->Draw();
        m_worldSpaceOperations[i]->Unbind();
    }
    
    for(ui32 i = 0; i < E_RENDER_MODE_SCREEN_SPACE_MAX; ++i)
    {
        if(m_screenSpaceOperations[i] != nullptr)
        {
            m_screenSpaceOperations[i]->Bind();
            m_screenSpaceOperations[i]->Draw();
            m_screenSpaceOperations[i]->Unbind();
        }
    }

    while(!m_customScreenSpaceOperationsQueue.empty())
    {
        CRenderOperationScreenSpace* operation = m_customScreenSpaceOperationsQueue.front();
        operation->Bind();
        operation->Draw();
        operation->Unbind();
        m_customScreenSpaceOperationsQueue.pop();
        delete operation;
    }

    m_screenOutputOperation->Get_Material()->Set_Texture(m_worldSpaceOperations[E_RENDER_MODE_WORLD_SPACE_COMMON]->Get_OperatingTexture(), E_TEXTURE_SLOT_01);
    m_screenOutputOperation->Bind();
    m_screenOutputOperation->Draw();
    m_screenOutputOperation->Unbind();

    m_guiContext->Update();
    m_guiContext->Render();
    
    m_glContext->Present();
    
    GLenum error = glGetError();
    assert(error == GL_NO_ERROR);
}



