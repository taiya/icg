#pragma once
#include "Quad.h"


namespace EigenVisualizer
{
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> GreyLevelImage;
    typedef Eigen::Matrix<Eigen::Vector3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RGBImage;

    void showImage(GreyLevelImage & image, const char * windowTitle = NULL)
    {
        unsigned int width = image.rows();
        unsigned int height = image.cols();

        _Quad _quad;
        glfwInitWindowSize(width, height);
        if (windowTitle != NULL)
        {
            glfwCreateWindow(windowTitle);
        } else
        {
            glfwCreateWindow("Image");
        }
        //After the openGL context is set up, copy data into an openGL texture
        _quad.init();
        _quad.loadTextureR32F(image.data(), width, height);

        while(glfwGetKey(GLFW_KEY_ESC)!=GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)){
            _quad.draw();
            glfwSwapBuffers();
        }

        /// Close OpenGL window and terminate GLFW
        glfwTerminate();
        _quad.cleanup();

    }

    void showImage(RGBImage & image, const char * windowTitle = NULL)
    {
        unsigned int width = image.rows();
        unsigned int height = image.cols();

        _Quad _quad;
        glfwInitWindowSize(width, height);
        if (windowTitle != NULL)
        {
            glfwCreateWindow(windowTitle);
        } else
        {
            glfwCreateWindow("Image");
        }
        //After the openGL context is set up, copy data into an openGL texture
        _quad.init();
        _quad.loadTextureRGB32F(image.data(), width, height);

        while(glfwGetKey(GLFW_KEY_ESC)!=GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)){
            _quad.draw();
            glfwSwapBuffers();
        }

        /// Close OpenGL window and terminate GLFW
        glfwTerminate();
        _quad.cleanup();
    }
}
