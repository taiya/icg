#version 330 core 
uniform float time;
in vec3 vpoint; ///< [-1,+1]
out float vheight; ///< for debug coloring
out float scale=.5;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJ;

uniform sampler2D tex;
float tex_at(vec2 uv){ return texture(tex,uv).r; }

void main() {
    /// UNCOMMENT ONE OF THESE
//    vheight = 0;
//    vheight = scale * sin(10*vpoint.x + time);
    vheight = scale * tex_at( .5*vec2(time+vpoint.x, vpoint.y)+.5 );

    gl_Position = PROJ * VIEW * MODEL * vec4(vpoint.x, vpoint.y, vheight, 1.0);
}
