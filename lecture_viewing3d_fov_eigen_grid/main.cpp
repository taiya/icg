#include "icg_common.h"
#include "_mesh/Mesh.h"

int window_width = 1024;
int window_height = 640;

Mesh mesh;
float theta = 30; //< camera angle

void init(){
    glfwEnable(GLFW_KEY_REPEAT);     
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

        float theta_rad = M_PI/180.0*theta;
        vec3 camera_pos( 0, -2*cos(theta_rad), 2*sin(theta_rad));
        mat4 VIEW = Eigen::lookAt( camera_pos, vec3(0,0,0), vec3(0,0,1) ); //< "z" up on screen
        glUniformMatrix4fv(glGetUniformLocation(pid, "VIEW"), 1, GL_FALSE, VIEW.data());
        
        mat4 PROJ = Eigen::perspective(75.0f, window_width/(float)window_height, 0.1f, 10.0f);
        glUniformMatrix4fv(glGetUniformLocation(pid, "PROJ"), 1, GL_FALSE, PROJ.data());
    glUseProgram(pid);
    
    mesh.draw();
}

/// NOTE: see glfwEnable(GLFW_KEY_REPEAT)
void keyboard(int key, int action){
    if (action==GLFW_PRESS && key==GLFW_KEY_SPACE)
        mesh.wireframe = !mesh.wireframe;
    if (action==GLFW_PRESS && key==GLFW_KEY_UP)
        theta = std::min( theta+1, +89.f );
    if (action==GLFW_PRESS && key==GLFW_KEY_DOWN)
        theta = std::max( theta-1, -89.f );
}

int main(int, char**){
    glfwInitWindowSize(window_width, window_height);
    glfwCreateWindow();
    glfwSetKeyCallback(keyboard);
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    return EXIT_SUCCESS;
}
