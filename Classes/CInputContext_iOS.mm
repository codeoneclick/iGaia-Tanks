//
//  CInputMgr.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#include "CInputContext.h"
#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

@interface CInputRecognizerWindow : UIView

@property(nonatomic, unsafe_unretained) CInputContext* m_inputMgr;

@end

@implementation CInputRecognizerWindow

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_inputMgr != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_inputMgr->TapRecognizerPressed(point.x, point.y);
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_inputMgr != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_inputMgr->TapRecognizerMoved(point.x, point.y);
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_inputMgr != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_inputMgr->TapRecognizerReleased(point.x, point.y);
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_inputMgr != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_inputMgr->TapRecognizerReleased(point.x, point.y);
    }
}

@end

CInputContext::CInputContext(void* _glWindow)
{
    UIView* glWindow = (__bridge UIView*)_glWindow;

    CInputRecognizerWindow* inputRecognizerWindow = [CInputRecognizerWindow new];
    inputRecognizerWindow.m_inputMgr = this;
    inputRecognizerWindow.frame = CGRectMake(0.0f, 0.0f, glWindow.frame.size.width, glWindow.frame.size.height);
    [glWindow addSubview:inputRecognizerWindow];
}

CInputContext::~CInputContext(void)
{

}

void CInputContext::AddTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
    m_tapRecognizerListeners.insert(_listener);
}

void CInputContext::RemoveTapRecognizerListener(CInputTapRecognizerCallback_INTERFACE *_listener)
{
    m_tapRecognizerListeners.erase(_listener);
}

void CInputContext::TapRecognizerPressed(i32 _x, i32 _y)
{
    for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
    {
        CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
        listener->Get_Commands()->DispatchInputTapRecognizerDidPressed(_x, _y);
    }
}

void CInputContext::TapRecognizerMoved(i32 _x, i32 _y)
{
    for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
    {
        CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
        listener->Get_Commands()->DispatchInputTapRecognizerDidMoved(_x, _y);
    }
}

void CInputContext::TapRecognizerReleased(i32 _x, i32 _y)
{
    for(std::set<CInputTapRecognizerCallback_INTERFACE*>::iterator iterator = m_tapRecognizerListeners.begin(); iterator != m_tapRecognizerListeners.end(); ++iterator)
    {
        CInputTapRecognizerCallback_INTERFACE* listener = (*iterator);
        listener->Get_Commands()->DispatchInputTapRecognizerDidReleased(_x, _y);
    }
}







