#version 330 core 

uniform float time;
in vec3 vpoint; ///< [-.5, +.5]^3
in vec3 vnormal;
out vec3 fpoint; ///< for debug
out vec3 fnormal_cam;

/// helper function
mat4 T(float x, float y, float z){ 
    mat4 _T = mat4(1);  
    _T[3] = vec4(x,y,z,1);
    return _T;
}

mat4 ortho(float l, float r, float b, float t, float n, float f){
    mat4 _T = T( -(l+r)/2, -(t+b)/2, -(n+f)/2 );
    mat4 _S = mat4(1);
    _S[0][0] = 2.0 / (r-l);
    _S[1][1] = 2.0 / (t-b);
    _S[2][2] = 2.0 / (f-n);
    return _S*_T;
}

mat4 lookat(vec3 origin, vec3 at, vec3 up){
    mat4 M = mat4(1);
    vec3 z = normalize(at-origin);
    vec3 x = normalize(cross(z, up));
    vec3 y = normalize(cross(x, z));
    M[0] = vec4(x,0);
    M[1] = vec4(y,0);
    M[2] = vec4(z,0);
    M[3] = vec4(origin,1);
    return inverse(M);
}

mat4 persp(float n, float f){
    mat4 _T = mat4(1);
    _T[0][0] = n;
    _T[1][1] = n;
    _T[2] = vec4(0,0,n+f, -n*f);
    _T[3] = vec4(0,0,1,0);
    return transpose(_T);
}

///-- DEFAULT MATRICES
mat4 Ms[2] = mat4[](T(-.5,0,0), T(+.5,0,0));
mat4 MODEL = Ms[gl_InstanceID];
mat4 VIEW = mat4(1);
mat4 PROJ = mat4(1);

void main() {
    // VIEW = lookat( 2*vec3(cos(time),0,sin(time)), vec3(0,0,0), vec3(0,1,0));
    VIEW = lookat( vec3(0,0,-2), vec3(0,0,0), vec3(0,1,0));
    MODEL = mat4(1);
    float near = 1.0;
    float far = 3.5;
    PROJ = ortho(-.5,+.5, -.5,+.5, near,far) * persp(near, far);
    
    fpoint = vpoint + .5; ///< For Debug [0,1]^3 
    fnormal_cam = inverse( transpose( mat3(VIEW * MODEL) )) * vnormal; 
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint, 1.0);
}
