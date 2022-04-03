#pragma once

namespace sceneobjs {

	class Light : public oglElements::SceneShaderObject {
		public:

		Light();
		~Light();

		void update(const CVector3f &cameraPos);

		void add2scene();

		CVector3f cameraPos;
		CVector3f direction;
		CVector3f color;
		float32 ambientIntensity;
		float32 diffuseIntensity;
	private:
		oglElements::ShaderContext* set_shader_temp2();
	};
}
