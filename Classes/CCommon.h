//
//  CCommon.h
//  iGaia
//
//  Created by Sergey Sergeev on 8/31/12.
//
//

#ifndef iGaia_CCommon_h
#define iGaia_CCommon_h

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SAFE_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

#include <iostream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "CLogger.h"

#endif
