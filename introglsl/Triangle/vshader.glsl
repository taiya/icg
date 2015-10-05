#version 330 core
in vec3 vpoint;

const vec3 COLORS[3] = vec3[](
    vec3(1.0,0.0,0.0),
    vec3(0.0,1.0,0.0),
    vec3(0.0,0.0,1.0));
out vec3 fcolor;
uniform mat4 M;

void main() {
#if 1
    ///--- VERSION1: matrix passed with uniforms
    gl_Position = M*vec4(vpoint, 1.0);  
#else
    ///--- VERSION1: matrix composed in shader
    ///--- Scale
    mat3 S = mat3(.25);
    
    ///--- Rotation 
    mat3 R = mat3(1);
    float alpha = radians(30 /*degrees*/);
    R[0][0] =  cos(alpha);
    R[0][1] =  sin(alpha);
    R[1][0] = -sin(alpha);
    R[1][1] =  cos(alpha);
    
    ///--- Translation
    mat4 T = mat4(1);
    T[3][0] = .5;
    T[3][1] = .5;
    
    ///--- Assemble the Model matrix
    mat4 M = mat4(T)*mat4(S)*mat4(R);
    gl_Position = M*vec4(vpoint, 1.0);
#endif

    fcolor = COLORS[gl_VertexID];
}
