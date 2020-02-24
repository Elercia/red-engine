#include <RedEngine/Engine.hpp>
#include <RedEngine/Window.hpp>
#include <RedEngine/debug/Debug.hpp>

namespace red
{
LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(wnd, &ps);
        EndPaint(wnd, &ps);
        return 0;
    }
    case WM_SIZE: {
        // Window size has been changed
        RenderingEngine& renderinEngine = GetRedInstance().GetRenderingEngine();
        renderinEngine.WindowResizeCallBack(LOWORD(lParam), HIWORD(lParam));
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    case WM_GETMINMAXINFO: {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;

        lpMMI->ptMinTrackSize.x = 320;
        lpMMI->ptMinTrackSize.y = 240;
        return 0;
    }
    default:
        return DefWindowProc(wnd, message, wParam, lParam);
    }
}

Window::Window(std::wstring title) : m_title(title), m_windowHeight(600), m_windowWidth(800)
{
    LPCWSTR windowClass = L"Window class";

    WNDCLASSEX wcex = {sizeof(WNDCLASSEX),
                       CS_HREDRAW | CS_VREDRAW,
                       MessageProc,
                       0L,
                       0L,
                       GetModuleHandle(NULL),
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       windowClass,
                       NULL};
    RegisterClassEx(&wcex);

    // Create a window using the Windows API
    RECT rc = {0, 0, m_windowWidth, m_windowHeight};

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    m_nativeWindowHandle = CreateWindow(
        windowClass, m_title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!m_nativeWindowHandle)
    {
        MessageBox(NULL, L"Cannot create window", L"Error", MB_OK | MB_ICONERROR);
        RED_ABORT("Win32 Window cannot be created");
    }

    ShowWindow(m_nativeWindowHandle, true);
    UpdateWindow(m_nativeWindowHandle);
}

Window::~Window() {}

HWND Window::GetNativeHandle() { return m_nativeWindowHandle; }
} // namespace red
