//
//  CGuiShellEventListenerInstancer.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CUIShellEventListenerInstancer.h"
#include "CUIShellEventHandler.h"
#include "CUIMgr.h"


CUIShellEventListenerInstancer_INTERFACE::CUIShellEventListenerInstancer_INTERFACE(CUIMgr* _uiMgr) : m_uiMgr(_uiMgr)
{
    
}

CUIShellEventListenerInstancer_INTERFACE::~CUIShellEventListenerInstancer_INTERFACE(void)
{
}

Rocket::Core::EventListener* CUIShellEventListenerInstancer_INTERFACE::InstanceEventListener(const Rocket::Core::String& _command, Rocket::Core::Element* _element)
{
    assert(m_uiMgr != nullptr);
	return new CUIShellEventHandler(m_uiMgr, _command);
}

void CUIShellEventListenerInstancer_INTERFACE::Release(void)
{
	delete this;
}
