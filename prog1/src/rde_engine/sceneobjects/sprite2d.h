#pragma once
#pragma once

namespace sceneobjs {

	class Sprite2D : public oglElements::SceneObject {
	public:
		Sprite2D();

		void updateSpriteFrame(float32 elaps);

		void add2scene();

		oglElements::DrawSprite2D* getSpriteRendering();

		float32 speed;
		CVector3f position;
		CVector3f size;
	};

}