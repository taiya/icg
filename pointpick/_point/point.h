#pragma once
#include "icg_common.h"

class ControlPoint {
public:
    ControlPoint() {
        _p = vec3(0.0, 0.0, 0.0);
        _id = 0;
        _selected = false;
    }

    ControlPoint(float x, float y, float z, unsigned int id) {
        _p = vec3(x, y, z);
        _id = id;
        _selected = false;
    }

    void init(GLuint pid, GLuint pid_selection) {
        ///--- Set the (compiled) shaders
        _pid = pid;
        _pid_selection = pid_selection;

        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &_vao);
    }

    void draw(const mat4& model, const mat4& view, const mat4& projection) {
        glUseProgram(_pid);
        glBindVertexArray(_vao);

        ///--- Load position
        GLint pos_id = glGetUniformLocation(_pid, "pos");
        glUniform3fv(pos_id, 1, _p.data());

        ///--- Load selection
        GLint sel_id = glGetUniformLocation(_pid, "selected");
        glUniform1i(sel_id, _selected);

        ///--- Setup MVP
        mat4 MVP = projection*view*model;
        GLint MVP_id = glGetUniformLocation(_pid, "mvp");
        assert(MVP_id >= 0);
        glUniformMatrix4fv(MVP_id, 1, GL_FALSE, MVP.data());

        ///--- Draw
        glEnable(GL_PROGRAM_POINT_SIZE);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisable(GL_PROGRAM_POINT_SIZE);

        glBindVertexArray(0);
        glUseProgram(0);
    }

    void draw_selection(const mat4& model, const mat4& view, const mat4& projection) {
        glUseProgram(_pid_selection);
        glBindVertexArray(_vao);

        ///--- Load position
        GLint pos_id = glGetUniformLocation(_pid_selection, "pos");
        glUniform3fv(pos_id, 1, _p.data());

        GLint code_id = glGetUniformLocation(_pid_selection, "code");
        glUniform1i(code_id, _id);

        ///--- Setup MVP
        mat4 MVP = projection*view*model;
        GLint MVP_id = glGetUniformLocation(_pid_selection, "mvp");
        assert(MVP_id >= 0);
        glUniformMatrix4fv(MVP_id, 1, GL_FALSE, MVP.data());

        ///--- Draw
        glEnable(GL_PROGRAM_POINT_SIZE);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisable(GL_PROGRAM_POINT_SIZE);

        glBindVertexArray(0);
        glUseProgram(0);
    }

public:
    vec3& position() {return _p;}
    unsigned int &id() {return _id;}
    bool &selected() {return _selected;}

private:
    vec3 _p;
    unsigned int _id;
    bool _selected;

    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID
    GLuint _pid_selection;
    GLuint _vbo; ///< memory buffer
};
