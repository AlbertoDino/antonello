#include <rdecommon.h>
#include "shaderuniforms.h"

namespace oglElements {

	void UniformLocation_M4f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {		
		glUniformMatrix4fv(location, count, transpose, (const float32*)v);

		const Matrix4f32* d = (const Matrix4f32*)v;
	}

	void UniformLocation_M3f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniformMatrix3fv(location, count, transpose, (const float32*)v);

		const Matrix3f32* d = (const Matrix3f32*)v;
	}

	void UniformLocation_V4f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniform4fv(location, count, (const float32*)v);

		const Vector4f* d = (const Vector4f*)v;
	}

	void UniformLocation_V3f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniform3fv(location, count, (const float32*)v);

		const Vector3f* d = (const Vector3f*)v;
	}

	void UniformLocation_V2f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniform2fv(location, count, (const float32*)v);

		const Vector2f* d = (const Vector2f*)v;
	}

	void UniformLocation_V1f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniform1fv(location, count, (const float32*)v);

		const float32* d = (const float32*)v;
	}

	void UniformLocation_V1i(const void* v, const int32 count, int32 index, int32 location, bool8 transpose) {
		glUniform1iv(location, count, (const int32*)v);

		const int32* d = (const int32*)v;
	}

	/**/

	ShaderValueInput::ShaderValueInput() :
		uniformFunc(0),
		location(0),
		value (0),
		count(1),
		transpose(false)
	{

	}

	ShaderValueInput::~ShaderValueInput()
	{
		value = 0;
	}

	ShaderValueInput& ShaderValueInput::operator=(const ShaderValueInput& u)
	{
		uniformFunc = u.uniformFunc;
		value = u.value;
		location = u.location;
		count = u.count;
		transpose = u.transpose;
		return *this;
	}

	void ShaderValueInput::update() const
	{
		uniformFunc(value, count, 0, location, transpose);
	}

	/**/

	ShaderUniforms::ShaderUniforms() :
		programId(0)
	{
	}

	ShaderUniforms::~ShaderUniforms()
	{
	}

	void ShaderUniforms::init(uint32 programId)
	{
		this->programId = programId;
	}

	void ShaderUniforms::add(UniformLocationFunc f, const char8* uniformName, void* value)
	{	
		ShaderValueInput unif;

		unif.transpose = false;
		unif.location = glGetUniformLocation(programId, uniformName);
		unif.uniformFunc = f;
		unif.count = 1;
		unif.value = value;
		unif.__debugName = uniformName;
	
		if (unif.location < 0) {
			tracelog(format("Uniform [%s] not valid", uniformName));
			return;
		}

		inputValues.push_back(unif);	
	}

	ShaderUniforms& ShaderUniforms::operator=(const ShaderUniforms& u) {
		programId = u.programId;
		return *this;
	}

	const ShaderValueInput* ShaderUniforms::get(const int32& i) const
	{
		return &this->inputValues[i];
	}

	void ShaderUniforms::useShader() const
	{
		glUseProgram(programId);
	}

	void ShaderUniforms::updateUniforms() const
	{
		for (auto const& unif : std::as_const(inputValues)) {
			unif.update();
		}
	}

	/**/

	ShaderSetter::ShaderSetter() : programId(0) 
	{
	}

	void ShaderSetter::init(uint32 _programId) 
	{
		programId = _programId;
	}

	void ShaderSetter::set_mat4(const glm::mat4& mat4, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}

	void ShaderSetter::set_i1(int v, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glUniform1i(myLoc, v);
	}

	void ShaderSetter::set_f1(float v, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glUniform1f(myLoc, v);
	}

	void ShaderSetter::set_f3(float a, float b, float c, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glUniform3f(myLoc, a, b, c);
	}

	void ShaderSetter::set_vec3(const glm::vec3& vec3, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glProgramUniform3fv(programId, myLoc, 1, glm::value_ptr(vec3));
	}

	void ShaderSetter::set_vec4(const glm::vec4& vec4, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(programId, name.c_str());
		glProgramUniform4fv(programId, myLoc, 1, glm::value_ptr(vec4));
	}
}