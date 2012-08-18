

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "X11/Xlib.h"
#include "X11/Xutil.h"


#include "CWindow.h"
#include "CGame.h"

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

	/*
		EGL has to create a context for OpenGL ES. Our OpenGL ES resources
		like textures will only be valid inside this context
		(or shared contexts).
		Creation of this context takes place at step 7.
	*/
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

	// Matrix used for projection model view (PMVMatrix)
	float pfIdentity[] =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	// Fragment and vertex shaders code
	const char* pszFragShader = "\
		void main (void)\
		{\
			gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
		}";

	const char* pszVertShader = "\
		attribute lowp vec4	myVertex;\
		uniform  mat4	myPMVMatrix;\
		void main(void)\
		{\
			gl_Position = myPMVMatrix * myVertex;\
		}";
	/*
		Step 0 - Create a NativeWindowType that we can use it for OpenGL ES output
	*/
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

	/*
		Step 4 - Specify the required configuration attributes.
		An EGL "configuration" describes the pixel format and type of
		surfaces that can be used for drawing.
		For now we just want to use a 16 bit RGB surface that is a
		Window surface, i.e. it will be visible on screen. The list
		has to contain key/value pairs, terminated with EGL_NONE.
	 */
        EGLint pi32ConfigAttribs[5];
        pi32ConfigAttribs[0] = EGL_SURFACE_TYPE;
        pi32ConfigAttribs[1] = EGL_WINDOW_BIT;
        pi32ConfigAttribs[2] = EGL_RENDERABLE_TYPE;
        pi32ConfigAttribs[3] = EGL_OPENGL_ES2_BIT;
        pi32ConfigAttribs[4] = EGL_NONE;

	/*
		Step 5 - Find a config that matches all requirements.
		eglChooseConfig provides a list of all available configurations
		that meet or exceed the requirements given as the second
		argument. In most cases we just want the first config that meets
		all criteria, so we can limit the number of configs returned to 1.
	*/
	EGLint iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
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

	/*
		Step 9 - Draw something with OpenGL ES.
		At this point everything is initialized and we're ready to use
		OpenGL ES to draw something on the screen.
	*/
#if 0
	GLuint uiFragShader, uiVertShader;		// Used to hold the fragment and vertex shader handles
	GLuint uiProgramObject;					// Used to hold the program handle (made out of the two previous shaders

	// Create the fragment shader object
	uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the source code into it
	glShaderSource(uiFragShader, 1, (const char**)&pszFragShader, NULL);

	// Compile the source code
	glCompileShader(uiFragShader);

	// Check if compilation succeeded
	GLint bShaderCompiled;
    glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled)
	{
		// An error happened, first retrieve the length of the log message
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(uiFragShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		// Allocate enough space for the message and retrieve it
		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(uiFragShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		// Displays the error
		printf("Failed to compile fragment shader: %s\n", pszInfoLog);
		delete [] pszInfoLog;
		goto cleanup;
	}

	// Loads the vertex shader in the same way
	uiVertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(uiVertShader, 1, (const char**)&pszVertShader, NULL);
	glCompileShader(uiVertShader);
    glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(uiVertShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(uiVertShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		printf("Failed to compile vertex shader: %s\n", pszInfoLog);
		delete [] pszInfoLog;
		goto cleanup;
	}

	// Create the shader program
    uiProgramObject = glCreateProgram();

	// Attach the fragment and vertex shaders to it
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);

	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
    glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "myVertex");

	// Link the program
    glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);

	if (!bLinked)
	{
		int ui32InfoLogLength, ui32CharsWritten;
		glGetProgramiv(uiProgramObject, GL_INFO_LOG_LENGTH, &ui32InfoLogLength);
		char* pszInfoLog = new char[ui32InfoLogLength];
		glGetProgramInfoLog(uiProgramObject, ui32InfoLogLength, &ui32CharsWritten, pszInfoLog);
		printf("Failed to link program: %s\n", pszInfoLog);
		delete [] pszInfoLog;
		goto cleanup;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	// Sets the clear color.
	// The colours are passed per channel (red,green,blue,alpha) as float values from 0.0 to 1.0
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // clear blue

	// We're going to draw a triangle to the screen so create a vertex buffer object for our triangle
	{
		// Interleaved vertex data
		GLfloat afVertices[] = {	-0.4f,-0.4f,0.0f, // Position
								0.4f ,-0.4f,0.0f,
								0.0f ,0.4f ,0.0f};

		// Generate the vertex buffer object (VBO)
		glGenBuffers(1, &ui32Vbo);

		// Bind the VBO so we can fill it with data
		glBindBuffer(GL_ARRAY_BUFFER, ui32Vbo);

		// Set the buffer's data
		unsigned int uiSize = 3 * (sizeof(GLfloat) * 3); // Calc afVertices size (3 vertices * stride (3 GLfloats per vertex))
		glBufferData(GL_ARRAY_BUFFER, uiSize, afVertices, GL_STATIC_DRAW);
	}
#else
    CWindow::Set_ScreenWidth(WINDOW_WIDTH);
    CWindow::Set_ScreenHeight(WINDOW_HEIGHT);

    CGame::Instance()->Load();
#endif
	// Draws a triangle for 800 frames
	for(;;)
	{
		// Check if the message handler finished the demo
		//if (bDemoDone) break;

		/*
			Clears the color buffer.
			glClear() can also be used to clear the depth or stencil buffer
			(GL_DEPTH_BUFFER_BIT or GL_STENCIL_BUFFER_BIT)
		*/
		glClear(GL_COLOR_BUFFER_BIT);
		if (!TestEGLError("glClear"))
		{
			goto cleanup;
		}
#if 1
        CGame::Instance()->Update();
		CGame::Instance()->Render();
#else
		/*
			Bind the projection model view matrix (PMVMatrix) to
			the associated uniform variable in the shader
		*/

		// First gets the location of that variable in the shader using its name
		int i32Location = glGetUniformLocation(uiProgramObject, "myPMVMatrix");

		// Then passes the matrix to that variable
		glUniformMatrix4fv( i32Location, 1, GL_FALSE, pfIdentity);

		/*
			Enable the custom vertex attribute at index VERTEX_ARRAY.
			We previously binded that index to the variable in our shader "vec4 MyVertex;"
		*/
		glEnableVertexAttribArray(VERTEX_ARRAY);

		// Sets the vertex data to this attribute index
		glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, 0);

		/*
			Draws a non-indexed triangle array from the pointers previously given.
			This function allows the use of other primitive types : triangle strips, lines, ...
			For indexed geometry, use the function glDrawElements() with an index list.
		*/
		glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
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
//		int i32NumMessages = XPending( x11Display );
//		for( int i = 0; i < i32NumMessages; i++ )
//		{
//			XEvent	event;
//			XNextEvent( x11Display, &event );
//
//			switch( event.type )
//			{
//			// Exit on mouse click
//			case ButtonPress:
//        		bDemoDone = true;
//        		break;
//			default:
//				break;
//			}
//		}
	}

	// Frees the OpenGL handles for the program and the 2 shaders
//	glDeleteProgram(uiProgramObject);
//	glDeleteShader(uiFragShader);
//	glDeleteShader(uiVertShader);
//
//	// Delete the VBO as it is no longer needed
//	glDeleteBuffers(1, &ui32Vbo);

	/*
		Step 10 - Terminate OpenGL ES and destroy the window (if present).
		eglTerminate takes care of destroying any context or surface created
		with this display, so we don't need to call eglDestroySurface or
		eglDestroyContext here.
	*/
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


