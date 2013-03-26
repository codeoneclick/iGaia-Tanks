
#ifndef CGuiShellCommonMgr_h
#define CGuiShellCommonMgr_h

#include <Rocket/Core/SystemInterface.h>

class CGuiShellCommonMgr_INTERFACE : public Rocket::Core::SystemInterface
{
private:

protected:
    
public:

    CGuiShellCommonMgr_INTERFACE(void) {};
    ~CGuiShellCommonMgr_INTERFACE(void) {};
    
	virtual float GetElapsedTime();
    
};

#endif
