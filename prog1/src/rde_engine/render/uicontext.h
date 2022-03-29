#pragma once


namespace render
{
	class UIScene {
	public:
		std::string dialogName;
		std::vector<std::string> textList;
		std::vector<oglElements::IUIComponent*> uiComponents;
	};

	class UIContext : public oglElements::IRenderingCtx {
	
	public:
		UIContext(int32 rndContextId);
		~UIContext();

		virtual void init(oglElements::WinObj* window);
		virtual void render() const;
		virtual void end();

		void render(UIScene* ui);

	private:
		UIScene* uiScene;
	};
}