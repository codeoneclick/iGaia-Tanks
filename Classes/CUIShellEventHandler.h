//
//  CGuiShellEventHandler.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#ifndef CUIShellEventHandler_h
#define CUIShellEventHandler_h

#include "HCommon.h"

class CUIShellEventHandler : public Rocket::Core::EventListener
{
private:

    Rocket::Core::String m_command;

protected:
    
public:
    
	CUIShellEventHandler(const Rocket::Core::String& _command);
	virtual ~CUIShellEventHandler(void);

	void ProcessEvent(Rocket::Core::Event& event);
	void OnDetach(Rocket::Core::Element* element);
};

#endif 
