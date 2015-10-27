#include "icg_common.h"
#include "Quad.h"


typedef Eigen::Transform<float,3,Eigen::Affine> Transform;


const int SUN_ROT_PERIOD = 30;        
const int EARTH_ROT_PERIOD = 4;       
const int MOON_ROT_PERIOD = 8;       
const int EARTH_ORBITAL_PERIOD = 10; 
const int MOON_ORBITAL_PERIOD = 5;   
const int SPEED_FACTOR = 1;
    
Quad sun;
Quad earth;
Quad moon;

void init(){
    glClearColor(/*white*/ 1.0f,1.0f,1.0f, /*solid*/1.0 );

    sun.init("sun.tga");
    earth.init("earth.tga");
    moon.init("moon.tga");
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();


    //TODO: Set up the transform hierarchies for the three objects!

    Transform sun_M = Transform::Identity();
    sun.draw(sun_M.matrix());
    Transform earth_M = Transform::Identity();
    earth.draw(earth_M.matrix());
    Transform moon_M = Transform::Identity();
    moon.draw(moon_M.matrix());
}

int main(int, char**){
    glfwInitWindowSize(512, 512);
    glfwCreateWindow("planets");
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();


    sun.cleanup();
    earth.cleanup();
    moon.cleanup();

    return EXIT_SUCCESS;
}
