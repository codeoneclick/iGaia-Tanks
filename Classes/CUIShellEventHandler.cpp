//
//  CGuiShellEventHandler.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIShellEventHandler.h"

CUIShellEventHandler::CUIShellEventHandler(const Rocket::Core::String& _command) : m_command(_command)
{
    
}

CUIShellEventHandler::~CUIShellEventHandler(void)
{
    
}

void CUIShellEventHandler::ProcessEvent(Rocket::Core::Event& _event)
{
	
}

void CUIShellEventHandler::OnDetach(Rocket::Core::Element* ROCKET_UNUSED(element))
{
	delete this;
}
