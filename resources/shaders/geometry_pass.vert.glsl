#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 WVP;
uniform mat4 W;
uniform mat4 V;

out vec2 TexCoord0;
out vec3 Normal0;
out vec3 WorldPos0;

void main()
{
    gl_Position = WVP * vec4(Position, 1.0);
    TexCoord0 = TexCoord;
    Normal0 = (W * vec4(Normal, 0.0)).xyz;
    WorldPos0 = (W * vec4(Position, 1.0)).xyz;
}