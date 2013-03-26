
#ifndef CGuiShellFilesystem_h
#define CGuiShellFilesystem_h

#include <Rocket/Core/RocketString.h>
#include <Rocket/Core/FileInterface.h>

class CGuiShellFilesystem_INTERFACE : public Rocket::Core::FileInterface
{
private:

    Rocket::Core::String root;

protected:
    
public:
    
	CGuiShellFilesystem_INTERFACE(const Rocket::Core::String& root);
	~CGuiShellFilesystem_INTERFACE();
	
	Rocket::Core::FileHandle Open(const Rocket::Core::String& path);	
	void Close(Rocket::Core::FileHandle file);	
	size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file);	
	bool Seek(Rocket::Core::FileHandle file, long offset, int origin);	
	size_t Tell(Rocket::Core::FileHandle file);
};

#endif
