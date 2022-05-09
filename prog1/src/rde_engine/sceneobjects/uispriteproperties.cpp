#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "sprite2d.h"
#include "uispriteproperties.h"

namespace sceneobjs {

	UISpriteProperties::UISpriteProperties(sceneobjs::Sprite2D* object)
		: sprite(object)
	{
	}

	void UISpriteProperties::render()
	{
		ImGui::Begin("Antonello");

		ImGui::DragFloat("speed", &sprite->data->speed, 0.1, -2, +2);
		ImGui::DragFloat3("position-offset", sprite-> data->positionOffset.data, 0.1, -10, 50);
		ImGui::DragFloat3("position", sprite->data->position.data, 0.1, -10, 50);

		ImGui::End();
	}

}