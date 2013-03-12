//
//  CGameAppDelegate.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CGameAppDelegate.h"

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pWindow = [[UIWindow alloc] initWithFrame: screenBounds];
    MainMenuViewController *vc = [MainMenuViewController new];
    m_pNavigationViewController = [[UINavigationController alloc] initWithRootViewController:vc];
    [m_pNavigationViewController setNavigationBarHidden:YES animated:NO];
    m_pWindow.backgroundColor = [UIColor blackColor];
    [m_pWindow setRootViewController:_pNavigationViewController];
    [m_pWindow makeKeyAndVisible];
    
}
