//
//  GameLoadingViewController.m
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#import "GameLoadingViewController.h"
#import "GameInGameViewController.h"
#import "GLView.h"

@interface GameLoadingViewController ()

@end

@implementation GameLoadingViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewDidAppear:(BOOL)animated
{
    [self performSelector:@selector(loadInGameScene) withObject:self afterDelay:3];
}

- (void)loadInGameScene
{
    GameInGameViewController* vc = [GameInGameViewController new];
    [self pushViewController:vc];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIDeviceOrientationLandscapeRight || interfaceOrientation == UIDeviceOrientationLandscapeLeft;
}

@end
