#pragma once

namespace rex {

	class FlatShader {
	public:
		bool8 init();
		uint32 programId;
	};

	class Light {
	public:
		bool8 init();
		uint32 programId;
	};

	class FlatShaderWithTexture {
	public:
		bool8 init();
		uint32 programId;

	};

	class NormalTextureLight {
	public:
		bool8 init();
		uint32 programId;
	};

}