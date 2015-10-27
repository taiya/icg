#version 330 core
out vec3 color;
in vec3 fpoint;

vec3 R = vec3(1,0,0);
vec3 G = vec3(0,1,0);

void main() {
    color = mix(R,G,fpoint[2]);
    // color = COLORS[int( mod(gl_PrimitiveID,6) )];
}
