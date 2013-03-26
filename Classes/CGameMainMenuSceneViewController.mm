//
//  CGameMainMenuSceneViewController.m
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CGameMainMenuSceneViewController.h"
#include "CGLContext_iOS.h"
#include "CGLWindow_iOS.h"
#include "CGameMainMenuScene.h"
#include "CMoveControllerView_iOS.h"
#include "CRotateControllerView_iOS.h"

@interface CGameMainMenuSceneViewController ()

@property(weak, nonatomic) IBOutlet CGLWindow_iOS *m_glView;
@property(unsafe_unretained, nonatomic) CGameMainMenuScene* m_scene;
@property (strong, nonatomic) IBOutlet CMoveControllerView_iOS *m_moveController;
@property (strong, nonatomic) IBOutlet CRotateControllerView_iOS *m_rotateController;

@end

@implementation CGameMainMenuSceneViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {

    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    CRoot* root = new CRoot((__bridge void*)_m_glView);
    self.m_scene = new CGameMainMenuScene();
    self.m_scene->Load(root);
    [self.m_moveController AddEventListener:self.m_scene->Get_CharacterController()];
    [self.m_rotateController AddEventListener:self.m_scene->Get_CharacterController()];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload
{
    [self setM_glView:nil];
    [self setM_moveController:nil];
    [self setM_rotateController:nil];
    [super viewDidUnload];
}
@end
