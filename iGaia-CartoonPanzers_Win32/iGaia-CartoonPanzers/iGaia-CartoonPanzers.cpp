// iGaia-CartoonPanzers.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "../Classes/CGLWindow_Win32.h"
#include "../Classes/CGLContext_Win32.h"
#include "../Classes/CMainLoop.h"
#include "../Classes/CGameMainMenuSceneViewController_Win32.h"

int main(int argc, const char* argv[])
{
	CGameMainMenuSceneViewController_Win32* controller = new CGameMainMenuSceneViewController_Win32();
	Run();
	return 0;
}

