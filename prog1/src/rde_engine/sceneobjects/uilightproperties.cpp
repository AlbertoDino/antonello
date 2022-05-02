#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "light.h"
#include "uilightproperties.h"


namespace sceneobjs {



	UILightProperties::UILightProperties() :
		light(0)
	{
	}

	void UILightProperties::setLight(Light* _light)
	{
		light = _light;
	}

	void UILightProperties::render()
	{
		if (!light) return;

		ImGui::Begin("Light Properties");
		ImGui::SliderFloat("ambient", &light->ambientIntensity, 0, 1.0f);
		ImGui::SliderFloat("diffuse", &light->diffuseIntensity, 0, 1.0f);
		if (ImGui::SliderFloat3("direction", light->direction.data, -1.0f, +1.0f)) {
			light->direction.Normalize();
		}
		ImGui::ColorEdit3("color", light->color.data);
		ImGui::End();
	}

}