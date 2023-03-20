//#include "VideoRenderWindow.h"
//
//
//LRESULT VideoRenderWindow::renderViewProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    VideoRenderWindow* prender_view = (VideoRenderWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//    if (prender_view == nullptr)
//        return(DefWindowProc(hwnd, uMsg, wParam, lParam));
//    else
//        return prender_view->onReceiveMessage(hwnd, uMsg, wParam, lParam);
//}
//
//LRESULT VideoRenderWindow::onReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return LRESULT();
//}
//
//VideoRenderWindow::VideoRenderWindow(HWND parent_hwnd, HINSTANCE hInstance)
//    :mHwnd(nullptr)
//{
//
//}
//
//HWND VideoRenderWindow::getHWnd()
//{
//    return mHwnd;
//}
