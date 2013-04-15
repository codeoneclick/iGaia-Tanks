//
//  HCommon.h
//  iGaia
//
//  Created by Sergey Sergeev on 2/7/13.
//
//

#ifndef HCommon_h
#define HCommon_h

#include "stdlib.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>
#include <future>
#include <mutex>
#include <thread>
#include <set>
#include <queue>
#include <fstream>
#include <strstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include <Rocket/Core/EventListener.h>
#include <Rocket/Core/EventListenerInstancer.h>
#include <Rocket/Core/RocketString.h>
#include <Rocket/Core/FileInterface.h>
#include <Rocket/Core/Platform.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>

#ifdef __APPLE__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <QuartzCore/QuartzCore.h>

#else

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include <pugixml/pugixml.hpp>

#include "PVRTTexture.h"

#include "Box2D.h"

#include "HEnum.h"

typedef signed char i8;
typedef unsigned char ui8;
typedef signed short i16;
typedef unsigned short ui16;
typedef signed int i32;
typedef unsigned int ui32;
typedef unsigned long long ui64;
typedef long long i64;
typedef float f32;

#define TO_RGB(r,g,b) (unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))
#define MAX_VALUE(a,b) (((a) > (b)) ? (a) : (b))

#ifndef __APPLE__

#define M_PI 3.14f
#define M_PI_2 1.57f

#endif

#endif
