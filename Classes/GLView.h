//#import "IRenderiniGaia.hpp"
#import <QuartzCore/QuartzCore.h>
#include "CGame.h"

@interface GLView : UIView {
@private
    CAEAGLLayer* m_pEAGlLayer;
    EAGLContext* m_pContext;
}

+ (GLView*)Instance;

- (void)drawView:(CADisplayLink*)displayLink;
- (void)didRotate:(NSNotification*)notification;

- (void)clearScreen;

@end
