#pragma once


namespace sceneobjs {

	class UILightProperties : public oglElements::IUIComponent {
	public:
		UILightProperties();

		void setLight(Light* _light);

		void render();

	private:
		Light* light;

	};

}
