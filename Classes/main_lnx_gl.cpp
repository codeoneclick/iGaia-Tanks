
#include <glf/glf.hpp>
#include <glm/glm.hpp>


#include "CWindow.h"
#include "CGame.h"

#include "Common.h"

#include <memory>

namespace Settings
{
    int const SIZE_WIDTH(960);
	int const SIZE_HEIGHT(640);
	int const MAJOR_VERSION(3);
	int const MINOR_VERSION(0);
}

namespace
{
    glf::window Window(glm::ivec2(Settings::SIZE_WIDTH,Settings::SIZE_HEIGHT));
}

// Fragment and vertex shaders code
	const char* pszFragShader = "\
		void main (void)\
		{\
			gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
		}";

	const char* pszVertShader = "\
		attribute  vec4	myVertex;\
		uniform  mat4	myPMVMatrix;\
		void main(void)\
		{\
			gl_Position = myPMVMatrix * myVertex;\
		}";

    	float pfIdentity[] =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

        static const GLuint VERTEX_ARRAY = 0;

        GLuint	ui32Vbo = 0; // Vertex buffer object handle
        GLuint vertexArray = 0;
        GLuint uiProgramObject;					// Used to hold the program handle (made out of the two previous shaders

bool initDebugOutput()
{
	bool Validated(true);

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glDebugMessageCallbackARB(&glf::debugOutput, NULL);

	return Validated;
}

bool initProgram()
{
	bool Validated = true;

    CWindow::Set_ScreenWidth(Settings::SIZE_WIDTH);
    CWindow::Set_ScreenHeight(Settings::SIZE_HEIGHT);

    glf::checkError("initProgram");

    CGame::Instance()->Load();

#if 0

    GLuint uiFragShader, uiVertShader;		// Used to hold the fragment and vertex shader handles
	
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
		return false;
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
		return false;
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
		return false;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	// Sets the clear color.
	// The colours are passed per channel (red,green,blue,alpha) as float values from 0.0 to 1.0
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // clear blue

	// We're going to draw a triangle to the screen so create a vertex buffer object for our triangle
	{
#if 1
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

#else
        GLfloat* vrt = new GLfloat[3 * 3];
        
        vrt[0] = -0.4f;
        vrt[1] = -0.4f;
        vrt[2] =  0.0f;
        
        vrt[3] =  0.4f;
        vrt[4] =  -0.4f;
        vrt[5] =  0.0f;
        
        vrt[6] =  0.0f;
        vrt[7] =  0.4f;
        vrt[8] =  0.0f;
        
        glGenBuffers(1, &ui32Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, ui32Vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * 3 * 4, vrt, GL_STATIC_DRAW);

        //glGenVertexArrays(1, &vertexArray);
        //glBindVertexArray(vertexArray);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        //glBindVertexArray(0);

        delete[] vrt;
#endif


	}
#endif

    
	return Validated && glf::checkError("initProgram");
}

bool begin()
{
	bool Validated = glf::checkGLVersion(Settings::MAJOR_VERSION, Settings::MINOR_VERSION);

	glEnable(GL_DEPTH_TEST);

	if(Validated && glf::checkExtension("GL_ARB_debug_output"))
		Validated = initDebugOutput();
	if(Validated)
		Validated = initProgram();

	return Validated && glf::checkError("begin");
}

bool end()
{
	return glf::checkError("end");
}

void display()
{
   	/*float Depth(1.0f);
	glClearBufferfv(GL_DEPTH, 0, &Depth);
	glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f)[0]);*/


    glClear(GL_COLOR_BUFFER_BIT);
    
    CGame::Instance()->Update();
	CGame::Instance()->Render();
#if 0
    // First gets the location of that variable in the shader using its name
	int i32Location = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
e = glf::checkError("display");
		// Then passes the matrix to that variable
	glUniformMatrix4fv( i32Location, 1, GL_FALSE, pfIdentity);
e = glf::checkError("display");
		/*
			Enable the custom vertex attribute at index VERTEX_ARRAY.
			We previously binded that index to the variable in our shader "vec4 MyVertex;"
		*/
	glEnableVertexAttribArray(VERTEX_ARRAY);
e = glf::checkError("display");
		// Sets the vertex data to this attribute index

	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, 0);
e = glf::checkError("display");
		/*
			Draws a non-indexed triangle array from the pointers previously given.
			This function allows the use of other primitive types : triangle strips, lines, ...
			For indexed geometry, use the function glDrawElements() with an index list.
		*/
	glDrawArrays(GL_TRIANGLES, 0, 3);

#endif


    glf::checkError("display");

	glf::swapBuffers();
}

int main(int argc, char* argv[])
{
    new Common::Logger();
    LOGGER->Initialize("Tanki", "Debug");

	return glf::run(
		argc, argv,
		glm::ivec2(Settings::SIZE_WIDTH, Settings::SIZE_HEIGHT),
		/*WGL_CONTEXT_ES2_PROFILE_BIT_EXT,*/
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        /*WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,*/ Settings::MAJOR_VERSION,
		Settings::MINOR_VERSION);
}