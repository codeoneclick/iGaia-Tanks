//
//  CJoystick.h
//  iGaia
//
//  Created by sergey sergeev on 5/7/12.
//
//

#import <UIKit/UIKit.h>

@interface CJoystick : UIView
{
    NSInteger m_iMaxOffsetX;
    NSInteger m_iMinOffsetX;
    NSInteger m_iMaxOffsetY;
    NSInteger m_iMinOffsetY;
    UIImageView* m_pBackground;
    UIImageView* m_pControl;
}
@end
