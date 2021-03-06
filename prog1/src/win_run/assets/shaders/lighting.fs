#version 330

in vec3 VertexPos0;
in vec3 Normal0;
in vec2 TexCoord0;   
  

// light parameters
struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
	float DiffuseIntensity;
	vec3 Direction; 	
};
uniform DirectionalLight gDirectionalLight;
// camera parameters
uniform vec3 			camPos;
// material parameters
uniform sampler2D 		sampler;  
uniform vec3 			objColor;
uniform float 			objSpecularIntensity;
uniform float 			objSpecularPower;

out vec4 FragColor;

const float PI = 3.14159265359;

void main()
{
	vec3 N            = normalize(Normal0);	
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
	vec3 lightDir     =  -gDirectionalLight.Direction;

	float DiffuseFactor = dot(N,lightDir); 
	
	vec4 DiffuseColor  = vec4(0, 0, 0, 0); 
	vec4 SpecularColor = vec4(0, 0, 0, 0); 
	
	if (DiffuseFactor > 0) {                                                        
        DiffuseColor      = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);				 
		vec3 VertexToEye  = normalize(camPos - VertexPos0); 
		vec3 LightReflect = normalize(reflect(gDirectionalLight.Direction, N));
		float SpecularFactor = dot(VertexToEye, LightReflect); 
		if (SpecularFactor > 0) {                                                   
            SpecularFactor = pow(SpecularFactor, objSpecularPower);
            SpecularColor = vec4(gDirectionalLight.Color * objSpecularIntensity * SpecularFactor, 1.0f);
        }		
		
    }                                                                               
	
	FragColor = texture2D(sampler, TexCoord0.xy) *vec4(objColor,1.f) * AmbientColor + DiffuseColor + SpecularColor;
}
