vert:
#version 330 core
layout (location = 0) in vec3 inVertPos;
layout (location = 1) in vec2 inUv;
out vec2 uv;

void main()
{
    uv = inUv;
    gl_Position = vec4( inVertPos.xyz, 1.0);
}

frag:
#version 330 core
uniform sampler2D tex0;
in vec2 uv;
out vec4 fragColor;

void main()
{
    fragColor = texture( tex0, uv);
}
