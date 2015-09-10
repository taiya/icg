#pragma once

///--- Standard library IO
#include <iostream>
#include <cassert>

///--- On some OSs the exit flags are not defined
#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 1
#endif

///--- Load OpenGL here (cross platform)
#ifdef WITH_GLEW
    #include <GL/glew.h> ///< must be before glfw
#endif

#ifdef WITH_GLFW
    #include <GL/glfw.h>
#endif

///--- Linux needs extensions for framebuffers
#ifdef WITH_OPENGL
    #if __unix__
        #define GL_GLEXT_PROTOTYPES 1
        #include <GL/gl.h>
        #include <GL/glext.h>
    #endif
#endif

///--- We use Eigen for linear algebra
#ifdef WITH_EIGEN
    #include <Eigen/Dense>
    typedef Eigen::Vector2f vec2;
    typedef Eigen::Vector3f vec3;
    typedef Eigen::Vector4f vec4;
    typedef Eigen::Matrix4f mat4;
    typedef Eigen::Matrix3f mat3;
#endif

#if defined(WITH_EIGEN) && defined(WITH_OPENGL)
    #include <OpenGP/GL/EigenOpenGLSupport3.h>
    /// We use a modified (to support OpenGL3) version of the Eigen OpenGL module 
    /// @see http://eigen.tuxfamily.org/dox/unsupported/group__OpenGLSUpport__Module.html
    // #include <Eigen/OpenGL3Support>
#endif

///--- Shader compiling utilities
#if defined(WITH_OPENGL) && defined(WITH_OPENGP)
    #include "OpenGP/GL/shader_helpers.h"
#endif 

///--- Utilities to simplify glfw setup
#if defined(WITH_OPENGP) && defined(WITH_GLFW)
    #include <OpenGP/GL/glfw_helpers.h>
    #include <OpenGP/GL/glfw_trackball.h>
#endif

///--- For mesh I/O we use OpenGP
#ifdef WITH_OPENGP
    #include <OpenGP/Surface_mesh.h>
    using namespace opengp; ///< yes, pollution :)
#endif

///--- GL Error checking
#ifdef WITH_OPENGL
    #include "check_error_gl.h"
#endif

#ifdef WITH_OPENCV
    #include "opencv2/core/core.hpp"       ///< cv::Mat
    #include "opencv2/highgui/highgui.hpp" ///< cv::imShow
#endif

///--- These namespaces assumed by default
using namespace std;
