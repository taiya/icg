#include "icg_common.h"

using namespace std;
using namespace opengp;

/// Vertex position of the triangle
const GLfloat vpoint[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,};

void init(){
    ///--- Sets background color
    glClearColor(/*gray*/ .937,.937,.937, /*solid*/1.0 );
    
    ///--- Compile the shaders
    GLuint programID = opengp::load_shaders("vshader.glsl", "fshader.glsl");
    if(!programID) exit(EXIT_FAILURE);
    glUseProgram(programID);
    
    ///--- Setup vertex array
    /// vertex arrays wrap buffers & attributes together
    /// creating it is mandatory in newer OpenGL versions
    GLuint VertexArrayID;
    glGenVertexArrays(ONE, &VertexArrayID);
    glBindVertexArray(VertexArrayID);  
    
    ///--- Generate memory for vertexbuffer
    GLuint vertexbuffer; 
    glGenBuffers(ONE, &vertexbuffer); 
    /// The subsequent commands will affect the specified buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); 
    /// Pass the vertex positions to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW); 
   
    ///--- Creates Vertex Attribute to store Vertex Positions
    GLuint vpoint_id = glGetAttribLocation(programID, "vpoint");
    glEnableVertexAttribArray(vpoint_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0 /*buffer offset*/, 3 /*#vertices*/); 
}

int main(int, char**){
    /// GLFW Initialization
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return EXIT_FAILURE;
    }
    
    /// Hint GLFW that we would like an OpenGL 3 context (at least)
    /// http://www.glfw.org/faq.html#41__how_do_i_create_an_opengl_30_context
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /// Attempt to open the window: fails if required version unavailable
    /// @note some Intel GPUs do not support OpenGL 3.2
    /// @note update the driver of your graphic card
    if( !glfwOpenWindow(512, 512, 0,0,0,0, 32,0, GLFW_WINDOW ) ){
        fprintf( stderr, "Failed to open OpenGL 3.2 GLFW window.\n" );
        glfwTerminate();
        return EXIT_FAILURE;
    }
   
	/// GLEW Initialization (must have a context)
	glewExperimental = true; ///< 
	if( glewInit() != GLEW_NO_ERROR ){
		fprintf( stderr, "Failed to initialize GLEW\n"); 
        return EXIT_FAILURE;
	}

    /// Set window title
    glfwSetWindowTitle("helloglsl");
    std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;
    
    /// Initialize our OpenGL program
    init();
    
    /// Render loop & keyboard input
    while(glfwGetKey(GLFW_KEY_ESC)!=GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)){
        display();
        glfwSwapBuffers();
    }
    
    /// Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit( EXIT_SUCCESS );
}
