#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

flat in int iTextureIndex;

uniform vec4      ambientColor;

uniform sampler2D colorMap1;
uniform sampler2D normalMap1;
uniform sampler2D colorMap2;
uniform sampler2D normalMap2;
uniform sampler2D colorMap3;
uniform sampler2D normalMap3;
uniform sampler2D colorMap4;
uniform sampler2D normalMap4;
uniform sampler2D colorMap5;
uniform sampler2D normalMap5;


uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{       

	// obtain normal from normal map in range [0,1]
	vec3 normal;
	// get diffuse color
	vec3 color;		
	
	switch(iTextureIndex)
	{
	case 0: color=texture(colorMap1, fs_in.TexCoords).rgb;
			normal = texture(normalMap1, fs_in.TexCoords).rgb;
			break;
	case 1: color=texture(colorMap2, fs_in.TexCoords).rgb;
			normal = texture(normalMap2, fs_in.TexCoords).rgb;
			break;
	case 2: color=texture(colorMap3, fs_in.TexCoords).rgb;
			normal = texture(normalMap3, fs_in.TexCoords).rgb;
			break;
	case 3: color=texture(colorMap4, fs_in.TexCoords).rgb;
			normal = texture(normalMap4, fs_in.TexCoords).rgb;
			break;
	case 4: color=texture(colorMap5, fs_in.TexCoords).rgb;
			normal = texture(normalMap5, fs_in.TexCoords).rgb;
			break;
	}
	
	
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
	
    // ambient
    vec3 ambient = ambientColor.rgb * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
	
    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}