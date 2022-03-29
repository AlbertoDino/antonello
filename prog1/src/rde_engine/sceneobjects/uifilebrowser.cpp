#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "uifilebrowser.h"


namespace sceneobjs {



	UiFileBrowser::UiFileBrowser()
	{
		currentFile = "< ... >";
		fileDialog.SetTitle("Open mesh");
		fileDialog.SetFileFilters({ ".fbx", ".obj" });
	}

	void UiFileBrowser::render()
	{
		ImGui::Begin("Properties");
		if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Open..."))
			{
				fileDialog.Open();
			}
			ImGui::SameLine(0, 5.0f);
			ImGui::Text(currentFile.c_str());
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

	void UiFileBrowser::set_mesh_load_callback(const std::function<void(const std::string&)>& callback)
	{
		meshLoadCallback = callback;
	}

}