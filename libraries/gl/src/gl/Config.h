//
//  GPUConfig.h
//  libraries/gpu/src/gpu
//
//  Created by Sam Gateau on 12/4/14.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_gpu_GPUConfig_h
#define hifi_gpu_GPUConfig_h

#include <QtCore/QtGlobal>

#if defined(USE_GLES)
// Minimum GL ES version required is 3.2
#define GL_MIN_VERSION_MAJOR 0x03
#define GL_MIN_VERSION_MINOR 0x02
#define GL_DEFAULT_VERSION_MAJOR GL_MIN_VERSION_MAJOR
#define GL_DEFAULT_VERSION_MINOR GL_MIN_VERSION_MINOR
#else
// Minimum desktop GL version required is 4.1
#define GL_MIN_VERSION_MAJOR 0x04
#define GL_MIN_VERSION_MINOR 0x01
#define GL_DEFAULT_VERSION_MAJOR 0x04
#define GL_DEFAULT_VERSION_MINOR 0x05
#endif

#define MINIMUM_GL_VERSION ((GL_MIN_VERSION_MAJOR << 8) | GL_MIN_VERSION_MINOR)

#if defined(USE_GLES)

#if defined(Q_OS_ANDROID)

#include <GLES3/gl32.h>
#include <EGL/egl.h>

#else

#include <glad/glad.h>
#if defined(Q_OS_WIN)
#include <glad/glad_wgl.h>
#endif

#endif

#define GL_DEPTH_COMPONENT32_OES          0x81A7
#define GL_TIME_ELAPSED_EXT               0x88BF
#define GL_TIMESTAMP_EXT                  0x8E28
#define GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#define GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#define GL_CLAMP_TO_BORDER_EXT            0x812D
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF


#else // !defined(USE_GLES)

#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>

#if defined(Q_OS_DARWIN)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/OpenGL.h>
#elif defined(Q_OS_WIN64)
#include <GL/wglew.h>
#endif

#endif // !defined(Q_OS_ANDROID)

// Platform specific code to load the GL functions
namespace gl {
    void initModuleGl();
}

#endif // hifi_gpu_GPUConfig_h
