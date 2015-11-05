#include "icg_common.h"
#include "_mesh/Mesh.h"

int window_width = 640;
int window_height = 640;

Mesh mesh;

void init(){
    glClearColor(1,1,1, /*solid*/1.0 );    
    glEnable(GL_DEPTH_TEST);
    mesh.init();
}

void display(){
    opengp::update_title_fps("lecture_viewing3d");   
    glViewport(0,0,window_width,window_height);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh.draw();
}

void cleanup(){}

int main(int, char**){
    glfwInitWindowSize(window_width, window_height);
    glfwCreateWindow();
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    cleanup();
    return EXIT_SUCCESS;
}
