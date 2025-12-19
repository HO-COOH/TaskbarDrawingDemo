#include "TaskbarWindow.h"
#include <wingdi.h>

template<typename T>
static auto ScaleForDpi(T value, UINT dpi)
{
	return value * dpi / 96.0;
}

TaskbarWindow::TaskbarWindow(): BaseWindow { L"GDI window", WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT, WS_POPUP }
{
	auto const dpi = GetDpi();
	m_font.reset(CreateFontW(
		ScaleForDpi(m_fontSize, dpi),
		0,
		0,
		0,
		FW_REGULAR,
		false,
		false,
		false,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		FontFamily.data()
	));

	auto hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);
	SetParent(m_hwnd.get(), hTaskbar);

	RECT taskbarRect;
	GetWindowRect(hTaskbar, &taskbarRect);


	MoveWindow(m_hwnd.get(), taskbarRect.right - taskbarRect.left - ScaleForDpi(600, dpi), ScaleForDpi(14, dpi), ScaleForDpi(142, dpi), ScaleForDpi(48, dpi), true);
	SetWindowPos(m_hwnd.get(), HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetLayeredWindowAttributes(m_hwnd.get(), RGB(0, 0, 0), 0, LWA_COLORKEY);
}

void TaskbarWindow::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(hwnd, &ps);
	SetBkMode(hdc, TRANSPARENT);
	auto self = getSelfFromHwnd(hwnd);
	RECT rect = self->ClientRect();
	auto oldFont = reinterpret_cast<HFONT>(SelectObject(hdc, self->m_font.get()));

	SetTextColor(hdc, RGB(255, 255, 255));

	FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
	DrawText(hdc, L"Text in taskbar", -1, &rect, DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc, oldFont);
	EndPaint(hwnd, &ps);
}
