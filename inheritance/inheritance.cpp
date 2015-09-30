#include <iostream>
#include <vector>
using namespace std;

/// Just to avoid having to import Eigen
class ray3{};
class vec3{};

struct Shape{
    virtual ~Shape(){}
    virtual float hit(ray3 ray) = 0;
};

struct Triangle : public Shape{
    float hit(ray3 ray){
        cout << "Called Triangle::hit()" << endl;
        return 0;
    }
};

struct Sphere  : public Shape{
    float hit(ray3 ray){
        cout << "Called Sphere::hit()" << endl;
        return 0;
    }
};

int main (int argc, char const *argv[]){
    // Shape a; ///< error
    
    ///--- Create geometry
    Triangle t1;
    Sphere s1;
    Sphere s2;
    
    ///--- Create scene
    std::vector<Shape*> scene;
    scene.push_back(&t1);
    scene.push_back(&s1);
    scene.push_back(&s2);

    ///--- A primary ray
    ray3 ray; 

    for(size_t i = 0; i < scene.size(); ++i){
        float t = scene[i]->hit(ray);
        ///< only save smallest "t" and reference 
    }
    
    return 0;
}
