#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "model.h"
#include "uicameraproperties.h"

namespace sceneobjs {
	
	UiCameraProperties::UiCameraProperties() :
		camera(0),
		textList(0)
	{
	}

	void UiCameraProperties::setTextList(const render::UITextList* list)
	{
		textList = list;
	}

	void UiCameraProperties::setCamera(oglElements::Camera* cam)
	{
		camera = cam;
	}

	void UiCameraProperties::render()
	{
		ImGui::Begin("Camera Details");
		for (auto const& text : std::as_const(textList->list)) {
			ImGui::Text(text.c_str());
		}
		ImGui::SliderFloat("speed", &camera->speed, 0, 500.0f);
		ImGui::SliderFloat("rotationSpeed", &camera->rotationSpeed, 0, 100.0f);
		ImGui::End();
	}
}