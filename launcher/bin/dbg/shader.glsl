vert:
#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 uv;
uniform vec2 pos;
uniform vec2 size;
uniform vec2 anchor;

void main()
{
    gl_Position = vec4( vertexPos.xy * size - anchor * size + ( pos * 2 - vec2(1, 1)), 0.0 , 1.0);
}

frag:
#version 330 core
uniform vec3 color;
out vec4 fragColor;

void main()
{
    fragColor = vec4( color, 1.0);
}