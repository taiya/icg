#version 330 core
in vec3 fcolor; ///< passed by vshader
out vec3 color; ///< output color

void main() {
    color = fcolor; /// fcolor is interpolated!
}
