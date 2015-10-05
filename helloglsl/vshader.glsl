// helloworld/vshader.glsl
#version 330 core 
in vec3 vpoint;
void main(){
    gl_Position = vec4(vpoint, 1.0);
}
