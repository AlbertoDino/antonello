#pragma once

namespace sceneobjs {

	class Light : public oglElements::SceneShaderObject {
		public:

		Light();
		~Light();

		void add2scene();
		void updateViewMatrix();

		func::CVector3f position;
		func::CVector3f color;
		float Strength;
	};
}
