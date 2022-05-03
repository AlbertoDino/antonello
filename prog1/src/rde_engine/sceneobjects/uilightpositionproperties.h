#pragma once
#include "lightposition.h"

namespace sceneobjs {

	class UILightPositionProperties : public oglElements::IUIComponent {
	public:
		UILightPositionProperties();

		void setLight(LightPosition* _light);

		void render();

	private:
		LightPosition* light;

	};

}