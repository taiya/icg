#include "icg_common.h"

#include "_quad/Quad.h"
#include "_point/point.h"
#include "_multiline/multiline.h"


int window_width = 1024;
int window_height = 768;

mat4 projection;
mat4 view;
mat4 model;

GLuint _pid_multiline;
GLuint _pid_point;
GLuint _pid_point_selection;

Quad quad;

MultiLine cam_pos_curve;

std::vector<ControlPoint> cam_pos_points;
int selected_point;
int x_last, y_last;
void init(){
    /// Compile the shaders here to avoid the duplication
    _pid_multiline = opengp::load_shaders("_multiline/line_vshader.glsl", "_multiline/line_fshader.glsl");
    if(!_pid_multiline) exit(EXIT_FAILURE);

    _pid_point = opengp::load_shaders("_point/point_vshader.glsl", "_point/point_fshader.glsl");
    if(!_pid_point) exit(EXIT_FAILURE);

    _pid_point_selection = opengp::load_shaders("_point/point_selection_vshader.glsl", "_point/point_selection_fshader.glsl");
    if(!_pid_point_selection) exit(EXIT_FAILURE);

    glClearColor(1,1,1, /*solid*/1.0 );    
    glEnable(GL_DEPTH_TEST);
    quad.init();

    ///--- init cam_pos_curve
    cam_pos_curve.init(_pid_multiline);
    cam_pos_points.push_back(ControlPoint(-0.79, 0.09, 0.2, 0));
    cam_pos_points.push_back(ControlPoint(-0.88, -0.71, 0.2, 1));
    cam_pos_points.push_back(ControlPoint(1.3, -0.8, 0.2, 2));
    cam_pos_points.push_back(ControlPoint(0.71, 0.76, 0.2, 3));
    for (unsigned int i = 0; i < cam_pos_points.size(); i++) {
        cam_pos_points[i].id() = i;
        cam_pos_points[i].init(_pid_point, _pid_point_selection);
    }

    cam_pos_curve.set_points(cam_pos_points[0].position(), cam_pos_points[1].position(), cam_pos_points[2].position(), cam_pos_points[3].position());

    ///--- Setup view-projection matrix
    GLfloat top = 1.0f;
    GLfloat right = (GLfloat)window_width / window_height * top;

    projection = Eigen::ortho(-right, right, -top, top, -10.0f, 10.0f);

    vec3 cam_pos(0.0f, 0.0f, 2.0f);
    vec3 cam_look(0.0f, 0.0f, 0.0f);
    vec3 cam_up(0.0f, 1.0f, 0.0f);

    view = Eigen::lookAt(cam_pos, cam_look, cam_up);
    model = mat4::Identity();
    selected_point = -1;
    x_last = 0;
    y_last = 0;
}

bool unproject (int mouse_x, int mouse_y, vec3 &p) {
    ///---This only works with the specific projection, model and view matrices defined in init().
    p[0] =  ((float)mouse_x - (float) window_width / 2.0f) / (float) window_height / 0.5;
    p[1] =  ((float) window_height/2 - (float) mouse_y) / (float) window_height / 0.5;
    return true;
}

void display(){
    opengp::update_title_fps("shading");   
    glViewport(0,0,window_width,window_height);
        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < cam_pos_points.size(); i++) {
        cam_pos_points[i].draw(model, view, projection);
    }
    cam_pos_curve.draw(model, view, projection);
}

void render_selection() {
    glViewport(0,0,window_width,window_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < cam_pos_points.size(); i++) {
        cam_pos_points[i].draw_selection(model, view, projection);
    }
}

void selection_button(int button, int action) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int x = 0, y = 0;
        glfwGetMousePos(&x, &y);
        x_last = x; y_last = y;
        //render the image with color code
        render_selection();

        glFlush();
        glFinish();
        //picking pixel
        unsigned char res[4];
        glReadPixels(x, window_height - y, 1,1,GL_RGBA, GL_UNSIGNED_BYTE, &res);
        selected_point = res[0];

        if (selected_point >= 0 && selected_point < cam_pos_points.size())
            cam_pos_points[selected_point].selected() = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        if (selected_point >= 0 && selected_point < cam_pos_points.size()) {
            cam_pos_points[selected_point].selected() = false;

        int x = 0, y = 0;
        glfwGetMousePos(&x, &y);
        //if the mouse is not moved at all, don't bother redraw
        if (x != x_last || y != y_last) {
        //caculate the world coordiante from the pixel coordinate on screen
        unproject(x, y, cam_pos_points[selected_point].position());
        cam_pos_curve.set_points(cam_pos_points[0].position(),
                cam_pos_points[1].position(),
                cam_pos_points[2].position(),
                cam_pos_points[3].position());
            }
        }
        selected_point = -1;
    }
}

void mousemove(int x, int y)
{

    //TODO: make the curve change while holding down a mouse button and
    //move the mouse!

}

void keyboard(int key, int action){
    if(action != GLFW_RELEASE) return; ///< only act on key release
    switch(key){
        default:
            break;
    }
}

void cleanup(){
    glDeleteProgram(_pid_multiline);
    glDeleteProgram(_pid_point);
    glDeleteProgram(_pid_point_selection);
}

int main(int, char**){
    glfwInitWindowSize(window_width, window_height);
    glfwCreateWindow();
    glfwDisplayFunc(display);
    glfwSetKeyCallback(keyboard);
    glfwSetMouseButtonCallback(selection_button);
    glfwSetMousePosCallback(mousemove);
    init();
    glfwMainLoop();
    cleanup();
    return EXIT_SUCCESS;
}
