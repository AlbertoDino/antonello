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


	//LightShader

	bool8 LightShader::init()
	{
		oglElements::Shader shader;
		shader.loadFromFile("assets/shaders/vs.shader", "assets/shaders/fs_pbr.shader");
		programId = shader.get_program_id();
		return programId != 0;
	}

}