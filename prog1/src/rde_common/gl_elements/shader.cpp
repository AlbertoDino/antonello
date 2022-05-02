#include <rdecommon.h>
#include "shader.h"

namespace oglElements {

	unsigned int Shader::get_compiled_shader(unsigned int shader_type, const std::string& shader_source)
	{
		unsigned int shader_id = glCreateShader(shader_type);

		const char* c_source = shader_source.c_str();
		glShaderSource(shader_id, 1, &c_source, nullptr);
		glCompileShader(shader_id);

		GLint result;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

			GLchar* strInfoLog = new GLchar[length + 1];
			glGetShaderInfoLog(shader_id, length, &length, strInfoLog);

			tracelog("Shader compile status ERROR");
			fprintf(stderr, "Compile error in shader: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		return shader_id;
	}

	bool Shader::loadFromFile(const std::string& vertexshader_file, const std::string& fragmentshader_file)
	{
		std::ifstream is_vs(vertexshader_file);
		const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

		std::ifstream is_fs(fragmentshader_file);
		const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

		return load(f_vs, f_fs);
	}

	bool Shader::load(const std::string& vertexshade, const std::string& fragmentshade) {
		ProgramId = glCreateProgram();

		unsigned int vs = get_compiled_shader(GL_VERTEX_SHADER, vertexshade);
		unsigned int fs = get_compiled_shader(GL_FRAGMENT_SHADER, fragmentshade);

		glAttachShader(ProgramId, vs);
		glAttachShader(ProgramId, fs);

		glLinkProgram(ProgramId);
		glValidateProgram(ProgramId);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return true;
	}

	void Shader::use() const
	{
		glUseProgram(ProgramId);
	}

	void Shader::unload() const
	{
		glDeleteProgram(ProgramId);
	}

	uint32 Shader::get_program_id() const
	{
		return ProgramId;
	}
}