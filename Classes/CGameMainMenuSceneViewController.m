//
//  CGameMainMenuSceneViewController.m
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#import "CGameMainMenuSceneViewController.h"
#import "CGLContext_iOS.h"

@interface CGameMainMenuSceneViewController ()

@property (weak, nonatomic) IBOutlet CGLWindow_iOS *m_glView;

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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload
{
    [self setM_glView:nil];
    [super viewDidUnload];
}
@end
