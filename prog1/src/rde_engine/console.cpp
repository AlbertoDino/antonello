#include <rde_common/lib.h>
#include "rde_engine/win/local.h"
#include "console.h"

win::Console* gConsole;

namespace win {

#define  CONSOLE_MAX_LINES		 500
#define  CONSOLE_MAX_INPUTBUFFER 1024

#define COPY_ID			1
#define QUIT_ID			2
#define CLEAR_ID		3
#define ERRORBOX_ID		10
#define ERRORTEXT_ID	11
#define EDIT_ID			100
#define INPUT_ID		101


    LRESULT CALLBACK ConsoleProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg)
        {
        case WM_CREATE:
            SetTimer(hWnd, 1, 1000, NULL);
            break;
        case WM_TIMER:
            if (wParam == 1)
            {

            }
            break;
        case WM_CTLCOLORSTATIC:
            if ((HWND)lParam == gConsole->hwndBuffer)
            {
                SetBkColor((HDC)wParam, RGB(0x00, 0x00, 0xB0));
                SetTextColor((HDC)wParam, RGB(0xff, 0xff, 0x00));
                return (long)gConsole->hbrEditBackground;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            switch (wParam)
            {
            case COPY_ID:
                SendMessage(gConsole->hwndBuffer, EM_SETSEL, 0, -1);
                SendMessage(gConsole->hwndBuffer, WM_COPY, 0, 0);
                break;
            case CLEAR_ID:
                SendMessage(gConsole->hwndBuffer, EM_SETSEL, 0, -1);
                SendMessage(gConsole->hwndBuffer, EM_REPLACESEL, FALSE, (LPARAM)"");
                UpdateWindow(gConsole->hwndBuffer);
                break;
            }
            break;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // Passes it on if unproccessed
    }

    LONG WINAPI InputLineWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg)
        {
        case WM_KILLFOCUS:
            if ((HWND)wParam == gConsole->hWnd)
            {
                SetFocus(hWnd);
                return 0;
            }
            break;
        case WM_CHAR:
            if (wParam == 13)
            {
                memset(gConsole->inputBuffer, 0, sizeof(CONSOLE_MAX_INPUTBUFFER));
                GetWindowText(gConsole->hwndInputLine, gConsole->inputBuffer, CONSOLE_MAX_INPUTBUFFER);
                SetWindowText(gConsole->hwndInputLine, "");

                gConsole->logDebug(gConsole->inputBuffer);
            }
            break;
        }
        return CallWindowProc(gConsole->inputLineWndProc, hWnd, uMsg, wParam, lParam);
    }

    Console::Console(const oglElements::WinObj& win) :
        hWnd{ 0 }
        , maxLines{ CONSOLE_MAX_LINES }
        , linecounter{ 0 }
    {
        Window = win;
    }

    Console::~Console()
    {
        if (hWnd) {
            ShowWindow(hWnd, SW_HIDE);
            CloseWindow(hWnd);
            DestroyWindow(hWnd);
            hWnd = 0;
        }
        if (inputBuffer) free(inputBuffer);
        inputBuffer = 0;
    }

    void Console::init(HINSTANCE parentHInstance)
    {
        HDC			hDC;
        RECT		wndposition;
        WNDCLASS	wc;
        int			DEDSTYLE;

        const char8* title = "Console";

        wndposition.left = Window.left;
        wndposition.right = Window.width;
        wndposition.top = Window.top;
        wndposition.bottom = Window.height;

        memset(&wc, 0, sizeof(wc));
        wc.style = 0;
        wc.lpfnWndProc = (WNDPROC)ConsoleProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = parentHInstance;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);  // Load The Default Icon
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
        wc.lpszMenuName = 0;
        wc.lpszClassName = title;

        if (!RegisterClass(&wc))
            return;

        DEDSTYLE = WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        AdjustWindowRect(&wndposition, DEDSTYLE, FALSE);

        hDC = GetDC(GetDesktopWindow());
        ReleaseDC(GetDesktopWindow(), hDC);

        hWnd = CreateWindowEx(0,
            title, title,
            DEDSTYLE,
            wndposition.left, wndposition.top, wndposition.right, wndposition.bottom,
            NULL,
            NULL,
            parentHInstance,
            NULL);

        if (!hWnd)
            return;

        hfont = win32_NewFont(hDC, "Courier New");
        Rectui uipos;

        // create the input line
        uipos[0] = 6;
        uipos[1] = 400;
        uipos[2] = 528;
        uipos[3] = 20;
        hwndInputLine = win32_NewEdit(hWnd, INPUT_ID, uipos);
        win32_SetFont(hwndInputLine, hfont);
        inputLineWndProc = win32_SetWndProc(hwndInputLine, (long)InputLineWndProc);

        // create the button copy
        uipos[0] = 5;
        uipos[1] = 425;
        uipos[2] = 72;
        uipos[3] = 24;
        hwndButtonCopy = win32_NewButton(hWnd, COPY_ID, uipos, "Copy");

        // create the button clear
        uipos[0] = 82;
        uipos[1] = 425;
        uipos[2] = 72;
        uipos[3] = 24;
        hwndButtonClear = win32_NewButton(hWnd, CLEAR_ID, uipos, "Clear");

        // create the button quit
        uipos[0] = 462;
        uipos[1] = 425;
        uipos[2] = 72;
        uipos[3] = 24;
        hwndButtonClear = win32_NewButton(hWnd, QUIT_ID, uipos, "Quit");

        // create the scrollbuffer
        uipos[0] = 6;
        uipos[1] = 40;
        uipos[2] = 780;
        uipos[3] = 354;
        hwndBuffer = win32_NewScrollArea(hWnd, EDIT_ID, uipos);
        win32_SetFont(hwndBuffer, hfont);

        hbrEditBackground = CreateSolidBrush(RGB(0x00, 0x00, 0xB0));

        inputBuffer = (char8*)malloc(CONSOLE_MAX_INPUTBUFFER);

        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        SetForegroundWindow(hWnd);
        SetFocus(hwndInputLine);
    }

    void Console::logDebug(const std::string& msg)
    {
        pushString(msg, 0);
    }

    void Console::logEvent(const std::string& msg)
    {
        pushString(msg, 1);
    }

    void Console::logError(const std::string& msg)
    {
        pushString(msg, 2);
    }

    void Console::pushString(const std::string& msg, int msgType)
    {
        currentLines++;
        if (currentLines > maxLines)
        {
            currentLines = 0;
            SendMessage(hwndBuffer, EM_SETSEL, 0, -1);
            SendMessage(hwndBuffer, EM_REPLACESEL, FALSE, (LPARAM)"");
            UpdateWindow(hwndBuffer);
        }

        this->msgType = msgType;
        SendMessage(this->hwndBuffer, EM_LINESCROLL, 0, 0xffff);
        SendMessage(this->hwndBuffer, EM_SCROLLCARET, 0, 0);
        SendMessage(this->hwndBuffer, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        SendMessage(this->hwndBuffer, EM_REPLACESEL, 0, (LPARAM)msg.c_str());
    }
}