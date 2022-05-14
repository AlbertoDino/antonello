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
		ImGui::Begin("Camera Details",0,0/* ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);

		auto const pos = camera->getPosition();
		auto const dir = camera->getDirection();
		auto const rot = camera->getRotation();

		if (textList) {
			for (auto const& text : std::as_const(textList->list)) {
				ImGui::Text(text.c_str());
			}
		}

		ImGui::Text(format("Camera Pos [%2.2f,%2.2f,%2.2f]", pos[0], pos[1], pos[2]).c_str());
		ImGui::Text(format("Camera Dir [%2.2f,%2.2f,%2.2f]", dir[0], dir[1], dir[2]).c_str());
		ImGui::Text(format("Camera Rot [%2.2f,%2.2f,%2.2f]", rot[0], rot[1], rot[2]).c_str());


		ImGui::SliderFloat("speed", &camera->defaultSpeed, 0, 500.0f);
		ImGui::SliderFloat("rotationSpeed", &camera->rotationSpeed, 0, 100.0f);
		ImGui::SliderFloat("fovx", &camera->fovx, -90, 180.0f);
		ImGui::SliderFloat("znear", &camera->znear, 0, 180.0f);
		ImGui::SliderFloat("zfar", &camera->zfar, 0, 180.0f);


		ImGui::End();
	}
}