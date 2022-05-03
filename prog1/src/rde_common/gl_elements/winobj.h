#pragma once

namespace oglElements {

	class WinObj
	{
		public:
			WinObj() :
				backgroundColor { 0.2f, 0.2f, 0.2f, 1.0f },
				viewPort {0,0,0,0} 
			{
			}

			void		*user_pointer;
			GLFWwindow	*glWindowHandler;
			HINSTANCE	osWindowHandler;
			
			// General settings
			bool8		isFullScreen;
			std::string title;
			Color		backgroundColor;
			// Window Size
			int         width, height, top, left;

			// View size is used by glViewport
			Recti		viewPort;
			
	};

}

