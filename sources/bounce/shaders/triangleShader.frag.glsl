#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

in vec4 fragmentColor;
out vec4 color;

void main() {
    color = fragmentColor;
}
