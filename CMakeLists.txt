cmake_minimum_required(VERSION 2.8)
project(icg)

#--- Load the common ICG configuration
include(common/config.cmake)
include(common/Eigen.cmake)
include(common/OpenCV.cmake)
include(common/OpenGP.cmake)

#--- Subprojects
add_subdirectory(introcpp)
add_subdirectory(raytrace)
add_subdirectory(trimeshio)
