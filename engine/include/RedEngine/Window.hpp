#pragma once

#include <string>

#include <RedEngine/Platform.hpp>

namespace red
{
LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam);

class Window
{
public:
    Window(std::wstring title);
    ~Window();

    HWND GetNativeHandle();

private:
    std::wstring m_title;
    long m_windowWidth;
    long m_windowHeight;

    HWND m_nativeWindowHandle;
};

} // namespace red
