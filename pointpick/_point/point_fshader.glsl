#version 330 core

uniform bool selected;

out vec3 color;

void main(){
    if (selected)
        color = vec3(0.0, 1.0, 0.0);
    else
        color = vec3(1.0, 0.0, 0.0);
}
