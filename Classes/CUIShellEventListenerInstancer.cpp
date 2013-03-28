//
//  CGuiShellEventListenerInstancer.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIShellEventListenerInstancer.h"
#include "CUIShellEventHandler.h"


CUIShellEventListenerInstancer_INTERFACE::CUIShellEventListenerInstancer_INTERFACE(void)
{
    
}

CUIShellEventListenerInstancer_INTERFACE::~CUIShellEventListenerInstancer_INTERFACE(void)
{
}

Rocket::Core::EventListener* CUIShellEventListenerInstancer_INTERFACE::InstanceEventListener(const Rocket::Core::String& _command, Rocket::Core::Element* _element)
{
	return new CUIShellEventHandler(_command);
}

void CUIShellEventListenerInstancer_INTERFACE::Release(void)
{
	delete this;
}
