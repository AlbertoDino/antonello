#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "model.h"
#include "uimodelproperties.h"


namespace sceneobjs {


	UiModelProperties::UiModelProperties() : 
		modelSelected(0),
		modelListIndex(-1),
		modelSelectedCallback(0)
	{
		currentFile = "< ... >";
		fileDialog.SetTitle("Open mesh");
		fileDialog.SetFileFilters({ ".obj",".fbx" });


	}

	void UiModelProperties::setModelList(const std::vector<Model* >& modelList)
	{
		models = modelList;
	}

	void UiModelProperties::render()
	{
		ImGui::Begin("Model Properties");
		if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Open..."))
			{
				fileDialog.Open();
			}
			ImGui::SameLine(0, 5.0f);
			ImGui::Text(currentFile.c_str());


			std::string currentModelSelectedName = modelSelected == 0 ? "None" : modelSelected->name;
			ImGui::Text("Models ");
			ImGui::SameLine(0, 5.0f);			
			if (ImGui::Button((modelListIndex == -1 ? "None" : models.at(modelListIndex)->name).c_str()))
			{
				modelSelected = 0;
				if (modelListIndex >= 0 && modelSelectedCallback) {
					modelSelectedCallback(models.at(modelListIndex)->id);
					modelSelected = models.at(modelListIndex);
				}

				modelListIndex++;
				if (modelListIndex == models.size())
					modelListIndex = -1;
			};

			ImGui::Text("Model selected:");
			ImGui::SameLine(0, 5.0f);
			ImGui::Text(currentModelSelectedName.c_str());

			if (modelSelected) {
				ImGui::ColorEdit3("color", modelSelected->color);
				ImGui::SliderFloat("specularIntensity", &modelSelected->specularIntensity, 0.0f, 1.0f);
				ImGui::SliderFloat("specularPower", &modelSelected->specularPower, -10.0f, 64.0f);

			}
		}

		ImGui::End();
		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			auto file_path = fileDialog.GetSelected().string();
			currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);

			meshLoadCallback(file_path);

			fileDialog.ClearSelected();
		}
	}

	void UiModelProperties::set_mesh_load_callback(const std::function<void(const std::string&)>& callback)
	{
		meshLoadCallback = callback;
	}

	void UiModelProperties::set_model_selected_callback(const std::function<void(uint32)>& callback)
	{
		modelSelectedCallback = callback;
	}

}