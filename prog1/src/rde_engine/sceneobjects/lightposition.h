#pragma once

namespace sceneobjs {

	class LightPosition : public oglElements::GameObject {
	public:
		LightPosition();

		void add2scene();

		void update(const CVector3f& cameraPos);

		float32		lightPower;
		CVector3f	lightPosition;
		CVector3f	cameraPosition;
		CVector4f	ambientColor;
		CVector4f	diffuseColor;
	};
}