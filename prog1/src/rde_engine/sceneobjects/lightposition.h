#pragma once

namespace sceneobjs {

	class LightPosition {
	public:
		LightPosition();

		void add2scene();

		void update(const CVector3f& cameraPos);

		oglElements::GameObject shaderNormal;
		oglElements::GameObject shaderNormalInstance;

		float32		lightPower;
		CVector3f	lightPosition;
		CVector3f	cameraPosition;
		CVector4f	ambientColor;
		CVector4f	diffuseColor;
	};
}