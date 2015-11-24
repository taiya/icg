#pragma once
#include "icg_common.h"

class Floor{
protected:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo; ///< memory buffer
    GLuint _tex; ///< Texture ID
    GLuint _tex_mirror; ///< Texture ID of mirror texture
    
public:    
    void init(GLuint tex_mirror = -1){
        ///--- Compile the shaders
        _pid = opengp::load_shaders("_floor/Floor_vshader.glsl", "_floor/Floor_fshader.glsl");
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
        
        ///--- Load texture
        glGenTextures(1, &_tex);
        glBindTexture(GL_TEXTURE_2D, _tex);
        glfwLoadTexture2D("_floor/Floor_texture.tga", 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        _tex_mirror = (tex_mirror==-1)? _tex : tex_mirror;
        
        ///--- Texture uniforms
        GLuint tex_id = glGetUniformLocation(_pid, "tex");
        glUniform1i(tex_id, 0 /*GL_TEXTURE0*/);
        GLuint tex_mirror_id = glGetUniformLocation(_pid, "tex_mirror");
        glUniform1i(tex_mirror_id, 1 /*GL_TEXTURE1*/);
        
        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
    
    void draw(const mat4& MVP){
        glUseProgram(_pid);
        glBindVertexArray(_vao);        
            ///--- Bind textures
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _tex);
            
            ///--- Bind textures
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, _tex_mirror);
            
            ///--- Setup MVP
            GLuint MVP_id = glGetUniformLocation(_pid, "MVP");
            glUniformMatrix4fv(MVP_id, 1, GL_FALSE, MVP.data());   
            
            ///--- Draw
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);        
        glUseProgram(0);
    }
};
