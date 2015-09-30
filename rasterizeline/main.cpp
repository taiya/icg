#include "icg_common.h"
#include <Eigen/Geometry>

#include <cmath>

#ifndef WITH_OPENCV
    #error OpenCV required for this exercise
#endif

typedef cv::Vec3b Colour;
Colour red() { return Colour(255, 0, 0); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }

/// Rays and vectors represented with Eigen
typedef Eigen::Vector3f vec3;
typedef Eigen::Vector2f vec2;
typedef Eigen::ParametrizedLine<float, 3> ray3;

struct MyImage{
    /// Data (not private for convenience)
    int cols = 640;
    int rows = 480;
    ///  Channel with [0..255] range image (aka uchar)
    cv::Mat image = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(255,255,255));

    Colour& operator()(int row, int col)
    {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        return image.at<cv::Vec3b>(cv::Point(col, row));
    }

    /// Displays the image and pauses program execution (until key pressed)
    void show(){
        /// Display the image
        cv::imshow("image", image);
        cv::waitKey(0);
    }

    /// Use files with "*.png" extension
    void save(const std::string& filename){
        cv::imwrite(filename, image);
    }

    void ImageCordBound(int & xCord, int & yCord)
    {
        if (xCord < 0) xCord = 0;
        if (xCord >= cols) xCord = cols - 1;
        if (yCord < 0) yCord = 0;
        if (yCord >= rows) yCord = rows -1;
    }
};

float LineEquation(const vec2 & p0, const vec2 & p1, float x, float y)
{
    //compute the implicit line equation -- four terms
    //(y0 - y1) x + (x1 - x0) y + x0y1 -x1y0
}

int main(int, char**){

    MyImage image;
    
    //Set up parameters for the line segment 
    vec2 lineStart(100, 200);
    vec2 lineEnd(500, 220);   
    //Line drawing - midpoint algorithm
    //determine if we do a x-loop or y-loop
    //TODO: Rasterize the line using the mid-point algorithm
    
    image.show();
    // image.save("output.png"); ///< Does not work on Windows!

    return EXIT_SUCCESS;
}
