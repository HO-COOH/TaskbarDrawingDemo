#pragma once
#include <Windows.h>
#include "BaseWindow.hpp"
#include <wil/resource.h>

class TaskbarWindow : public BaseWindow<TaskbarWindow, L"Gdi window">
{
	constexpr static auto m_fontSize = 16 * 1.5;
	constexpr static std::wstring_view FontFamily{ TEXT("Microsoft YaHei") };
	wil::unique_hfont m_font;
public:
	TaskbarWindow();

	static void OnPaint(HWND hwnd);
};

