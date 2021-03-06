#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;

uniform mat4 mvpMatrix;
uniform mat4 viewMatrix;

out vec3 VertexPos0;
out vec3 Normal0;
out vec2 TexCoord0;    

void main()
{
    gl_Position = mvpMatrix * vec4(vPosition, 1.0);
	
	TexCoord0   = vUV;  
/*
	Normal0 = (viewMatrix * vec4(vNormal, 0.0)).xyz;
*/	
	mat4 normalMatrix = transpose(inverse(viewMatrix));
	Normal0 = normalize(normalMatrix * vec4(vNormal, 0.0)).xyz;
	VertexPos0 = (mvpMatrix * vec4(vPosition, 1.0)).xyz;  
}
