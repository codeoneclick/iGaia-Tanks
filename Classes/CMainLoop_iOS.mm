//
//  CMainLoop_iOS.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "CMainLoop.h"
#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

@interface CMainLoop_iOS : NSObject
{
@private
    std::set<CMainLoopUpdateCallback_INTERFACE*> m_listeners;
}

+ (CMainLoop_iOS*)SharedInstance;

- (void)ConnectToMainLoop:(CMainLoopUpdateCallback_INTERFACE*)_listener;
- (void)DisconnectFromMainLoop:(CMainLoopUpdateCallback_INTERFACE*)_listener;

@end

@implementation CMainLoop_iOS

+ (CMainLoop_iOS*)SharedInstance
{
    static CMainLoop_iOS *instance = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        instance = [[self alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if(self)
    {
        CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(onUpdate:)];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void)ConnectToMainLoop:(CMainLoopUpdateCallback_INTERFACE*)_listener
{
    m_listeners.insert(_listener);
}

- (void)DisconnectFromMainLoop:(CMainLoopUpdateCallback_INTERFACE*)_listener
{
    m_listeners.erase(_listener);
}

- (void)onUpdate:(CADisplayLink*)displayLink
{
    for (std::set<CMainLoopUpdateCallback_INTERFACE*>::iterator iterator = m_listeners.begin(); iterator != m_listeners.end(); ++iterator)
    {
        CMainLoopUpdateCallback_INTERFACE* listener = *iterator;
        listener->Get_Commands()->DispatchMainLoopDidUpdate(0.0f);
    }
}

@end

void ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
    [[CMainLoop_iOS SharedInstance] ConnectToMainLoop:_listener];
}

void DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener)
{
    [[CMainLoop_iOS SharedInstance] DisconnectFromMainLoop:_listener];
}