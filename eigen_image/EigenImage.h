#pragma once

#include <Eigen/Core>
#include <GL/glew.h> ///< GLFW required (must be before glfw!)
#include <GL/glfw.h> ///< GLFW2 required.
#include "OpenGP/GL/shader_helpers.h"
#include "OpenGP/GL/glfw_helpers.h"

namespace opengp{

template <class PixelType>
class EigenImage : public Eigen::Matrix< PixelType, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor >{  
    /// The type of my Super class
    typedef Eigen::Matrix< PixelType, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor > Super;

public:
    EigenImage(int width, int height) : Super(width, height){}
    int width(){ return Super::cols(); }
    int height(){ return Super::rows(); }
    
protected:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo_vpoint; ///< memory buffer
    GLuint _vbo_vtexcoord; ///< memory buffer
    GLuint _tex; ///< Texture ID

protected:
    void init(){
        ///--- Generic vertex shader
        const GLchar* vshader = R"GLSL(
            #version 330 core
            in vec3 vpoint;
            in vec2 vtexcoord;
            out vec2 uv;
            void main() { 
                uv = vtexcoord;
                gl_Position = vec4(vpoint, 1.0);
            }
        )GLSL";
        
        ///--- Fragment shader for RGB textures
        const GLchar* fshader_rgb = R"GLSL(
            #version 330 core
            out vec3 color;
            in vec2 uv;
            uniform sampler2D tex;
            void main() { color = texture(tex,uv).rgb; }
        )GLSL";

        ///--- Fragment shader for grayscale textures
        const GLchar* fshader_gray = R"GLSL(
            #version 330 core
            out vec3 color;
            in vec2 uv;
            uniform sampler2D tex;
            void main() { color = vec3(texture(tex,uv).r); }
        )GLSL";   
        
        ///--- Pick the right shader    
        const GLchar* fshader = fshader_rgb;
        fshader = (std::is_same<PixelType, Eigen::Vector3f >::value) ? fshader_rgb  : fshader;
        fshader = (std::is_same<PixelType, float >::value) ? fshader_gray : fshader;  
        assert(fshader!=NULL);
                    
        ///--- Compile the shaders
        _pid = opengp::compile_shaders(vshader, fshader);
        if(!_pid) exit(EXIT_FAILURE);       
        glUseProgram(_pid);
        
        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
     
        ///--- Vertex coordinates
        {
            const GLfloat vpoint[] = { /*V0*/ -1.0f, -1.0f, 0.0f, 
                                       /*V1*/ +1.0f, -1.0f, 0.0f, 
                                       /*V2*/ -1.0f, +1.0f, 0.0f,
                                       /*V3*/ +1.0f, +1.0f, 0.0f };        
            ///--- Buffer
            glGenBuffers(1, &_vbo_vpoint);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo_vpoint);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW);
        
            ///--- Attribute
            GLuint vpoint_id = glGetAttribLocation(_pid, "vpoint");
            glEnableVertexAttribArray(vpoint_id);
            glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
        }
        
        ///--- Texture coordinates
        /// NOTE: swaps Y upside down to match top-left image coordinates system
        ///       this way Image(0,0) is the top-left pixel in screen
        {
            const GLfloat vtexcoord[] = { /*v0*/ 1.0f, 0.0f, 
                                          /*v1*/ 1.0f, 1.0f,
                                          /*v2*/ 0.0f, 0.0f, 
                                          /*v3*/ 0.0f, 1.0f };
            
            ///--- Buffer
            glGenBuffers(1, &_vbo_vtexcoord);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo_vtexcoord);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vtexcoord), vtexcoord, GL_STATIC_DRAW);
        
            ///--- Attribute
            GLuint vtexcoord_id = glGetAttribLocation(_pid, "vtexcoord");
            glEnableVertexAttribArray(vtexcoord_id);
            glVertexAttribPointer(vtexcoord_id, 2, GL_FLOAT, 0, 0, (void*) 0);
        }
        
        ///--- Load texture
        {
            glGenTextures(1, &_tex);
            glBindTexture(GL_TEXTURE_2D, _tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            if ( std::is_same<PixelType, Eigen::Vector3f>::value )
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width(), height(), 0, 
                             GL_RGB, GL_FLOAT, this->data());
            else if( std::is_same<PixelType, float>::value )
                glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width(), height(), 0, 
                             GL_RED, GL_FLOAT, this->data());
        }
        
        ///--- Tell shader texture unit to use
        {
            GLuint tex_id = glGetUniformLocation(_pid, "tex");
            glUniform1i(tex_id, 0 /*GL_TEXTURE0*/);
        }
        
        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
    
    void cleanup(){
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &_tex);
        glDeleteBuffers(1, &_vbo_vpoint);
        glDeleteBuffers(1, &_vbo_vtexcoord);
        glDeleteProgram(_pid);
        glDeleteVertexArrays(1, &_vao);
    }
    
    void draw(){
        ///--- Bind
        glUseProgram(_pid);
        glBindVertexArray(_vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _tex);

        ///--- Draw
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        ///--- Unbind
        glBindVertexArray(0);        
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, _tex);
    }

public:
    void show(const char * windowTitle = NULL){
        windowTitle = (windowTitle==NULL) ? "Eigen::Image" : windowTitle;
        opengp::glfwInitWindowSize(width(), height());
        opengp::glfwCreateWindow(windowTitle);
        this->init();
        
        while(glfwGetKey(GLFW_KEY_ESC)!=GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)){
            this->draw();
            glfwSwapBuffers();
        }

        /// Close OpenGL window and terminate GLFW
        glfwTerminate();
        this->cleanup();
    }
};

} // opengp::
