#pragma once
#include "framework.h"

namespace QMedia {
    class QIPlayerContext;
    class QMediaModel;
}
class VideoRenderWindow;
class PlayerWindow;
class UrlListWindow;
class MainWindow
{

private:
    static LRESULT CALLBACK main_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK resize_child_windows_proc(HWND hwndChild, LPARAM lParam);
   
    void url_Click_call_back(HWND hwnd, QMedia::QMediaModel* model);

public:
    MainWindow(HINSTANCE hInstance, int nCmdShow);

    ~MainWindow();

    MainWindow(const MainWindow&) = delete;

    MainWindow(MainWindow&&) = delete;

    MainWindow& operator=(const MainWindow&) = delete;

    MainWindow& operator=(MainWindow&&) = delete;

    HWND get_hwnd();
private:
    LRESULT on_create();
    LRESULT on_resize();
    LRESULT on_create_play_menu();
     
    //HWND createVideoRenderWindow(HWND parent_hwnd);

    static int get_render_window_height(int parent_window_height);
    static int get_render_window_width(int parent_window_width);
    void button_click(int button_id);

    void list_window_click(int item_id);

    bool notify_resize_to_player(LPRECT proot_window_rect);
private:

    HWND mHwnd;
    HINSTANCE mHinstance;


    static const int MAX_LOADSTRING = 100;
    WCHAR mTitle[MAX_LOADSTRING];                  // 标题栏文本
    WCHAR mWindowClass[MAX_LOADSTRING];            // 主窗口类名


	PlayerWindow* mpPlayerWindow;

    UrlListWindow* mUrlListView;

	HWND mPlayButton;
};

 