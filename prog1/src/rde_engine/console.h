#pragma once
#include <rde_common/lib.h>

namespace win {

	class Console
	{
	public:
		Console(const oglElements::WinObj &win);
		~Console();

		void init(HINSTANCE parentHInstance);

		void logDebug(const std::string& msg);
		void logEvent(const std::string& msg);
		void logError(const std::string& msg);


		oglElements::WinObj Window;
		HWND		hWnd;
		HWND		hwndBuffer;
		HWND		hwndInputLine;
		HWND		hwndButtonClear;
		HWND		hwndButtonCopy;
		HWND		hwndButtonQuit;
		HFONT		hfont;
		int			currentLines, maxLines;
		int			msgType;
		char8		*inputBuffer;
		WNDPROC		inputLineWndProc;
		HBRUSH		hbrEditBackground;
		int			linecounter;
		int			logDebugfpshit;
	private:
		void		pushString(const std::string& msg,int msgType);
	};
}


EXTERN_ win::Console* gConsole;

