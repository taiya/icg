#include "icg_common.h"
#include "_mesh/Mesh.h"

int window_width = 1024;
int window_height = 640;

Mesh mesh;

void init(){
    glClearColor(1,1,1, /*solid*/1.0 );    
    glEnable(GL_DEPTH_TEST);
    mesh.init();
}

void display(){
    opengp::update_title_fps("Intro. to Computer Graphics");   
    glViewport(0,0,window_width,window_height);    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ///--- Upload viewing matrices externally
    GLuint pid = mesh.getProgramID();
    glUseProgram(pid);
        mat4 MODEL = mat4::Identity();
        glUniformMatrix4fv(glGetUniformLocation(pid, "MODEL"), 1, GL_FALSE, MODEL.data());

        mat4 VIEW = Eigen::lookAt( vec3(1,1,1), vec3(0,0,0), vec3(0,1,0) );
        glUniformMatrix4fv(glGetUniformLocation(pid, "VIEW"), 1, GL_FALSE, VIEW.data());
        
        mat4 PROJ = Eigen::perspective(45.0f, window_width/(float)window_height, 0.1f, 10.0f);
        glUniformMatrix4fv(glGetUniformLocation(pid, "PROJ"), 1, GL_FALSE, PROJ.data());
    glUseProgram(pid);
    
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
