//
//  CGuiShellEventHandler.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIShellEventHandler.h"
#include "CUIMgr.h"

CUIShellEventHandler::CUIShellEventHandler(CUIMgr* _uiMgr, const Rocket::Core::String& _command) : m_command(_command), m_uiMgr(_uiMgr)
{
    
}

CUIShellEventHandler::~CUIShellEventHandler(void)
{
    
}

void CUIShellEventHandler::ProcessEvent(Rocket::Core::Event& _event)
{
    assert(m_uiMgr != nullptr);
	m_uiMgr->PerformEvent(m_command.CString());
}

void CUIShellEventHandler::OnDetach(Rocket::Core::Element* ROCKET_UNUSED(element))
{
	delete this;
}
