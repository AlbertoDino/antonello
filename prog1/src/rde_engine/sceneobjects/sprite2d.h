#pragma once
#pragma once

namespace sceneobjs {

	class Sprite2D : public oglElements::SceneObject {
	public:
		Sprite2D();

		void updateFrame(float32 elaps);

		void add2scene();


		oglElements::AnimationType currentAnimation;
	};

}