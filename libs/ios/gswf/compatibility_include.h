// Dummy header; should get included first into tu-testbed headers.
// This is for manual project-specific configuration.

//
// Some optional general configuration.
//


#define TU_CONFIG_LINK_TO_THREAD 2
#define TU_USE_OGLES
//#define TU_USE_OPENAL

#ifndef GL_BGR
#define GL_BGR GL_BGR_EXT
#endif
#ifndef GL_BGRA
#define GL_BGRA GL_BGRA_EXT
#endif