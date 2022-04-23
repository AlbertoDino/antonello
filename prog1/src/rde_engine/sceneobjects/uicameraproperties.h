#pragma once


namespace sceneobjs {


	class UiCameraProperties : public oglElements::IUIComponent {
	public:
		UiCameraProperties();

		void setTextList(const render::UITextList* list);
		void setCamera(oglElements::Camera* cam);

		virtual void render();
	private:
		oglElements::Camera* camera;
		const render::UITextList* textList;
	};
}