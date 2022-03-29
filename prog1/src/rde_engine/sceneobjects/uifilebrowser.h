#pragma once
#include <ImFileBrowser.h>

namespace sceneobjs {

	class UiFileBrowser : public oglElements::IUIComponent {
	public:
		UiFileBrowser();

		void render();
		void set_mesh_load_callback(const std::function<void(const std::string&)>& callback);


	private:
		ImGui::FileBrowser fileDialog;
		std::function<void(const std::string&)> meshLoadCallback;
		std::string currentFile;
	};

}