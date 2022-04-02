#pragma once

namespace win {

    enum class eMouseButton : int32
    {
        Left = 0,
        Right = 1,
        Middle = 2,
        None = 9
    };

    extern eMouseButton getMousePressedButton(oglElements::WinObj* window);

}