#version 330 core
out vec3 color;
in vec3 fpoint;
in float vheight; ///< for debug coloring
in float scale; ///< to normalize color range

vec3 Y = vec3(1,1,0);
vec3 G = vec3(0,1,0);

void main() {
    color = mix(Y,G, vheight/scale);
}
