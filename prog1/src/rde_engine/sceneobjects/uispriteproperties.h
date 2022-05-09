#pragma once

namespace sceneobjs {

	class UISpriteProperties : public oglElements::IUIComponent {
	public:
		UISpriteProperties(sceneobjs::Sprite2D* object);

		void render();

	private:
		sceneobjs::Sprite2D* sprite;

	};

}
