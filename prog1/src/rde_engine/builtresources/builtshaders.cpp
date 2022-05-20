#include <rde_common/lib.h>
#include "builtshaders.h"

namespace rex {

	//FlatShader

	static const char* szFlatShaderVP =
		"#version 330 \n"
		"in vec4 vVertex;"
		"uniform mat4 mvpMatrix;"
		"void main(void) "
		"{ gl_Position = mvpMatrix * vVertex; "
		"}";

	static const char* szFlatShaderFP =
		"#version 330 \n"
		"layout(location = 0) out vec4 vFragColor;"
		"uniform vec4 color;"
		"void main(void) "
		"{  vFragColor = color; "
		"}";

	bool8 FlatShader::init() {
	
		oglElements::Shader shader;
		shader.load(szFlatShaderVP, szFlatShaderFP);
		programId = shader.get_program_id();
		return programId != 0;
	}

	//ShaderLight

	bool8 Light::init()
	{
		oglElements::Shader shader;
		shader.loadFromFile("assets/shaders/lighting.vs", "assets/shaders/lighting.fs");
		programId = shader.get_program_id();
		return programId != 0;
	}

	// FlatShaderWithTexture
	static const char* szFlatShaderTextureVP =
		"#version 330\n"
		"in vec4 vVertex;"
		"in vec2 vTexCoord0;"
		"uniform mat4 mvpMatrix;"
		"smooth out vec2 vTex;"
		"void main(void) "
		"{ vTex = vTexCoord0;"
		" gl_Position = mvpMatrix * vVertex; "
		"}";

	static const char* szFlatShaderTextureFP =
		"#version 330\n"
		"out vec4 vFragColor;"
		"uniform sampler2D sampler;"
		"uniform vec4 vColor;"
		"smooth in vec2 vTex;"
		"void main(void) "
		"{ "
		"	vFragColor = texture(sampler, vTex); "
		"	/* vFragColor+=vColor; */"
		"}";

	bool8 FlatShaderWithTexture::init()
	{
		oglElements::Shader shader;
		shader.load(szFlatShaderTextureVP, szFlatShaderTextureFP);
		programId = shader.get_program_id();
		return programId != 0;
	}

	//NormalTextureLight

	bool8 NormalTextureLight::init()
	{
		oglElements::Shader shader;
		shader.loadFromFile("assets/shaders/NormalMapping.vs", "assets/shaders/NormalMapping.fs");
		programId = shader.get_program_id();
		return programId != 0;
	}


	//NormalTextureLightInstaced

	bool8 NormalTextureLightInstanced::init()
	{
		oglElements::Shader shader;
		shader.loadFromFile("assets/shaders/NormalMappingInstanced.vs", "assets/shaders/NormalMappingInstanced.fs");
		programId = shader.get_program_id();
		return programId != 0;
	}
}