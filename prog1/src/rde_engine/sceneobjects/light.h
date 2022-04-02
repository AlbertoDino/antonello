#pragma once

namespace sceneobjs {

	class Light : public oglElements::SceneShaderObject {
		public:

		Light();
		~Light();

		void add2scene();

		func::CVector3f direction;
		CVector3f color;
		float32 ambientIntensity;
		float32 diffuseIntensity;
	private:
		oglElements::ShaderContext* set_shader_temp2();
	};
}
