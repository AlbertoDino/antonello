#include <rde_common/lib.h>
#include "window.h"

namespace win {

	Window::Window()
	{
		WindowsObj = std::make_unique<oglElements::WinObj>();
	}
}
