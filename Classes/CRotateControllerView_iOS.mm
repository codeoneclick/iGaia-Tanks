//
//  CRotateControllerView_iOS.m
//  iGaia
//
//  Created by Sergey Sergeev on 3/19/13.
//
//

#include "CRotateControllerView_iOS.h"
#include "HGameEnum.h"

@interface CRotateControllerView_iOS()
{
    std::set<CRotateControllerCallback_INTERFACE*> m_listeners;
}

@property(nonatomic, assign) NSInteger m_maxOffsetX;
@property(nonatomic, assign) NSInteger m_minOffsetX;
@property(nonatomic, strong) UIImageView* m_background;
@property(nonatomic, strong) UIImageView* m_control;

@end

@implementation CRotateControllerView_iOS

- (void)awakeFromNib
{
    [self setBackgroundColor:[UIColor clearColor]];

    _m_maxOffsetX = self.frame.size.width - 32;
    _m_minOffsetX = 32;

    _m_background = [[UIImageView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.frame.size.width, self.frame.size.height)];
    [_m_background setBackgroundColor:[UIColor yellowColor]];
    [self addSubview:_m_background];

    _m_control = [[UIImageView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.frame.size.width / 3, self.frame.size.height / 3)];
    _m_control.center = CGPointMake(self.frame.size.width / 2.0f, self.frame.size.height / 2.0f);
    [_m_control setBackgroundColor:[UIColor greenColor]];
    [self addSubview:_m_control];
}

- (void)AddEventListener:(CRotateControllerCallback_INTERFACE*)_listener
{
    m_listeners.insert(_listener);
}

- (void)RemoveEventListener:(CRotateControllerCallback_INTERFACE*)_listener
{
    m_listeners.erase(_listener);
}

- (void)invokeCallback:(E_ROTATE_CONTROLLER_DIRECTION)_direction
{
    for (std::set<CRotateControllerCallback_INTERFACE*>::iterator iterator = m_listeners.begin(); iterator != m_listeners.end(); ++iterator)
    {
        CRotateControllerCallback_INTERFACE* listener = *iterator;
        listener->Get_Commands()->DispatchRotateControllerDidUpdate(_direction);
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
        [self invokeCallback:E_ROTATE_CONTROLLER_DIRECTION_NONE];
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{

}

- (void)update:(CGPoint)touchPoint
{
    if(touchPoint.x > _m_maxOffsetX)
    {
        [self invokeCallback:E_ROTATE_CONTROLLER_DIRECTION_RIGHT];
    }
    else if(touchPoint.x < _m_minOffsetX)
    {
        [self invokeCallback:E_ROTATE_CONTROLLER_DIRECTION_LEFT];
    }
    else
    {
        [self invokeCallback:E_ROTATE_CONTROLLER_DIRECTION_NONE];
    }
    _m_control.center = CGPointMake(touchPoint.x, touchPoint.y);
}

@end
