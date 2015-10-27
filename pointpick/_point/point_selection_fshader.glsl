#version 330 core

uniform int code;

out vec3 color;

void main(){

    if (code < 0) {
        color = vec3(1.0, 0.0, 0.0);
    } else {
        color = vec3(code/255.0, 0, 0);
    }
}
