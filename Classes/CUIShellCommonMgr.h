
#ifndef CUIShellCommonMgr_h
#define CUIShellCommonMgr_h

#include "HCommon.h"

class CUIShellCommonMgr_INTERFACE : public Rocket::Core::SystemInterface
{
private:

protected:
    
public:

    CUIShellCommonMgr_INTERFACE(void) {};
    ~CUIShellCommonMgr_INTERFACE(void) {};
    
	virtual float GetElapsedTime();
    
};

#endif
