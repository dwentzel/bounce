#version 330 core
#extension GL_ARB_explicit_attrib_location : enable


// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace[10];

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
struct DirectionalLight {
    vec3 position;
    vec3 color;
    float diffuse_intensity;
    float ambient_intensity;
};

uniform DirectionalLight directionalLights[10];

uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace[10];

uniform vec3 Material_diffuse;
uniform vec3 Material_ambient;
uniform vec3 Material_specular;
uniform vec3 Material_emissive;
uniform float Material_shininess;

uniform int LightCount;

void main(){

	// Light emission properties
	// You probably want to put them as uniforms
	//vec3 LightColor = vec3(1,1,1);
	//float LightPower = 50.0f;
	
	// Material properties
    vec3 MaterialEmissiveColor = Material_emissive;
//	vec3 MaterialDiffuseColor = Material_diffuse;
    vec3 MaterialDiffuseColor = texture( myTextureSampler, UV ).rgb;
	vec3 MaterialAmbientColor = Material_ambient;
	vec3 MaterialSpecularColor = Material_specular;

    // Normal of the computed fragment, in camera space
    vec3 n = normalize(Normal_cameraspace);

    vec3 totalColor = vec3(0,0,0);

    for (int i; i < LightCount; i++) {
        // Distance to the light
        float distance = length(LightPosition_worldspace[i] - Position_worldspace);

        // Direction of the light (from the fragment to the light)
        vec3 l = normalize(LightDirection_cameraspace[i]);

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
        
        vec3 localColor =
            Material_emissive +
            // Ambient : simulates indirect lighting
            MaterialAmbientColor * directionalLights[i].color * directionalLights[i].ambient_intensity +
            // Diffuse : "color" of the object
            MaterialDiffuseColor * directionalLights[i].color * directionalLights[i].diffuse_intensity * cosTheta / (distance * distance);// +
            // Specular : reflective highlight, like a mirror
            //MaterialSpecularColor * directionalLights[i].color * directionalLights[i].specular_intensity * pow(cosAlpha, Material_shininess) / (distance * distance);
        
        totalColor = totalColor + localColor;
    }
    
    color = totalColor;
  
//	color =
//        Material_emissive +
//		// Ambient : simulates indirect lighting
//		MaterialAmbientColor +
//		// Diffuse : "color" of the object
//		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
//		// Specular : reflective highlight, like a mirror
//		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, Material_shininess) / (distance*distance);
}