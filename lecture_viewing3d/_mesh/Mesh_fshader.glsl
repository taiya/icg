#version 330 core
out vec3 color;
in vec3 fpoint;
in vec3 fnormal_cam;
uniform float time;

uniform sampler2D tex_day;
uniform sampler2D tex_night;

vec3 R = vec3(1,0,0);
vec3 G = vec3(0,1,0);
vec3 B = vec3(0,0,1);
vec3 K = vec3(0,0,0);

void main() {
    vec3 N = normalize(fnormal_cam);
    vec3 L = vec3(0,0,-1);
    L = normalize( vec3(cos(time),0,sin(time)) );
    float lamb = dot( N, L );
    //color = vec3(1,0,0) * lamb;
    
    vec3 p = normalize(fpoint-.5);
    float _phi = (6.28 - atan(p.z,p.x)) / 6.28;
    float _theta = (3.14 - acos(p.y)) / 3.14;
    vec3 day = texture(tex_day, vec2(_phi,_theta)).rgb * lamb;
    vec3 night = texture(tex_night, vec2(_phi,_theta)).rgb;
    color = mix(night, day, max(lamb,0));
    
    if(lamb>0){
        vec3 V = vec3(0,0,-1);
        vec3 R = reflect(V,N);
        float glossy = pow( max( dot(-R,L), 0 ), 100);
        color += vec3(.5) * glossy; 
    }
        
    // color = mix(R,G,fpoint[2]);
        
//    int index = int( mod(gl_PrimitiveID,6) );
//    color = COLORS[index];
}
