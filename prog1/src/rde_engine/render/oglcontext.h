#pragma once
#include <rde_common/lib.h>

namespace render {

	extern void Win_On_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	extern void Win_On_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
	extern void Win_On_Window_Size_Callback(GLFWwindow* window, int width, int height);
	extern void Win_On_Window_close_callback(GLFWwindow* window);
	extern void Win_On_Cursor_callback(GLFWwindow* window, double xpos, double ypos);

	class OglContext
	{
	public:
		OglContext();

		bool init(oglElements::WinObj* window);

		void pre_render();
		void post_render();
		void end();

	protected:
		oglElements::WinObj* Window;
	};

}

