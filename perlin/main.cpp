#include "icg_common.h"

#include "OpenGLImage/EigenVisualizer.h"

using namespace EigenVisualizer;

int main(int, char**){


    //This is a demo code for using the EigenVisualizer namespace
    //TODO: change the following code so we can make a single frequency perlin noise
    RGBImage image(512, 512);

    for (int i = 0; i < 512; ++ i)
    {
        for (int j = 0; j < 512; ++ j)
        {
            image(i, j) = vec3(i/512.0f, j/512.0f, 0);
        }
    }

    showImage(image); 

    return EXIT_SUCCESS;

}

