#pragma once
#include "framework.h"


class VideoRenderWindow
{
private:
    static LRESULT CALLBACK render_window_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

    LRESULT on_receive_message(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

public:
    VideoRenderWindow(HWND parent_hwnd, HINSTANCE hinstance);

    ~VideoRenderWindow() = default;

    VideoRenderWindow(const VideoRenderWindow&) = delete;

    VideoRenderWindow(VideoRenderWindow&&) = delete;

    VideoRenderWindow& operator=(const VideoRenderWindow&) = delete;

    VideoRenderWindow                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         operator=(VideoRenderWindow&&) = delete;

    HWND get_hwnd();


private:

    HWND mHwnd;

};