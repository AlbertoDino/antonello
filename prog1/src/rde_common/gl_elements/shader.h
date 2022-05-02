#pragma once

namespace oglElements {

	class Shader
	{

	private:
		unsigned int ProgramId;

		unsigned int get_compiled_shader(unsigned int shader_type, const std::string& shader_source);

	public:
		Shader() = default;

		// Load a add and a fragment shader from file
		bool loadFromFile(const std::string& vertexshader_file, const std::string& fragmentshader_file);
		bool load(const std::string& vertexshade, const std::string& fragmentshade);
		// Use the program
		void use() const;

		// Delete the program
		void unload() const;

		uint32 get_program_id() const;		 

	};
}
