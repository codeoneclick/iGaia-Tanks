
#import "MainAppDelegate.h"
#import "MainMenuViewController.h"
#import "GameViewController.h"

@implementation MainAppDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    m_pWindow = [[UIWindow alloc] initWithFrame: screenBounds];
    MainMenuViewController *vc = [MainMenuViewController new];
    m_pNavigationViewController = [[UINavigationController alloc] initWithRootViewController:vc];
    [m_pNavigationViewController setNavigationBarHidden:YES animated:NO];
    m_pWindow.backgroundColor = [UIColor blackColor];
    [m_pWindow addSubview:m_pNavigationViewController.view];
    [m_pWindow makeKeyAndVisible];
}  


@end
