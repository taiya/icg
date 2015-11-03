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

void keyboard(int key, int action){
    if(action != GLFW_RELEASE) return; ///< only act on release
    switch(key){
        case '0': break;
        default: break;
    }
}

int main(int, char**){
    glfwInitWindowSize(window_width, window_height);
    glfwCreateWindow();
    glfwDisplayFunc(display);
    glfwSetKeyCallback(keyboard);
    init();
    keyboard(GLFW_KEY_KP_1, 0);
    glfwMainLoop();
    cleanup();
    return EXIT_SUCCESS;
}
