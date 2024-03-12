#include "VideoRenderWindow.h"

LRESULT VideoRenderWindow::render_window_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    VideoRenderWindow* prender_view = (VideoRenderWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (prender_view == nullptr)
        return(DefWindowProc(hwnd, u_msg, w_param, l_param));
    else
        return prender_view->on_receive_message(hwnd, u_msg, w_param, l_param);
}

LRESULT VideoRenderWindow::on_receive_message(HWND hwnd, UINT uMsg, WPARAM w_param, LPARAM l_param)
{
    return LRESULT();
}

VideoRenderWindow::VideoRenderWindow(HWND parent_hwnd, HINSTANCE hinstance)
    :mHwnd(nullptr)
{
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(parent_hwnd, GWLP_HINSTANCE);
    // ”∆µœ‘ æ¥∞ø⁄
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = render_window_proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = TEXT(L"QRenderView");
    wcex.hIconSm = NULL;


    if (!RegisterClassExW(&wcex)) {
        throw "render view create failed!";
    }


    mHwnd = CreateWindowW(wcex.lpszClassName, TEXT(L"QRenderView"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        10, 10, 80, 20, parent_hwnd, NULL, hInst, NULL);
    if (mHwnd == nullptr)
    {
        throw "render view create failed!";
    }
}

HWND VideoRenderWindow::get_hwnd()
{
    return mHwnd;
}
