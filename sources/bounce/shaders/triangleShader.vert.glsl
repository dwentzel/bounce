#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec4 fragmentColor;

//in vec4 vertexPosition_modelspace;
uniform mat4 mvp;

void main() {
    vec4 v = vec4(vertexPosition_modelspace);
    gl_Position = mvp * v;
    
    fragmentColor = vec4(vertexColor, 1);
    //fragmentColor = vec3(1, 1, 0);
}