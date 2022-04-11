#pragma once
#include <ImFileBrowser.h>
#include "model.h"

namespace sceneobjs {

	class UIModelReference {
	public:
		std::string name;
		uint32 id;
	};

	class UiModelProperties : public oglElements::IUIComponent {
	public:
		UiModelProperties();

		void setModelList(const std::vector<Model *>& modelList);
		void setModelSelected(Model* model);

		void render();
		void set_mesh_load_callback(const std::function<void(const std::string&)>& callback);
		void set_model_selected_callback(const std::function<void(uint32)>& callback);


	private:
		ImGui::FileBrowser fileDialog;
		std::function<void(const std::string&)> meshLoadCallback;
		std::function<void(uint32)> modelSelectedCallback;
		std::string currentFile;
		std::vector<Model*> models;
		Model* modelSelected;
		int32 modelListIndex;
	};

}