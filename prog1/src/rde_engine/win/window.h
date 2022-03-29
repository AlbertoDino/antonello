#pragma once

namespace win {

	class Window
	{
		public: 
			Window();
			~Window();

			bool init(int width, int height, const std::string& title);
			void render();
			void handle_input();
			void on_scroll(double delta);
			void on_key(int key, int scancode, int action, int mods);
			void on_resize(int width, int height);
			void on_close();

		private:
			std::unique_ptr<oglElements::WinObj> WindowsObj;
	};

}

