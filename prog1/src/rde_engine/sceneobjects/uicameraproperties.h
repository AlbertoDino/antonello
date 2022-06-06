#pragma once


namespace sceneobjs {


	class UiCameraProperties : public oglElements::IUIComponent {
	public:
		UiCameraProperties();

		void setTextList(const render::UITextList* list);
		void setCamera(oglElements::Camera* cam);
		void setCameraThirdView(oglElements::ThirdCameraView* cam);

		virtual void render();
	private:

		void renderCameraUI();
		void renderCameraThirdViewUI();

		oglElements::Camera* camera;
		oglElements::ThirdCameraView* thirdCameraView;

		const render::UITextList* textList;
	};
}