#pragma once
#include "framework.h"

namespace QMedia {
    class QIPlayerContext;
}
class VideoRenderWindow;
class MainWindow
{

private:
    static LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT onReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK resizeChildWindowsProc(HWND hwndChild, LPARAM lParam);



public:
    MainWindow(HINSTANCE hInstance, int nCmdShow);

    ~MainWindow();

    MainWindow(const MainWindow&) = delete;

    MainWindow(MainWindow&&) = delete;

    MainWindow& operator=(const MainWindow&) = delete;

    MainWindow& operator=(MainWindow&&) = delete;

    HWND getHWnd();
private:
    LRESULT onCreate();
    LRESULT onResize();

     
    HWND createVideoRenderWindow(HWND parent_hwnd);

    static int getRenderWindowHeight(int parent_window_height);
    static int getRenderWindowWidth(int parent_window_width);

    bool notifyResizeToPlayer(LPRECT proot_window_rect);
private:

    HWND mHwnd;
    HINSTANCE mHinstance;
    VideoRenderWindow * mpVideoRenderWindow;


    static const int MAX_LOADSTRING = 100;
    WCHAR mTitle[MAX_LOADSTRING];                  // 标题栏文本
    WCHAR mWindowClass[MAX_LOADSTRING];            // 主窗口类名


    QMedia::QIPlayerContext* mpPlayerContext;
};

 