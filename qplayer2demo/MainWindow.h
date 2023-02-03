#pragma once
#include "framework.h"
class VideoRenderWindow;
class MainWindow
{

private:
    static LRESULT CALLBACK renderViewProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT onReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK resizeChildWindowsProc(HWND hwndChild, LPARAM lParam);
    static HWND createVideoRenderWindow(HWND parent_hwnd);

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
    
private:

    HWND mHwnd;
    HINSTANCE mHinstance;
    //VideoRenderWindow * mpVideoRenderWindow;


    static const int MAX_LOADSTRING = 100;
    WCHAR mTitle[MAX_LOADSTRING];                  // 标题栏文本
    WCHAR mWindowClass[MAX_LOADSTRING];            // 主窗口类名
};

 