//
//  GameViewController.m
//  iGaia
//
//  Created by sergey.sergeev on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "GameViewController.h"
#import "MainAppDelegate.h"

GameViewController* g_GameViewController;

@implementation GameViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
        g_GameViewController = self;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle
- (void)loadView
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    self.view = [GLView Instance];
    m_pGameInGameUI = [[CGameInGameUI alloc] initWithFrame:CGRectMake(0, 0, screenBounds.size.height, screenBounds.size.width)];
    m_pGameMenuUI = [[CGameMenuUI alloc] initWithFrame:CGRectMake(0, 0, screenBounds.size.height, screenBounds.size.width)];
    [self.view addSubview:m_pGameMenuUI];
    
    NSMethodSignature *pMethodSignature = [self methodSignatureForSelector:@selector(onTick:)];
    NSInvocation *pInvocation = [NSInvocation invocationWithMethodSignature:pMethodSignature];
    [pInvocation setTarget:self];
    [pInvocation setSelector:@selector(onTick:)];
    NSTimer *pTimer = [NSTimer timerWithTimeInterval:1.0 invocation:pInvocation repeats:YES];
    NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
    [runLoop addTimer:pTimer forMode:NSDefaultRunLoopMode];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIDeviceOrientationLandscapeRight || interfaceOrientation == UIDeviceOrientationLandscapeLeft;
}

-(void)onTick:(NSTimer *)timer
{
    [m_pGameMenuUI.m_pInfoLabel setText:[NSString stringWithFormat:@"FPS : %i, Triangles : %i", CSettings::g_iTotalFramesPerSecond, CSettings::g_iTotalTriagnlesPerFrame]];
}

-(void)Set_GameUI:(NSString*)_sName
{
    NSLog(@"[Set_GameUI] Name : %@", _sName);
}

extern void Global_Set_GameUI(const std::string& _sName)
{
    [g_GameViewController Set_GameUI:[NSString stringWithCString:_sName.c_str() encoding:NSUTF8StringEncoding]];
}

@end
