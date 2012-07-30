//
//  CGameInGameUI.h
//  iGaia
//
//  Created by code_oneclick on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#define k_MOVE_LEFT_TRACK_NONE  0
#define k_MOVE_RIGHT_TRACK_NONE 1
#define k_MOVE_LEFT_TRACK_INC   2
#define k_MOVE_RIGHT_TRACK_INC  3
#define k_MOVE_LEFT_TRACK_DEC   4
#define k_MOVE_RIGHT_TRACK_DEC  5
#define k_SCROLL_RIGHT_TRACK    6
#define k_SCROLL_LEFT_TRACK     7

@interface CGameInGameUI : UIView<UIScrollViewDelegate>
@property(nonatomic, strong) UILabel* m_pInfoLabel;
@end
