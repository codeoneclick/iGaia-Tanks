//
//  CSlider.h
//  iGaia
//
//  Created by sergey sergeev on 5/29/12.
//
//

#import <UIKit/UIKit.h>

@interface CSlider : UIView
{
    NSInteger m_iMaxOffsetX;
    NSInteger m_iMinOffsetX;
    UIImageView* m_pBackground;
    UIImageView* m_pControl;
}
@end
