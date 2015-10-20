#pragma once
#include "icg_common.h"

class ScreenQuad{
protected:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo; ///< memory buffer
    GLuint _tex; ///< Texture ID
public:
    void init(GLuint texture){ 
        
        ///--- Compile the shaders
        _pid = opengp::load_shaders("_screenquad/ScreenQuad_vshader.glsl", "_screenquad/ScreenQuad_fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);       
        glUseProgram(_pid);
        
        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
     
        ///--- Vertex coordinates
        {
            const GLfloat vpoint[] = { /*V1*/ -1.0f, -1.0f, 0.0f, 
                                       /*V2*/ +1.0f, -1.0f, 0.0f, 
                                       /*V3*/ -1.0f, +1.0f, 0.0f,
                                       /*V4*/ +1.0f, +1.0f, 0.0f };        
            ///--- Buffer
            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW);
        
            ///--- Attribute
            GLuint vpoint_id = glGetAttribLocation(_pid, "vpoint");
            glEnableVertexAttribArray(vpoint_id);
            glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
        }
        
        ///--- Texture coordinates
        {
            const GLfloat vtexcoord[] = { /*V1*/ 0.0f, 0.0f, 
                                          /*V2*/ 1.0f, 0.0f, 
                                          /*V3*/ 0.0f, 1.0f,
                                          /*V4*/ 1.0f, 1.0f}; 
            
            ///--- Buffer
            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vtexcoord), vtexcoord, GL_STATIC_DRAW);
        
            ///--- Attribute
            GLuint vtexcoord_id = glGetAttribLocation(_pid, "vtexcoord");
            glEnableVertexAttribArray(vtexcoord_id);
            glVertexAttribPointer(vtexcoord_id, 2, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
        }
        
        ///--- Load/Assign texture
        this->_tex = texture;
        GLuint tex_id = glGetUniformLocation(_pid, "tex");
        glUniform1i(tex_id, 0 /*GL_TEXTURE0*/);
    
        
        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
       
    void cleanup(){
        // TODO cleanup
    }
    
    void draw(){
        glUseProgram(_pid);
        glBindVertexArray(_vao);      
            glUniform1f(glGetUniformLocation(_pid, "tex_width"), _width);
            glUniform1f(glGetUniformLocation(_pid, "tex_height"), _height); 
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _tex);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);        
        glBindVertexArray(0);        
        glUseProgram(0);
    }
};
