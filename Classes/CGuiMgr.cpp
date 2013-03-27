//
//  CGuiMgr.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#include "CGuiMgr.h"
#include "CCommon.h"

CGuiMgr::CGuiMgr(void)
{
    Rocket::Core::SetRenderInterface(&m_renderInterface);
	Rocket::Core::SetSystemInterface(&m_commonInterface);

    Rocket::Core::Initialise();
    m_guiContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(Get_ScreenWidth(), Get_ScreenHeight()));

    Rocket::Core::String fontNames[4];
	fontNames[0] = "Delicious-Roman.otf";
	fontNames[1] = "Delicious-Italic.otf";
	fontNames[2] = "Delicious-Bold.otf";
	fontNames[3] = "Delicious-BoldItalic.otf";

	for (int i = 0; i < sizeof(fontNames) / sizeof(Rocket::Core::String); i++)
	{
		Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String(Get_BundlePath().c_str()) + fontNames[i]);
	}

    m_shaderComposite = nullptr;
}

void CGuiMgr::TEMP(void)
{
	std::string mainMenuFilename = Get_BundlePath();
    mainMenuFilename.append("main_menu.rml");
    m_guiDocument = m_guiContext->LoadDocument(mainMenuFilename.c_str());
	if (m_guiDocument != nullptr)
	{
		m_guiDocument->Show();
		m_guiDocument->RemoveReference();
	}
}

CGuiMgr::~CGuiMgr(void)
{
    
}

void CGuiMgr::OnInputTapRecognizerPressed(i32 _x, i32 _y)
{
    assert(m_guiContext != nullptr);
    m_guiContext->ProcessMouseMove(_x, _y, 0);
    m_guiContext->ProcessMouseButtonDown(0, 0);
}

void CGuiMgr::OnInputTapRecognizerMoved(i32 _x, i32 _y)
{
    assert(m_guiContext != nullptr);
    m_guiContext->ProcessMouseMove(_x, _y, 0);
}

void CGuiMgr::OnInputTapRecognizerReleased(i32 _x, i32 _y)
{
    assert(m_guiContext != nullptr);
    m_guiContext->ProcessMouseMove(_x, _y, 0);
    m_guiContext->ProcessMouseButtonUp(0, 0);
}

void CGuiMgr::OnPresent(void)
{
    assert(m_guiContext != nullptr);
    m_guiContext->Update();
    m_guiContext->Render();
}


