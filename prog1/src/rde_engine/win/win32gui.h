#pragma once
#include <rde_common/lib.h>


INLINE_ HWND win32_NewButton(HWND& hwnd, int Id, Rectui& rect, const char8* text)
{
	HWND btn = CreateWindowEx(0,
		"button", NULL, BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		rect[0], rect[1], rect[2], rect[3], hwnd, (HMENU)Id, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);
	SendMessage(btn, WM_SETTEXT, 0, (LPARAM)text);
	return btn;
}

INLINE_ HWND win32_NewEdit(HWND& hwnd, int Id, Rectui& rect)
{
	HWND edit = CreateWindowEx(0,
		"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		rect[0], rect[1], rect[2], rect[3], hwnd, (HMENU)Id, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);
	return edit;
}

INLINE_ HWND win32_NewScrollArea(HWND& hwnd, int Id, Rectui& rect)
{
	HWND edit = CreateWindowEx(0,
		"edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		rect[0], rect[1], rect[2], rect[3], hwnd, (HMENU)Id, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);
	return edit;
}

INLINE_ WNDPROC win32_SetWndProc(HWND& hwnd, LONG wndProc)
{
	return (WNDPROC)SetWindowLong(hwnd, GWLP_WNDPROC, wndProc);
}

INLINE_ void win32_SetFont(HWND& hwnd, HFONT& font)
{
	SendMessage(hwnd, WM_SETFONT, (WPARAM)font, 0);
}

INLINE_ HFONT win32_NewFont(HDC& hdc, const char8* fontname)
{
	int	nHeight = -MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	HFONT font = CreateFont(nHeight,
		0,
		0,
		0,
		FW_LIGHT,
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_MODERN | FIXED_PITCH,
		fontname);
	return font;
}

