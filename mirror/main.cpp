#include "icg_common.h"
#include "FrameBuffer.h"
#include "_floor/Floor.h"
#include "_mesh/Mesh.h"

typedef Eigen::Transform<float,3,Eigen::Affine> Transform;
int window_width = 1280;
int window_height = 720;
FrameBuffer fb(window_width, window_height);
Mesh mesh;
Floor shinyfloor;

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    mesh.init();
    //Set up the framebuffer object to be used as the texture
    //of the shiny floor
    GLuint fb_tex = fb.init();
    shinyfloor.init(fb_tex);
}

void display() {
    glViewport(0,0,window_width,window_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float ratio = window_width / (float) window_height;
    //Turn the bunny to face the camera
    Transform modelTransform = Transform::Identity();
    modelTransform *= Eigen::Translation3f(0, 0, 0.55);
    modelTransform *= Eigen::AngleAxisf(M_PI, vec3::UnitZ());
    modelTransform *= Eigen::AngleAxisf(M_PI / 2.0f, vec3::UnitX());
    mat4 model = modelTransform.matrix();
    mat4 projection = Eigen::perspective(45.0f, ratio, 0.1f, 10.0f);

    //camera movement  
    float time = .5 * glfwGetTime();
    vec3 cam_pos(2*cos(time), 2*sin(time), 2.0f);
    vec3 cam_look(0.0f, 0.0f, 0.0f);
    vec3 cam_up(0.0f, 0.0f, 1.0f);
    mat4 view = Eigen::lookAt(cam_pos, cam_look, cam_up);
    mat4 VP = projection * view;

    // TODO: 1. mirror the camera position about the Z=0 plane
    // 2. create new VP for mirrored camera
    // 3. render the object using the mirrored camera, but not the floor
    // it should be rendered to the framebuffer object (remember bind/unbind)
    
    shinyfloor.draw(VP);
    mesh.draw(model, view, projection);
}

int main(int, char**) {
    glfwInitWindowSize(window_width, window_height);
    glfwCreateWindow("mirror effect and clipping plane");
    glfwDisplayFunc(display);
    init();
    glfwMainLoop();
    return EXIT_SUCCESS;    
}
