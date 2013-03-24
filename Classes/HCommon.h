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

#ifdef TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <pugixml/pugixml.hpp>

#include "PVRTTexture.h"
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
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define M_PI 3.14f
#define M_PI_2 1.57f

#endif
