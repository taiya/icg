#version 330 core 
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
    vec4 world = MODEL * vec4(vpoint, 1.0);
    gl_Position = PROJ * VIEW * world;

    //TODO: Calculate the clipping distance and set it to
    //gl_ClipDistance[0]

}
