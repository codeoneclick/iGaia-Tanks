#include "CGameMainMenuSceneViewController_Win32.h"
#include "CGLContext_iOS.h"
#include "CGLWindow_Win32.h"
#include "CGameMainMenuScene.h"

CGameMainMenuSceneViewController_Win32::CGameMainMenuSceneViewController_Win32(void)
{
	CGLWindow_Win32* glWindow = new CGLWindow_Win32();
	CRoot* root = new CRoot((void*)glWindow);
    CGameMainMenuScene* scene = new CGameMainMenuScene();
    scene->Load(root);
}

CGameMainMenuSceneViewController_Win32::~CGameMainMenuSceneViewController_Win32(void)
{

}