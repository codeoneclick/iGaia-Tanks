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

class CUIMgr;
class CUIShellEventListenerInstancer_INTERFACE : public Rocket::Core::EventListenerInstancer
{
private:

protected:

    CUIMgr* m_uiMgr;

public:
    
	CUIShellEventListenerInstancer_INTERFACE(CUIMgr* _uiMgr);
	~CUIShellEventListenerInstancer_INTERFACE(void);

	Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& _value, Rocket::Core::Element* _element);

	void Release(void);
};


#endif 
