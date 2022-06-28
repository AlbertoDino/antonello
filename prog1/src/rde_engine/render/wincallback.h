#pragma once

namespace render {

	class WinEventHandler {
	public:

		virtual void OnKey(int key, int scancode, int action, int mods)=0;
		virtual void OnMouseScroll(double xoffset, double yoffset) = 0;
		virtual void OnWindowSizeChange(int width, int height) = 0;
		virtual void OnWindowClose() = 0;
		virtual void OnPositionCursorChange(double xpos, double ypos) = 0;

	};

}