
#include <CGuiShellFilesystem.h>
#include <stdio.h>

CGuiShellFilesystem_INTERFACE::CGuiShellFilesystem_INTERFACE(const Rocket::Core::String& root) : root(root)
{
}

CGuiShellFilesystem_INTERFACE::~CGuiShellFilesystem_INTERFACE(void)
{
}

Rocket::Core::FileHandle CGuiShellFilesystem_INTERFACE::Open(const Rocket::Core::String& path)
{
	FILE* fp = fopen((root + path).CString(), "rb");
	if (fp != NULL)
		return (Rocket::Core::FileHandle) fp;

	fp = fopen(path.CString(), "rb");
	return (Rocket::Core::FileHandle) fp;
}

void CGuiShellFilesystem_INTERFACE::Close(Rocket::Core::FileHandle file)
{
	fclose((FILE*) file);
}

size_t CGuiShellFilesystem_INTERFACE::Read(void* buffer, size_t size, Rocket::Core::FileHandle file)
{
	return fread(buffer, 1, size, (FILE*) file);
}

bool CGuiShellFilesystem_INTERFACE::Seek(Rocket::Core::FileHandle file, long offset, int origin)
{
	return fseek((FILE*) file, offset, origin) == 0;
}

size_t CGuiShellFilesystem_INTERFACE::Tell(Rocket::Core::FileHandle file)
{
	return ftell((FILE*) file);
}
