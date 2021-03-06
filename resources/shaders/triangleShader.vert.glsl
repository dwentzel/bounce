#version 330 core
//#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace[10];
uniform int LightCount;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace[10];


void main() {
    //vec4 v = vec4(vertexPosition_modelspace, 1);
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

    vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
    
    EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;

    for (int i = 0; i < LightCount; i++) {
        vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace[i], 1)).xyz;
        LightDirection_cameraspace[i] = LightPosition_cameraspace + EyeDirection_cameraspace;
    }
	
    // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
    Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace,0)).xyz;
	
    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}