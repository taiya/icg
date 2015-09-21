#--- OPENGP
find_package(OpenGP REQUIRED)
include_directories(${OpenGP_INCLUDE_DIRS})
add_definitions(-DHEADERONLY)
add_definitions(-DUSE_EIGEN)
if(NOT OPENGP_FOUND)
    message(ERROR "OPENGP not found!")
else()
    message(STATUS "OPENGP: ${OpenGP_INCLUDE_DIRS}")
    add_definitions(-DWITH_OPENGP)
endif()

#--- On UNIX|APPLE you can do "make update_opengp" to update
if(CMAKE_HOST_UNIX)
    add_custom_target( update_opengp
        COMMAND rm -rf OpenGP
        COMMAND svn checkout https://github.com/OpenGP/OpenGP/trunk/src/OpenGP
        COMMAND rm -rf OpenGP/.svn
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/OpenGP/include
        COMMENT "Updating OpenGP ${CMAKE_SOURCE_DIR}")
endif()
