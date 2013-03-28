//
//  CGuiShellEventListenerInstancer.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#ifndef CUIShellEventListenerInstancer_h
#define CUIShellEventListenerInstancer_h

#include "HCommon.h"

class CUIShellEventListenerInstancer_INTERFACE : public Rocket::Core::EventListenerInstancer
{
public:
    
	CUIShellEventListenerInstancer_INTERFACE(void);
	~CUIShellEventListenerInstancer_INTERFACE(void);

	Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& _value, Rocket::Core::Element* _element);

	void Release(void);
};


#endif 
