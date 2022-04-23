#pragma once


namespace render
{

	class UITextList {
	public:
		std::vector<std::string> list;
	};

	class UIScene {
	public:
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