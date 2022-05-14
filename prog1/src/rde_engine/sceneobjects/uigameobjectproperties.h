#pragma once

namespace sceneobjs {

	class UIGameObjectProperties : public oglElements::IUIComponent {
	public:
		UIGameObjectProperties(oglElements::GameObject* object);

		void render();

	private:
		oglElements::GameObject* instance;

	};

}
