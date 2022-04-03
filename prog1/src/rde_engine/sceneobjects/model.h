#pragma once

namespace sceneobjs {

	class Model : public oglElements::SceneShaderObject {
	public:

		Model();
		~Model();

		void add2scene();
		void updateViewMatrix();

		func::CVector3f position;
		Vector4f		color;
		float32			specularPower;
		float32			specularIntensity;
		std::string		name;
		uint32			id;
	private:
		func::Quaternion orientation;
		oglElements::ShaderContext* set_shader_1();
		oglElements::ShaderContext* set_shader_2();

		static uint32 modelIdCount;
		static uint32 getNextId();
	};
}