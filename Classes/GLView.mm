#import "GLView.h"
#import <OpenGLES/ES2/gl.h> // <-- for GL_RENDERBUFFER only
#include "CInput.h"
#include "CWindow.h"

@implementation GLView

+ (GLView*)Instance
{
    static GLView *pInstance = nil;
    static dispatch_once_t oncePredicate;
    
    dispatch_once(&oncePredicate, ^
    {
        CGRect screenBounds = [[UIScreen mainScreen] bounds];
        pInstance = [[self alloc] initWithFrame:CGRectMake(0, 0, screenBounds.size.height, screenBounds.size.width)];
    });
    return pInstance;
}

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect) frame
{
    if (self = [super initWithFrame:frame])
    {
        m_pEAGlLayer = (CAEAGLLayer*) super.layer;
        m_pEAGlLayer.opaque = YES;

        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_pContext = [[EAGLContext alloc] initWithAPI:api];

        if (!m_pContext || ![EAGLContext setCurrentContext:m_pContext])
        {
            return nil;
        }

        CWindow::Set_ScreenWidth(CGRectGetWidth(frame));
        CWindow::Set_ScreenHeight(CGRectGetHeight(frame));
        
        CGame::Instance()->Load();
        
        GLuint hScreenColorBuffer;
        glGenRenderbuffers(1, &hScreenColorBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, hScreenColorBuffer);        
        [m_pContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:m_pEAGlLayer];
        
        GLuint hScreenFrameBuffer;
        glGenFramebuffers(1, &hScreenFrameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, hScreenFrameBuffer);   
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, hScreenColorBuffer);
        
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout<<"[GLView::GLView] Screen Framebuffer FAILURE"<<std::endl;
        }
        
        CWindow::Set_ScreenFBO(hScreenFrameBuffer);

        CADisplayLink* pDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        [pDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void) didRotate: (NSNotification*) notification
{ 
 
}

- (void) drawView:(CADisplayLink*)displayLink
{
    CGame::Instance()->Update();
    CGame::Instance()->Render();
    [m_pContext presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event 
{
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_State(CInput::E_STATE_TOUCH, glm::vec2(TouchLocation.x, TouchLocation.y));
    }
}
- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_State(CInput::E_STATE_MOVE, glm::vec2(TouchLocation.x, TouchLocation.y));
    }
}
- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event 
{
    for (UITouch*touch in touches)
    {
        CGPoint TouchLocation = [touch locationInView:self];
        CInput::Instance()->Set_State(CInput::E_STATE_UNTOUCH, glm::vec2(TouchLocation.x, TouchLocation.y));
    }
}
- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event 
{

}

- (void)clearScreen
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    [m_pContext presentRenderbuffer:GL_RENDERBUFFER];
}

@end
