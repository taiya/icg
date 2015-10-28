#version 330 core
out vec3 color;
in vec3 fpoint;
in vec3 fnormal_cam;

vec3 R = vec3(1,0,0);
vec3 G = vec3(0,1,0);
vec3 B = vec3(0,0,1);
vec3 K = vec3(0,0,0);

void main() {
    /// Diffuse shading
    vec3 N = normalize(fnormal_cam);
    vec3 L = vec3(0,0,-1);
    color = vec3(1,0,0) * dot( N, L );
}
