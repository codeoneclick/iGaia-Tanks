

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "X11/Xlib.h"
#include "X11/Xutil.h"


#include "CWindow.h"
#include "CGame.h"
#include "CGameSceneMgr.h"

#include <Common.h>
#include <memory>

// Width and height of the window
#define WINDOW_WIDTH	960
#define WINDOW_HEIGHT	640

// Index to bind the attributes to vertex shaders
#define VERTEX_ARRAY	0

/*!****************************************************************************
 @Function		TestEGLError
 @Input			pszLocation		location in the program where the error took
								place. ie: function name
 @Return		bool			true if no EGL error was detected
 @Description	Tests for an EGL error and prints it
******************************************************************************/
bool TestEGLError(const char* pszLocation)
{
	/*
		eglGetError returns the last error that has happened using egl,
		not the status of the last called function. The user has to
		check after every single egl call or at least once every frame.
	*/
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		printf("%s failed (%d).\n", pszLocation, iErr);
		return false;
	}

	return true;
}

const EGLint pi32ConfigAttribs2[] =
{
	EGL_LEVEL,				0,
	EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
	EGL_NATIVE_RENDERABLE,	EGL_FALSE,
	EGL_DEPTH_SIZE,			EGL_DONT_CARE,
	EGL_NONE
};

enum EKeys
{
    VK_LEFT = 113,
    VK_RIGHT = 114,
    VK_UP = 111,
    VK_DOWN = 116,

    MAX_KEYS = 256
};

static bool keys[MAX_KEYS];

void ProcessInput ( )
{
	if( keys[VK_LEFT] )
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_LEFT);
	}
	else if( keys[VK_RIGHT] )
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT);
	}
	else
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_SteerState(ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_NONE);
	}

	if( keys[VK_UP] )
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_MoveState(ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD);
	}
	else if( keys[VK_DOWN] )
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_MoveState(ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD);
	}
	else
	{
		CGameSceneMgr::Instance()->Get_Scene()->Get_MainCharacterController()->Set_MoveState(ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_NONE);
	}
}


/*!****************************************************************************
 @Function		main
 @Input			argc		Number of arguments
 @Input			argv		Command line arguments
 @Return		int			result code to OS
 @Description	Main function of the program
******************************************************************************/
int main(int argc, char **argv)
{
	// Variable set in the message handler to finish the demo
	bool				bDemoDone	= false;

	// X11 variables
	Window				x11Window	= 0;
	Display*			x11Display	= 0;
	long				x11Screen	= 0;
	XVisualInfo*		x11Visual	= 0;
	Colormap			x11Colormap	= 0;

	// EGL variables
	EGLDisplay			eglDisplay	= 0;
	EGLConfig			eglConfig	= 0;
	EGLSurface			eglSurface	= 0;
	EGLContext			eglContext	= 0;
	GLuint	ui32Vbo = 0; // Vertex buffer object handle

    Common::Logger* loggersingleton = new Common::Logger();
    LOGGER->Initialize("tanki", "tanki-debug");

	/*
		EGL has to create a context for OpenGL ES. Our OpenGL ES resources
		like textures will only be valid inside this context
		(or shared contexts).
		Creation of this context takes place at step 7.
	*/
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

	
	Window					sRootWindow;
    XSetWindowAttributes	sWA;
	unsigned int			ui32Mask;
	int						i32Depth;
	int 					i32Width, i32Height;

	// Initializes the display and screen
	x11Display = XOpenDisplay( 0 );
	if (!x11Display)
	{
		printf("Error: Unable to open X display\n");
		goto cleanup;
	}
	x11Screen = XDefaultScreen( x11Display );

	// Gets the window parameters
	sRootWindow = RootWindow(x11Display, x11Screen);
	i32Depth = DefaultDepth(x11Display, x11Screen);
	x11Visual = new XVisualInfo;
	XMatchVisualInfo( x11Display, x11Screen, i32Depth, TrueColor, x11Visual);
	if (!x11Visual)
	{
		printf("Error: Unable to acquire visual\n");
		goto cleanup;
	}
    x11Colormap = XCreateColormap( x11Display, sRootWindow, x11Visual->visual, AllocNone );
    sWA.colormap = x11Colormap;

    // Add to these for handling other events
    sWA.event_mask = StructureNotifyMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
    ui32Mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

	i32Width  = WINDOW_WIDTH  < XDisplayWidth(x11Display, x11Screen) ? WINDOW_WIDTH : XDisplayWidth(x11Display, x11Screen);
	i32Height = WINDOW_HEIGHT < XDisplayHeight(x11Display,x11Screen) ? WINDOW_HEIGHT: XDisplayHeight(x11Display,x11Screen);

	// Creates the X11 window
    x11Window = XCreateWindow( x11Display, RootWindow(x11Display, x11Screen), 0, 0, i32Width, i32Height,
								 0, CopyFromParent, InputOutput, CopyFromParent, ui32Mask, &sWA);
	XMapWindow(x11Display, x11Window);
	XFlush(x11Display);

	/*
		Step 1 - Get the default display.
		EGL uses the concept of a "display" which in most environments
		corresponds to a single physical screen. Since we usually want
		to draw to the main screen or only have a single screen to begin
		with, we let EGL pick the default display.
		Querying other displays is platform specific.
	*/
	eglDisplay = eglGetDisplay((EGLNativeDisplayType)x11Display);

	/*
		Step 2 - Initialize EGL.
		EGL has to be initialized with the display obtained in the
		previous step. We cannot use other EGL functions except
		eglGetDisplay and eglGetError before eglInitialize has been
		called.
		If we're not interested in the EGL version number we can just
		pass NULL for the second and third parameters.
	*/
	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		printf("Error: eglInitialize() failed.\n");
		goto cleanup;
	}

	/*
		Step 3 - Make OpenGL ES the current API.
		EGL provides ways to set up OpenGL ES and OpenVG contexts
		(and possibly other graphics APIs in the future), so we need
		to specify the "current API".
	*/
	eglBindAPI(EGL_OPENGL_ES_API);

	if (!TestEGLError("eglBindAPI"))
	{
		goto cleanup;
	}

	EGLint iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs2, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		printf("Error: eglChooseConfig() failed.\n");
		goto cleanup;
	}

	/*
		Step 6 - Create a surface to draw to.
		Use the config picked in the previous step and the native window
		handle when available to create a window surface. A window surface
		is one that will be visible on screen inside the native display (or
		fullscreen if there is no windowing system).
		Pixmaps and pbuffers are surfaces which only exist in off-screen
		memory.
	*/
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)x11Window, NULL);

    if (!TestEGLError("eglCreateWindowSurface"))
	{
		goto cleanup;
	}

	/*
		Step 7 - Create a context.
	*/
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
	if (!TestEGLError("eglCreateContext"))
	{
		goto cleanup;
	}

	/*
		Step 8 - Bind the context to the current thread and use our
		window surface for drawing and reading.
		Contexts are bound to a thread. This means you don't have to
		worry about other threads and processes interfering with your
		OpenGL ES application.
		We need to specify a surface that will be the target of all
		subsequent drawing operations, and one that will be the source
		of read operations. They can be the same surface.
	*/
	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (!TestEGLError("eglMakeCurrent"))
	{
		goto cleanup;
	}

	
    CWindow::Set_ScreenWidth(WINDOW_WIDTH);
    CWindow::Set_ScreenHeight(WINDOW_HEIGHT);

    CGame::Instance()->Load();

	// Draws a triangle for 800 frames
	for(;;)
	{
	
		glClear(GL_COLOR_BUFFER_BIT);
		if (!TestEGLError("glClear"))
		{
			goto cleanup;
		}

        CGame::Instance()->Update();
		CGame::Instance()->Render();

		if (!TestEGLError("glDrawArrays"))
		{
			goto cleanup;
		}

		/*
			Swap Buffers.
			Brings to the native display the current render surface.
		*/
		eglSwapBuffers(eglDisplay, eglSurface);

		if (!TestEGLError("eglSwapBuffers"))
		{
			goto cleanup;
		}

		// Managing the X11 messages
		int i32NumMessages = XPending( x11Display );
		for( int i = 0; i < i32NumMessages; i++ )
		{
			XEvent	event;
			XNextEvent( x11Display, &event );

			switch( event.type )
			{
			// Exit on mouse click
			case ButtonPress:
        		
        		break;

            case KeyPress:
                //LogDebug(event.xkey.keycode);
                keys[event.xkey.keycode] = true;
                break;

            case KeyRelease:
                //LogDebug(event.xkey.keycode);
                keys[event.xkey.keycode] = false;
                break;

			default:
                //LogDebug(event.type);
				break;
			}
		}

        ProcessInput();

        //usleep(1000);
	}

cleanup:
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) ;
	eglTerminate(eglDisplay);

	/*
		Step 11 - Destroy the eglWindow.
		Again, this is platform specific and delegated to a separate function
	*/
	if (x11Window) XDestroyWindow(x11Display, x11Window);
    if (x11Colormap) XFreeColormap( x11Display, x11Colormap );
	if (x11Display) XCloseDisplay(x11Display);

    delete x11Visual;

	return 0;
}

/******************************************************************************
 End of file (OGLES2HelloTriangle_LinuxX11.cpp)
******************************************************************************/


