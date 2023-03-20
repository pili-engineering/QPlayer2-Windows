#pragma once
#include "framework.h"
class VideoRenderWindow
{
private:
    
    LRESULT onReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    VideoRenderWindow(HWND parent_hwnd, HINSTANCE hInstance);

    ~VideoRenderWindow();

    VideoRenderWindow(const VideoRenderWindow&) = delete;

    VideoRenderWindow(VideoRenderWindow&&) = delete;

    VideoRenderWindow& operator=(const VideoRenderWindow&) = delete;

    VideoRenderWindow& operator=(VideoRenderWindow&&) = delete;

    HWND getHWnd();
private:
    
    HWND mHwnd;
};

