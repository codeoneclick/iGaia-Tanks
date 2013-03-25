// iGaia-CartoonPanzers.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "../Classes/CGLWindow_Win32.h"

int main(int argc, const char* argv[])
{
	CGLWindow_Win32* glWindow = new CGLWindow_Win32();
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while(WM_QUIT != msg.message)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			glWindow->Process();
		}
	}

	return 0;
}

