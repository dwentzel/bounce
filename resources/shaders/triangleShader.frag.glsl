#version 330 core
#extension GL_ARB_explicit_attrib_location : enable


// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

uniform vec3 Material_diffuse;
uniform vec3 Material_ambient;
uniform vec3 Material_specular;
uniform vec3 Material_emissive;
uniform float Material_shininess;

void main(){

	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 50.0f;
	
	// Material properties
	vec3 MaterialDiffuseColor = Material_diffuse;
	vec3 MaterialAmbientColor = Material_ambient;
	vec3 MaterialSpecularColor = Material_specular;

	// Distance to the light
	float distance = length(LightPosition_worldspace - Position_worldspace);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(Normal_cameraspace);
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(LightDirection_cameraspace);

	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(n,l), 0,1);
//    float cosTheta = dot(n,l);
    
    
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E,R), 0,1);
	
	color = 
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}