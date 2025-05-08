#include "TaskbarWindow.h"
#include <wingdi.h>

TaskbarWindow::TaskbarWindow(): BaseWindow { L"GDI window", WS_EX_TOOLWINDOW | WS_EX_LAYERED, WS_POPUP | WS_SYSMENU }
{

	m_font.reset(CreateFontW(
		m_fontSize * GetDpi() / 96.0,
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
	MoveWindow(m_hwnd.get(), 3085, 12, 142, 48, true);
	SetWindowPos(m_hwnd.get(), HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetLayeredWindowAttributes(m_hwnd.get(), RGB(255, 255, 255), 0, LWA_COLORKEY);
}

void TaskbarWindow::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(hwnd, &ps);

	auto self = getSelfFromHwnd(hwnd);
	RECT rect = self->ClientRect();

	//auto memBitmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	//auto memDC = CreateCompatibleDC(nullptr);
	//auto oldBit = SelectObject(memDC, memBitmap);



	auto oldFont = reinterpret_cast<HFONT>(SelectObject(hdc, self->m_font.get()));

	SetTextColor(hdc, RGB(0, 0, 0));

	//FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
	//FillRect(hdc, &ps.rcPaint, self->m_backgroundBrush);
	DrawText(hdc, L"Text in taskbar", -1, &rect, DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc, oldFont);

	//BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.left, memDC, 0, 0, SRCCOPY);
	//
	//SelectObject(memDC, oldBit);
	//DeleteObject(memBitmap);
	//DeleteDC(memDC);


	EndPaint(hwnd, &ps);
}
