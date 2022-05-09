#pragma once

namespace sceneobjs {

	class Model : public oglElements::GameObject {
	public:

		Model();
		Model(oglElements::RenderingElement * rndElem);
		~Model();

		//Add Model to mouse selection layer
		void add2PickingLayer();

		void add2SceneWithFlatShader();
		void add2SceneWithLightShader();

		Vector4f		color;
		float32			specularPower;
		float32			specularIntensity;
		int32			textureUnit;
	private:
		void init();
	};
}