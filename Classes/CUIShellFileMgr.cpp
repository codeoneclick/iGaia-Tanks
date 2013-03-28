

#include "CUIShellFileMgr.h"

CUIShellFileMgr_INTERFACE::CUIShellFileMgr_INTERFACE(const Rocket::Core::String& root) : root(root)
{
}

CUIShellFileMgr_INTERFACE::~CUIShellFileMgr_INTERFACE(void)
{
}

Rocket::Core::FileHandle CUIShellFileMgr_INTERFACE::Open(const Rocket::Core::String& path)
{
	FILE* fp = fopen((root + path).CString(), "rb");
	if (fp != NULL)
		return (Rocket::Core::FileHandle) fp;

	fp = fopen(path.CString(), "rb");
	return (Rocket::Core::FileHandle) fp;
}

void CUIShellFileMgr_INTERFACE::Close(Rocket::Core::FileHandle file)
{
	fclose((FILE*) file);
}

size_t CUIShellFileMgr_INTERFACE::Read(void* buffer, size_t size, Rocket::Core::FileHandle file)
{
	return fread(buffer, 1, size, (FILE*) file);
}

bool CUIShellFileMgr_INTERFACE::Seek(Rocket::Core::FileHandle file, long offset, int origin)
{
	return fseek((FILE*) file, offset, origin) == 0;
}

size_t CUIShellFileMgr_INTERFACE::Tell(Rocket::Core::FileHandle file)
{
	return ftell((FILE*) file);
}
