#pragma once

namespace sceneobjs {

	class Model : public oglElements::SceneShaderObject {
	public:

		Model();
		Model(oglElements::RenderingElement * rndElem);
		~Model();

		//Add Model to mouse selection layer
		void add2PickingLayer();

		void add2SceneWithFlatShader();
		void add2SceneWithLightShader();

		void updateViewMatrix();

		func::CVector3f position;
		Vector4f		color;
		float32			specularPower;
		float32			specularIntensity;
		std::string		name;
		uint32			id;
		int32			textureUnit;
	private:
		func::Quaternion orientation;
		void init();
	};
}