# Locate the GLFW library (version 2.0)
# This module defines the following variables:
# GLFW_LIBRARIES, the name of the library;
# GLFW_INCLUDE_DIRS, where to find GLFW include files.
# GLFW_FOUND, true if library path was resolved
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (GLFW REQUIRED)
# INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIRS})
# ADD_EXECUTABLE (executable ${YOUR_EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARIES})
#
# TODO:
# Lookup for windows
# Allow the user to select to link to a shared library or to a static library.
#
# SEE:
# - https://raw.github.com/progschj/OpenGL-Examples/master/cmake_modules/FindGLFW.cmake
# 

SET( BITS "" )

IF (WIN32)
    IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        SET( BITS "64") 
		SET(LIBPATH ${CMAKE_SOURCE_DIR}/external/glfw/lib/x64)
    ELSE()
		SET(LIBPATH ${CMAKE_SOURCE_DIR}/external/glfw/lib/win32)
    ENDIF()
ELSE()
	SET(LIBPATH ${CMAKE_SOURCE_DIR}/external/glfw/lib/x11)
ENDIF()
FIND_PATH( GLFW_INCLUDE_DIRS GL/glfw.h
    $ENV{GLFWDIR}/include
    /usr/local/include
    /usr/local/X11R6/include
    /usr/X11R6/include
    /usr/X11/include
    /usr/include/X11
    /usr/include
    /opt/X11/include
    /opt/include 
    ${CMAKE_SOURCE_DIR}/external/glfw/include)

FIND_LIBRARY(GLFW_LIBRARIES NAMES glfw${BITS} PATHS
    $ENV{GLFWDIR}/lib
    /usr/local/lib
    /usr/local/X11R6/lib
    /usr/X11R6/lib
    /usr/X11/lib
    /usr/lib/X11
    /usr/lib
    /opt/X11/lib
    /opt/lib
    ${LIBPATH})

#--- Hack for INF3 machines where libglfw.so doesn't exist
# message("SUFFIXES: ${CMAKE_FIND_LIBRARY_SUFFIXES}")
# message("GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
if(GLFW_LIBRARIES)
else()
    #--- Hack to find it on INF machines
    find_file(GLFW_LIBRARIES NAMES libglfw.so.2
        PATHS
        /usr/lib
        ${CMAKE_SOURCE_DIR}/external/glfw/lib/x11)
endif()

SET(GLFW_FOUND "NO")
IF(GLFW_LIBRARIES AND GLFW_INCLUDE_DIRS)
    message(STATUS "Found GLFW: ${GLFW_LIBRARIES}")
    SET(GLFW_FOUND "YES")
ENDIF()
