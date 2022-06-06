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

	void UiCameraProperties::setCameraThirdView(oglElements::ThirdCameraView* cam)
	{
		thirdCameraView = cam;
	}

	void UiCameraProperties::render()
	{
		if(camera)
			renderCameraUI();
		if (thirdCameraView)
			renderCameraThirdViewUI();
	}

	void UiCameraProperties::renderCameraUI()
	{
		ImGui::Begin("Camera Details", 0, 0/* ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);

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

	void UiCameraProperties::renderCameraThirdViewUI()
	{
		auto const pos = thirdCameraView->getPosition();
		auto const dir = thirdCameraView->getDirection();
		auto const rot = thirdCameraView->getRotation();

		ImGui::Begin("Camera 3rd Details", 0, 0/* ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);
		
		ImGui::Text(format("Camera Pos [%2.2f,%2.2f,%2.2f]", pos[0], pos[1], pos[2]).c_str());
		ImGui::Text(format("Camera Dir [%2.2f,%2.2f,%2.2f]", dir[0], dir[1], dir[2]).c_str());
		ImGui::Text(format("Camera Rot [%2.2f,%2.2f,%2.2f]", rot[0], rot[1], rot[2]).c_str());


		ImGui::DragFloat("quaternion-x", &thirdCameraView->quaternion.x,0.01, -1, +1);
		ImGui::DragFloat("quaternion-y", &thirdCameraView->quaternion.y, 0.01, -1, +1);
		ImGui::DragFloat("quaternion-z", &thirdCameraView->quaternion.z, 0.01, -1, +1);

		ImGui::SliderFloat3("vDistance", thirdCameraView->vDistance.data, -41, +40);
		

		ImGui::SliderFloat("fovx", &thirdCameraView->fovx, -90, 180.0f);
		ImGui::SliderFloat("znear", &thirdCameraView->znear, 0, 180.0f);
		ImGui::SliderFloat("zfar", &thirdCameraView->zfar, 0, 180.0f);

		ImGui::End();
	}
}