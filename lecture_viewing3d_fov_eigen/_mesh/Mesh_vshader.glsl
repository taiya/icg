#version 330 core 
uniform float time;
in vec3 vpoint;
in vec3 vnormal;

out vec3 fpoint; ///< for debug
out vec3 fnormal_cam;

///--- Uploaded by Eigen in C++
uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;

void main() {          
    fpoint = vpoint + .5; ///< For coloring Debug [0,1]^3 
    fnormal_cam = inverse( transpose( mat3(VIEW * MODEL) )) * vnormal; 
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint, 1.0);
}
