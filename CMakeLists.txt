cmake_minimum_required(VERSION 2.8)
project(icg)

#--- Load the common ICG configuration
include(common/config.cmake)
include(common/Eigen.cmake)
include(common/OpenCV.cmake)
include(common/OpenGP.cmake)

#--- OpenGL configuration
include(common/OpenGL.cmake)
include(common/GLEW.cmake)
include(common/GLFW.cmake)

#--- Subprojects
#add_subdirectory(introcpp)
#add_subdirectory(inheritance)
#add_subdirectory(raytrace)
#add_subdirectory(trimeshio)
#add_subdirectory(rasterizeline)
#add_subdirectory(rasterizetriangle)
#add_subdirectory(helloglsl)
#add_subdirectory(introglsl)
#add_subdirectory(planets)
#add_subdirectory(pointpick)
#add_subdirectory(framebuffer2d)
#add_subdirectory(lecture_viewing3d)
#add_subdirectory(perlin)
#add_subdirectory(lecture_viewing3d_fov)
#add_subdirectory(lecture_viewing3d_fov_eigen)
#add_subdirectory(eigen_image)
#add_subdirectory(lecture_viewing3d_fov_eigen_grid)
add_subdirectory(mirror)
