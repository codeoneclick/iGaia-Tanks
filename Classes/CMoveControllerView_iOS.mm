//
//  CMoveControllerView_iOS.m
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#include "CMoveControllerView_iOS.h"
#include "HGameEnum.h"

@interface CMoveControllerView_iOS()
{
    std::set<CMoveControllerCallback_INTERFACE*> m_listeners;
}

@property(nonatomic, assign) NSInteger m_maxOffsetX;
@property(nonatomic, assign) NSInteger m_minOffsetX;
@property(nonatomic, assign) NSInteger m_maxOffsetY;
@property(nonatomic, assign) NSInteger m_minOffsetY;
@property(nonatomic, strong) UIImageView* m_background;
@property(nonatomic, strong) UIImageView* m_control;

@end

@implementation CMoveControllerView_iOS


- (void)awakeFromNib
{
    [self setBackgroundColor:[UIColor clearColor]];

    _m_maxOffsetX = self.frame.size.width - 32;
    _m_minOffsetX = 32;
    _m_maxOffsetY = self.frame.size.height - 32;
    _m_minOffsetY = 32;

    _m_background = [[UIImageView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.frame.size.width, self.frame.size.height)];
    [_m_background setBackgroundColor:[UIColor yellowColor]];
    [self addSubview:_m_background];

    _m_control = [[UIImageView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.frame.size.width / 3, self.frame.size.height / 3)];
    _m_control.center = CGPointMake(self.frame.size.width / 2.0f, self.frame.size.height / 2.0f);
    [_m_control setBackgroundColor:[UIColor greenColor]];
    [self addSubview:_m_control];
}

- (void)AddEventListener:(CMoveControllerCallback_INTERFACE*)_listener
{
    m_listeners.insert(_listener);
}

- (void)RemoveEventListener:(CMoveControllerCallback_INTERFACE*)_listener
{
    m_listeners.erase(_listener);
}

- (void)invokeCallback:(E_MOVE_CONTROLLER_DIRECTION)_direction
{
    for (std::set<CMoveControllerCallback_INTERFACE*>::iterator iterator = m_listeners.begin(); iterator != m_listeners.end(); ++iterator)
    {
        CMoveControllerCallback_INTERFACE* listener = *iterator;
        listener->Get_Commands()->DispatchMoveControllerDidUpdate(_direction);
    }
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        CGPoint touchLocation = [touch locationInView:self];
        [self update:touchLocation];
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        CGPoint touchLocation = [touch locationInView:self];
        [self update:touchLocation];
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        _m_control.center = CGPointMake(_m_background.frame.size.width / 2, _m_background.frame.size.height / 2);
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_NONE];
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{

}

- (void)update:(CGPoint)touchPoint
{
    if(touchPoint.x > _m_maxOffsetX && touchPoint.y > _m_maxOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_NORTH_WEST];
    }
    else if(touchPoint.x > _m_maxOffsetX && touchPoint.y < _m_minOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_SOUTH_WEST];
    }
    else if(touchPoint.x < _m_minOffsetX && touchPoint.y > _m_maxOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_NORTH_EAST];
    }
    else if(touchPoint.x < _m_minOffsetX && touchPoint.y < _m_minOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_SOUTH_EAST];
    }
    else if(touchPoint.x > _m_maxOffsetX)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_WEST];
    }
    else if(touchPoint.x < _m_minOffsetX)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_EAST];
    }
    else if(touchPoint.y >_m_maxOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_NORTH];
    }
    else if(touchPoint.y < _m_minOffsetY)
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_SOUTH];
    }
    else
    {
        [self invokeCallback:E_MOVE_CONTROLLER_DIRECTION_NONE];
    }
    _m_control.center = CGPointMake(touchPoint.x, touchPoint.y);
}

@end
