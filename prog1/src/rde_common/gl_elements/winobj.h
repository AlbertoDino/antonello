#pragma once

namespace oglElements {

	class WinObj
	{
		public:
			void		*user_pointer;
			GLFWwindow	*glWindowHandler;
			HINSTANCE	osWindowHandler;
			int         width, height, top, left;
			std::string title;
	};

}

