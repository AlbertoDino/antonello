#pragma once


namespace render
{

	class UITextList {
	public:
		std::vector<std::string> list;
	};

	class UIContext : public oglElements::IRenderingCtx {
	
	public:
		UIContext(int32 rndContextId);
		~UIContext();

		virtual void init(oglElements::WinObj* window);
		virtual void render() const;
		virtual void end();
		virtual void reset();

		std::vector<oglElements::IUIComponent*> uiComponents;

	};
}