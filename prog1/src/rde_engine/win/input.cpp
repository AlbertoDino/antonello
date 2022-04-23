#include <rde_common/lib.h>
#include "input.h"

namespace win {

	eMouseButton getMousePressedButton(oglElements::WinObj* window) {
        eMouseButton result = eMouseButton::None;

        if (glfwGetMouseButton(window->glWindowHandler, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            return eMouseButton::Left;
        else if (glfwGetMouseButton(window->glWindowHandler, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
            return eMouseButton::Right;
        else if (glfwGetMouseButton(window->glWindowHandler, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
            return eMouseButton::Middle;

        return eMouseButton::None;
	}

}

