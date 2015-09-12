if(UNIX) # Mac or Linux
    # OpenCV found through PkgConfig
    find_package(PkgConfig)
    if(PKGCONFIG_FOUND)
        pkg_check_modules(OPENCV opencv)
        list(APPEND COMMON_LIBS ${OPENCV_LDFLAGS})
        include_directories(${OPENCV_INCLUDE_DIRS})
        if(OPENCV_FOUND)
            add_definitions(-DWITH_OPENCV)
        endif()
    endif()

elseif(WIN32)
    #--- PRE-COMPILED STATIC LIBRARIES
    include_directories("${CMAKE_SOURCE_DIR}/external/OpenCV/include")

    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")

    set(CV_CORE 
        optimized ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/opencv_core2411.lib
        debug ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/opencv_core2411d.lib)
    set(CV_GUI
        optimized ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/opencv_highgui2411.lib
        debug ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/opencv_highgui2411d.lib)
    set(ZLIB
        optimized ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/zlib.lib
        debug ${CMAKE_SOURCE_DIR}/external/OpenCV/lib/zlibd.lib)

    if(NOT COMMON_LIBS)
        set(COMMON_LIBS ${CV_CORE} ${CV_GUI} ${ZLIB})
    else()
        list(APPEND ${COMMON_LIBS} ${CV_CORE})
        list(APPEND ${COMMON_LIBS} ${CV_GUI})
        list(APPEND ${COMMON_LIBS} ${ZLIB})
    endif()
    add_definitions(-DWITH_OPENCV)

    # if you want to use your own libraries
#    include(FindOpenCV)
#    if(OpenCV2_FOUND)
#        list(APPEND COMMON_LIBS ${OpenCV2_LIBRARIES})
#        include_directories(${OpenCV2_INCLUDE_DIRS})
#        add_definitions(-DWITH_OPENCV)
#    else()
#        message(ERROR " Could not find OpenCV")
#    endif()
else()
    message(ERROR " Unknown platform.")
endif()
