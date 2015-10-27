#version 330 core 
uniform float time;
in vec3 vpoint; ///< [-.5, +.5]^3
out vec3 fpoint; ///< for debug

/// helper function
mat4 T(float x, float y, float z){ 
    mat4 _T = mat4(1);  
    _T[3] = vec4(x,y,z,1);
    return _T;
}

#ifndef STRIP_CODE
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

mat4 ortho(float l, float r, float b, float t, float n, float f){
    mat4 T = mat4(1);
    T[3] = vec4(-(r+l)/2, -(t+b)/2, -(f+n)/2, 1);
    mat4 S = mat4(1);
    S[0][0] = 2.0/(r-l);
    S[1][1] = 2.0/(t-b);
    S[2][2] = 2.0/(f-n);
    return S*T;
}

mat4 persp(float n, float f){
    mat4 P = mat4(1); //!!! column assembly
    P[0][0] = n;
    P[1][1] = n;
    P[2] = vec4(0, 0, (n+f), -n*f);
    P[3] = vec4(0, 0, 1, 0);
    return transpose(P);
}

#endif

///-- DEFAULT MATRICES
mat4 Ms[2] = mat4[](T(-.5,0,0), T(+.5,0,0));
mat4 MODEL = Ms[gl_InstanceID];
mat4 VIEW = mat4(1);
mat4 PROJ = mat4(1);

void main() {
#ifndef STRIP_CODE  
    /// Write ortho (trivial test)
//    PROJ = ortho(-1,+1, -1,+1, -1,+1);

    /// Test clipping
//    PROJ = ortho(0,+1, -1,+1, -1,+1);
    
    /// Test clipping (w/o distortion)
//    PROJ = ortho(0,+2, -1,+1, -1,+1);
    
    /// Write lookat (trivial test)
//    VIEW = lookat( vec3(0,0,-1), vec3(0,0,0), vec3(0,1,0) );
//    PROJ = ortho(-1,+1, -1,+1, -1,+1);
    
    /// Write lookat (side view test)
//    VIEW = lookat( vec3(1,0,0), vec3(0,0,0), vec3(0,1,0) );
//    PROJ = ortho(-1,+1, -1,+1, -1,+1);

    /// Test spinning (w/ problem)
//    VIEW = lookat( vec3(cos(time), 0, sin(time)), vec3(0,0,0), vec3(0,1,0) );
//    PROJ = ortho(-1,+1, -1,+1, -1,+1);
    
    /// Test spinning (w/o problem)
//    VIEW = lookat( vec3(cos(time), 0, sin(time)), vec3(0,0,0), vec3(0,1,0) );
//    float near=0.0, far=2.0;
//    PROJ = ortho(-1,+1, -1,+1, near, far);
    
    /// Write perspective (w/ scaling difference)
//    Ms = mat4[](T(-.5,0,+.5), T(+.5,0,-.5));
//    MODEL = Ms[gl_InstanceID];
//    VIEW = lookat( vec3(0,0,-2), vec3(0,0,0), vec3(0,1,0) );
//    float near=1.0, far=3.0;
//    PROJ = ortho(-1,+1,-1,+1, near, far) * persp(near, far);

    /// Write perspective (w/ animation)
    //      test: near=0
    //      test: near>1.0
    VIEW = lookat( 2*vec3(cos(time), 0, sin(time)), vec3(0,0,0), vec3(0,1,0) );
    float near=1.0, far=3.0;
    PROJ = ortho(-1,+1,-1,+1, near, far) * persp(near, far);
#endif
    
    fpoint = vpoint + .5; ///< For Debug [0,1]^3 
    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint, 1.0);
}
