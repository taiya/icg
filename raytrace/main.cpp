#include "icg_common.h"
#include <vector>

#ifndef WITH_OPENCV
    #error OpenCV required for this exercise
#endif

struct MyColor{
    uchar b,g,r; ///< note BGR instead of RGB to conform to OpenCV
    MyColor(uchar r, uchar g, uchar b) : r(r), g(g), b(b){}
    static MyColor RED(){ return MyColor(255,0,0); }
    static MyColor WHITE(){ return MyColor(255,255,255); }
    static MyColor BLACK(){ return MyColor(0, 0, 0); }    
};

struct MyImage{
    /// Data (not private for convenience)
    int cols = 640;
    int rows = 480;
    ///  Channel with [0..255] range image (aka uchar)
    cv::Mat image = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(255,255,255));

    /// Allows to set image color as image(row,col) = MyColor(r,g,b);
    MyColor& operator()(int row, int col){
        assert(row>=0 && row<rows);
        assert(col>=0 && col<cols);
        return image.at<MyColor>(row,col);
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
};


int main(int, char**){
    MyImage image;
    
    /// TODO: define camera position and sphere position here

    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {
            if(row>100 && row<200 && col>200 && col<500) image(row,col) = MyColor::RED();
            if(row>140 && row<240 && col>240 && col<340) image(row,col) = MyColor(0,0,255);
       }
    }
    ////////////////////////////////////////////////
    image.show();
    image.save("output.png");

    return EXIT_SUCCESS;
}
