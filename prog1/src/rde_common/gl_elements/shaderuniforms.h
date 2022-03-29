#pragma once

namespace oglElements {

	typedef int (*UniformLocationFunc)(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);

	EXTERN_  void UniformLocation_M4f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);	
	EXTERN_  void UniformLocation_M3f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);
	EXTERN_  void UniformLocation_V4f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);
	EXTERN_  void UniformLocation_V3f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);
	EXTERN_  void UniformLocation_V2f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);
	EXTERN_  void UniformLocation_V1f(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);
	EXTERN_  void UniformLocation_V1i(const void* v, const int32 count, int32 index, int32 location, bool8 transpose);

	class ShaderValueInput {
	protected:
	public:
		UniformLocationFunc		uniformFunc;
		const void				*value;
		int32					location;
		int32					count;
		bool8					transpose;

		ShaderValueInput();
		~ShaderValueInput();

		ShaderValueInput& operator=(const ShaderValueInput& u);

		

		void update() const;
	};


	class ShaderUniforms {
	public:
		ShaderUniforms();
		~ShaderUniforms();

		void init(uint32 programId);

		ShaderUniforms& operator=(const ShaderUniforms& u);

		void add(UniformLocationFunc f, const char8* uniformName,void *value);

		const ShaderValueInput* get(const int32& i) const;

		void useShader() const;

		void updateUniforms() const;

	private:
		std::vector<ShaderValueInput> inputValues;
		uint32				programId;
	};

	class ShaderSetter {
	public:
		ShaderSetter();

		void init(uint32 _programId);

		void set_mat4(const glm::mat4& mat4, const std::string& name);
		void set_i1(int v, const std::string& name);
		void set_f1(float v, const std::string& name);
		void set_f3(float a, float b, float c, const std::string& name);
		void set_vec3(const glm::vec3& vec3, const std::string& name);
		void set_vec4(const glm::vec4& vec4, const std::string& name);
	private:
		uint32	programId;
	};


}