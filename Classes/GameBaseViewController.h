//
//  GameBaseViewController.h
//  iGaia
//
//  Created by sergey sergeev on 7/11/12.
//
//

#import <UIKit/UIKit.h>

@interface GameBaseViewController : UIViewController

- (void)pushViewController:(UIViewController*)vc;
- (void)popViewController;
- (void)popViewControllerToRoot;

@end
