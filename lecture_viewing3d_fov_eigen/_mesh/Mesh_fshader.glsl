#version 330 core
out vec3 color;
in vec3 fpoint;
in vec3 fnormal_cam;
uniform float time;

vec3 R = vec3(1,0,0);
vec3 G = vec3(0,1,0);

void main() {
    /// Color interpolated in model-space X-coordinate
    vec3 base_color = mix(R,G,fpoint[0]);
    
    /// Lambertian shading only
    vec3 N = normalize(fnormal_cam);
    
    /// --------------- VERY IMPORTANT -------------------
    /// REMEMBER THAT EIGEN CREATES MATRICES FOR A 
    /// RIGHT HAND COORDINATE SYSTEM, WHERE THE CAMERA
    /// LOOKS ALONG THE -Z DIRECTION. THAT'S WHY "L" IS
    /// NEGATED W.R.T. WHAT WE HAD EARLIER!!!!
    ///---------------------------------------------------
    //vec3 L = vec3(0,0,-1); ///< before
    vec3 L = vec3(0,0,1); ///< now
        
    float lamb = dot( N, L );
    color = base_color * lamb;
}
