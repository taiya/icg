# STATICALLY LINKED!
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(-DGLEW_STATIC)
# message(STATUS "HERE " ${GLEW_LIBRARIES})

if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
else()
    add_definitions(-DWITH_GLEW)
    list(APPEND COMMON_LIBS ${GLEW_LIBRARIES})
endif()
