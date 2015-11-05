#include "EigenImage.h"

int main(int, char**){
    using namespace opengp;
    
#if 0
    typedef Eigen::Vector3f vec3;
    EigenImage<vec3> I(512, 512);
    for (int row = 0; row < I.height(); row++){
        for (int col = 0; col < I.width(); col++){
            float r = row/ (float) I.width();
            float g = col/ (float) I.height();
            I(row, col) = vec3(r,g,0);
        }
    }
    I.show();
#else
    EigenImage<float> I(512, 512);
    float T = 10; ///< period
    for (int row = 0; row < I.height(); row++)
        for (int col = 0; col < I.width(); col++)
            I(row,col) = .5f + .5*std::sin( T*2*3.14*row/I.rows() );
    I.show();
#endif
    
    return EXIT_SUCCESS;
}

