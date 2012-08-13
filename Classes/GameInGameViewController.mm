//
//  GameInGameViewController.m
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#import "GameInGameViewController.h"
#import "GLView.h"
#import "CJoystick.h"
#import "CSlider.h"

#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"

@interface GameInGameViewController ()
{
    IBOutlet UIView* m_pOpenGLView;
    UILabel* m_pInfoLabel;
}
@end

@implementation GameInGameViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        m_pInfoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 32)];
        [m_pInfoLabel setBackgroundColor:[UIColor blackColor]];
        [m_pInfoLabel setTextColor:[UIColor whiteColor]];
        [self.view addSubview:m_pInfoLabel];
        
        CJoystick* pJoystick = [[CJoystick alloc] initWithFrame:CGRectMake(16, self.view.frame.size.height - (96 + 16), 96, 96)];
        [self.view addSubview:pJoystick];
        
        CSlider* pSlider = [[CSlider alloc] initWithFrame:CGRectMake(self.view.frame.size.width - (96 + 16), self.view.frame.size.height - (96 + 16), 96, 96)];
        [self.view addSubview:pSlider];
        
        UIButton* pCameraButton = [[UIButton alloc] initWithFrame:CGRectMake(self.view.frame.size.width - 66, 2, 64, 28)];
        [pCameraButton setBackgroundColor:[UIColor whiteColor]];
        [pCameraButton setImage:[UIImage imageNamed:@"camera_button.png"] forState:UIControlStateNormal];
        [pCameraButton.imageView setContentMode:UIViewContentModeScaleAspectFit];
        [pCameraButton addTarget:self action:@selector(onCameraButtonPress:) forControlEvents:UIControlEventTouchUpInside];
        pCameraButton.layer.cornerRadius = 8;
        pCameraButton.clipsToBounds = YES;
        [self.view addSubview:pCameraButton];
        
        UIButton* pShootButton = [[UIButton alloc] initWithFrame:CGRectMake(self.view.frame.size.width - (96 - 8), self.view.frame.size.height - 170, 48, 48)];
        [pShootButton setBackgroundColor:[UIColor redColor]];
        [pShootButton addTarget:self action:@selector(OnShootButtonPress:) forControlEvents:UIControlEventTouchUpInside];
        pShootButton.layer.cornerRadius = 24;
        [pShootButton setAlpha:0.5];
        pShootButton.clipsToBounds = YES;
        [self.view addSubview:pShootButton];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[GLView Instance] clearScreen];
    [m_pOpenGLView addSubview:[GLView Instance]];
    
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene == NULL)
    {
        return;
    }
    
    pScene->Unload();
    SAFE_DELETE(pScene);
    CGameSceneMgr::Instance()->Set_Scene(NULL);

    if(CGameSceneMgr::Instance()->Get_Scene() != NULL)
    {
        return;
    }
    
    pScene = new CGameInGameScene();
    CGameSceneMgr::Instance()->Set_Scene(pScene);
    pScene->Load();
    
    UIAccelerometer*  accelerometer = [UIAccelerometer sharedAccelerometer];
    accelerometer.updateInterval = 0.33f;
    accelerometer.delegate = self;
    
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

- (void)onCameraButtonPress:(UIButton*)sender
{
    static_cast<CGameInGameScene*>(CGameSceneMgr::Instance()->Get_Scene())->SwitchCameraModeToNext();
}

- (void)OnShootButtonPress:(UIButton*)sender
{
    CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Shoot();
}

-(void)onTick:(NSTimer *)timer
{
    [m_pInfoLabel setText:[NSString stringWithFormat:@"FPS : %i, Triangles : %i", CSettings::g_iTotalFramesPerSecond, CSettings::g_iTotalTriagnlesPerFrame]];
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    CSettings::g_fAccellerometer_X = acceleration.x;
    CSettings::g_fAccellerometer_Y = acceleration.y;
    CSettings::g_fAccellerometer_Z = acceleration.z;
}

- (IBAction)OnTankTypeChanged:(id)sender
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene == NULL || pScene->Get_MainCharacterController() == NULL)
    {
        return;
    }
    ICharacterController* pController = pScene->Get_MainCharacterController();
    
    UISegmentedControl *pSegmentedControl = (UISegmentedControl *)sender;
    if(pSegmentedControl.selectedSegmentIndex == 0)
    {
        pController->Set_FullSet(GameTankSDB::E_CHARACTER_FULLSET_TYPE_LIGHT);
    }
    else if(pSegmentedControl.selectedSegmentIndex == 1)
    {
        pController->Set_FullSet(GameTankSDB::E_CHARACTER_FULLSET_TYPE_MEDIUM);
    }
    else if(pSegmentedControl.selectedSegmentIndex == 2)
    {
        pController->Set_FullSet(GameTankSDB::E_CHARACTER_FULLSET_TYPE_HEAVY);
    }
}

@end
