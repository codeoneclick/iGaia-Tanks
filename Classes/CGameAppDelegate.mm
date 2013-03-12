//
//  CGameAppDelegate.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CGameAppDelegate.h"
#include "CGameMainMenuSceneViewController.h"

@implementation CGameAppDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.m_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    CGameMainMenuSceneViewController *vc = [CGameMainMenuSceneViewController new];
    UINavigationController* navigationViewController = [[UINavigationController alloc] initWithRootViewController:vc];
    [navigationViewController setNavigationBarHidden:YES animated:NO];
    self.m_window.backgroundColor = [UIColor blackColor];
    [self.m_window setRootViewController:navigationViewController];
    [self.m_window makeKeyAndVisible];
}

@end

