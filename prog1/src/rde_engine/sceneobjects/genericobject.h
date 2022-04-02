#pragma once

namespace sceneobjs {

	class GenericObject : public oglElements::SceneShaderObject {
	public:
		GenericObject();
		~GenericObject();

		void add2scene();
		void updateViewMatrix();

		func::CVector3f position;
		Vector4f		color;
		float32			roughness;
		float32			metallic;
		float32			ao;
	private:
		func::Quaternion orientation;

		oglElements::ShaderContext* set_shader_1();
		oglElements::ShaderContext* set_shader_2();
	};
}