//
// 
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/26/13.
//
//

#include "CUIMgr.h"
#include "CCommon.h"
#include "CMainMenuView.h"

CUIMgr::CUIMgr(void)
{
    Rocket::Core::SetRenderInterface(&m_renderInterface);
	Rocket::Core::SetSystemInterface(&m_commonInterface);

    Rocket::Core::Initialise();
    m_uiContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(Get_ScreenWidth(), Get_ScreenHeight()));

    m_eventListenerInterface = new CUIShellEventListenerInstancer_INTERFACE(this);
    Rocket::Core::Factory::RegisterEventListenerInstancer(m_eventListenerInterface);
	m_eventListenerInterface->RemoveReference();

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

CUIMgr::~CUIMgr(void)
{
    
}

void CUIMgr::OnInputTapRecognizerPressed(i32 _x, i32 _y)
{
    assert(m_uiContext != nullptr);
    m_uiContext->ProcessMouseMove(_x, _y, 0);
    m_uiContext->ProcessMouseButtonDown(0, 0);
}

void CUIMgr::OnInputTapRecognizerMoved(i32 _x, i32 _y)
{
    assert(m_uiContext != nullptr);
    m_uiContext->ProcessMouseMove(_x, _y, 0);
}

void CUIMgr::OnInputTapRecognizerReleased(i32 _x, i32 _y)
{
    assert(m_uiContext != nullptr);
    m_uiContext->ProcessMouseMove(_x, _y, 0);
    m_uiContext->ProcessMouseButtonUp(0, 0);
}

void CUIMgr::OnPresent(void)
{
    assert(m_uiContext != nullptr);
    m_uiContext->Update();
    m_uiContext->Render();
}

void CUIMgr::FillUIView(IUIView_INTERFACE *_view, const std::string &_filename)
{
    assert(m_uiContext != nullptr);
    std::string filename = Get_BundlePath();
    filename.append(_filename);
    Rocket::Core::ElementDocument* document = m_uiContext->LoadDocument(filename.c_str());
    assert(document != nullptr);
	if (document != nullptr)
	{
		document->Show();
		document->RemoveReference();
        Rocket::Core::Element* button = document->GetElementById("buttonExtId");
        button->SetProperty("left", Rocket::Core::Property(80.0f, Rocket::Core::Property::PX));
        button->SetClass("buttonExt2", true);
        assert(button != nullptr);
	}
    assert(_view != nullptr);
    _view->Set_Document(document);
}

void CUIMgr::PerformEvent(const std::string &_command)
{
    for(std::set<CUIEventCallback_INTERFACE*>::iterator iterator = m_uiEventListenersContainer.begin(); iterator != m_uiEventListenersContainer.end(); ++iterator)
    {
        CUIEventCallback_INTERFACE* listener = (*iterator);
        listener->Get_Commands()->DispatchEventDidPerform(_command);
    }
}

void CUIMgr::AddUIEventListener(CUIEventCallback_INTERFACE *_listener)
{
    m_uiEventListenersContainer.insert(_listener);
}

void CUIMgr::RemoveUIEventListener(CUIEventCallback_INTERFACE *_listener)
{
    m_uiEventListenersContainer.erase(_listener);
}




