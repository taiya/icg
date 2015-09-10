# Build configuration file for "Intro to Graphics"
#
#--- To understand its content: 
#   http://www.cmake.org/cmake/help/syntax.html
#   http://www.cmake.org/Wiki/CMake_Useful_Variables
#

#--- This is how you show a status message in the build system
message(STATUS "Intro to Graphics - Loading Common Configuration")

#--- Tell CMake he'll be able to include ".cmake" configurations 
# files in the folder where the current file is located
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

#--- Common headers/libraries for all the exercises
include_directories(${CMAKE_CURRENT_LIST_DIR})

#--- Make headers in common directory visible in the IDE
file(GLOB_RECURSE COMMON_DIR_HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.h")
add_custom_target(common_headers SOURCES ${COMMON_DIR_HEADERS})

#--- Configures compiler for C++11
if(EXISTS "/usr/bin/icc")
    #--- If intel compiler is installed use it (ICC is already c++11 compliant)
    message(STATUS "Using ICC Intel Compiler.")
    set(CMAKE_CC_COMPILER "/usr/bin/icc")
    set(CMAKE_CXX_COMPILER "/usr/bin/icc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(UNIX)
    if(NOT APPLE)
        # Enable c++11 for GCC 
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        # Clang in OSX supports partially c++11 through extensions
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-extensions")        
    endif()
elseif(WIN32)    
    # MSVC12 supports c++11 natively
endif()



