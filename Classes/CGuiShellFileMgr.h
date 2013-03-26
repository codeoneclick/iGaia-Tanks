
#ifndef CGuiShellFileMgr_h
#define CGuiShellFileMgr_h

#include <Rocket/Core/RocketString.h>
#include <Rocket/Core/FileInterface.h>

class CGuiShellFileMgr_INTERFACE : public Rocket::Core::FileInterface
{
private:

    Rocket::Core::String root;

protected:
    
public:
    
	CGuiShellFileMgr_INTERFACE(const Rocket::Core::String& root);
	~CGuiShellFileMgr_INTERFACE();
	
	Rocket::Core::FileHandle Open(const Rocket::Core::String& path);	
	void Close(Rocket::Core::FileHandle file);	
	size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file);	
	bool Seek(Rocket::Core::FileHandle file, long offset, int origin);	
	size_t Tell(Rocket::Core::FileHandle file);
};

#endif
