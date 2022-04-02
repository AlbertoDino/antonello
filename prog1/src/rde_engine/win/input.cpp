#include <rde_common/lib.h>
#include "input.h"

namespace win {

	eMouseButton getMousePressedButton(oglElements::WinObj* window) {
        eMouseButton result = eMouseButton::None;

        if (glfwGetMouseButton(window->glWindowHandler, 0) == GLFW_PRESS)
            return eMouseButton::Left;
        else if (glfwGetMouseButton(window->glWindowHandler, 1) == GLFW_PRESS)
            return eMouseButton::Right;
        else if (glfwGetMouseButton(window->glWindowHandler, 2) == GLFW_PRESS)
            return eMouseButton::Middle;

        return eMouseButton::None;
	}

}

