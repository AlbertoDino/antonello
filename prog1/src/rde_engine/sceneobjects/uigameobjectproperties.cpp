#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "sprite2d.h"
#include "uigameobjectproperties.h"

namespace sceneobjs {

	UIGameObjectProperties::UIGameObjectProperties(oglElements::GameObject* object)
		: instance(object)
	{
	}

	void UIGameObjectProperties::render()
	{
		ImGui::Begin(instance->data->name.c_str());

		ImGui::DragFloat("speed", &instance->data->currentSpeed, 0.05, -10, +10);
		ImGui::DragFloat("default speed", &instance->data->defaultSpeed, 0.05, -10, +10);
		ImGui::DragFloat3("scale", instance->data->scale.data, 0.05, -20, 50);
		ImGui::DragFloat3("position-offset", instance-> data->positionOffset.data, 0.1, -10, 50);
		ImGui::DragFloat3("position", instance->data->position.data, 0.1, -50, 50);
		ImGui::DragFloat("orientation-x", &instance->data->orientation.x, 0.05, -2, 2);
		ImGui::DragFloat("orientation-y", &instance->data->orientation.y, 0.05, -2, 2);
		ImGui::DragFloat("orientation-z", &instance->data->orientation.z, 0.05, -2, 2);
		ImGui::DragFloat("orientation-w", &instance->data->orientation.w, 0.05, -2, 2);
		ImGui::DragFloat3("direction", instance->data->direction.data, 0.1, -10, 50);
		ImGui::DragFloat3("rotation", instance->data->rotation.data, 0.1, -10, 50);

		auto sprite = (sceneobjs::Sprite2D*)instance;
		if (sprite) {
			ImGui::DragFloat("animation speed", &sprite->animationSpeed, 0.05, -4, +4);
			ImGui::DragFloat("speed jump", &sprite->jumpSpeed, 0.05, -4, +4);
			ImGui::DragFloat3("vJump", sprite->vJump.data, 0.05, -4, +4);

			if (ImGui::Button("Save")) {
				sprite->saveSettingsToFile();
			}

		}

		ImGui::End();
	}

}