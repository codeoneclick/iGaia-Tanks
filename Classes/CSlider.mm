//
//  CSlider.m
//  iGaia
//
//  Created by sergey sergeev on 5/29/12.
//
//

#import "CSlider.h"
#import "CGameSceneMgr.h"

@implementation CSlider

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self setBackgroundColor:[UIColor clearColor]];
        m_iMaxOffsetX = 80;
        m_iMinOffsetX = 48;
        
        m_pBackground = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
        [m_pBackground setImage:[UIImage imageNamed:@"joystick.png"]];
        [m_pBackground setBackgroundColor:[UIColor clearColor]];
        [m_pBackground setAlpha:0.5f];
        [self addSubview:m_pBackground];
        
        m_pControl = [[UIImageView alloc] initWithFrame:CGRectMake(self.frame.size.width / 2 - (self.frame.size.width / 3) / 2, self.frame.size.height / 2 - (self.frame.size.height / 3) / 2, self.frame.size.width / 3, self.frame.size.height / 3)];
        [m_pControl setImage:[UIImage imageNamed:@"joystick.png"]];
        [m_pControl setBackgroundColor:[UIColor clearColor]];
        [m_pControl setAlpha:0.75];
        [self addSubview:m_pControl];
    }
    return self;
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        [self update:TouchLocation];
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        [self update:TouchLocation];
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event 
{
    for (UITouch*touch in touches)
    {
        CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerTowerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE);
        CGRect tRect = m_pControl.frame;
        tRect.origin.x = self.frame.size.width / 2 - (self.frame.size.width / 3) / 2;
        m_pControl.frame = tRect;
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event 
{
    
}

- (void)update:(CGPoint)touchPoint
{
    if(touchPoint.x > m_iMaxOffsetX)
    {
        CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerTowerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_LEFT);
    }
    else if(touchPoint.x < m_iMinOffsetX)
    {
        CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerTowerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_RIGHT);
    }
    else
    {
        CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerTowerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE);
    }
    
    CGRect tRect = m_pControl.frame;
    tRect.origin.x = touchPoint.x - tRect.size.width / 2;
    m_pControl.frame = tRect;
}


@end
