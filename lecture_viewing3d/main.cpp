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
    
    ///--- Setup view-projection matrix
    float ratio = window_width / (float) window_height;
    static mat4 projection = Eigen::perspective(45.0f, ratio, 0.1f, 10.0f);
    vec3 cam_pos(2.0f, 2.0f, 2.0f);
    vec3 cam_look(0.0f, 0.0f, 0.0f);
    vec3 cam_up(0.0f, 0.0f, 1.0f);
    mat4 view = Eigen::lookAt(cam_pos, cam_look, cam_up);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh.draw(mat4::Identity(), view, projection);
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
