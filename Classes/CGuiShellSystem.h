
#ifndef CGuiShellSystem_h
#define CGuiShellSystem_h

#include <Rocket/Core/SystemInterface.h>

class CGuiShellSystem_INTERFACE : public Rocket::Core::SystemInterface
{
private:

protected:
    
public:

    CGuiShellSystem_INTERFACE(void) {};
    ~CGuiShellSystem_INTERFACE(void) {};
    
	virtual float GetElapsedTime();
    
};

#endif
