#include "MainWindow.h"
#include "resource.h"
#include <commctrl.h>
#include "VideoRenderWindow.h"

#include "QIPlayerContext.h"
#include "QIPlayerControlHandler.h"
#include "QIPlayerRenderHandler.h"
#include "QMediaModelBuilder.h"
#include "QMediaModel.h"
#include <iostream>
#include <filesystem>

#define ID_VIDEO_RENDER_WINDOW  200
#define ID_PAUSE_PLAY_BUTTON    201
#define ID_SEEK_BAR             202
#define ID_FPS_STATIC_TEXT      203
#define ID_BITRATE_STATIC_TEXT  204
#define ID_DOWNLOAD_STATIC_TEXT 205
#define ID_TIME_STATIC_TEXT     206
using namespace QMedia;

LRESULT MainWindow::mainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* pmain_window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (pmain_window != nullptr)
    {
        pmain_window->onReceiveMessage(hwnd, message, wParam, lParam);
    }

    
    switch (message)
    {
    case WM_CREATE:
    {

    }
    break;
    case WM_SIZE:
    {
        if (pmain_window != nullptr)
        {
            pmain_window->onResize();
        }
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT MainWindow::onReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (mpPlayerContext != nullptr)
    {
        if (mpPlayerContext->on_receive_message(hwnd, uMsg, wParam, lParam)) {
            return 0;
        }
    }

    return 0;
}

MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
	:mHinstance(hInstance),
    mpVideoRenderWindow(nullptr),
    mHwnd(nullptr),
    mpPlayerContext(nullptr)
{
    LoadStringW(mHinstance, IDS_APP_TITLE, mTitle, MAX_LOADSTRING);
    LoadStringW(mHinstance, IDC_QPLAYER2DEMO, mWindowClass, MAX_LOADSTRING);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = mainWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = mHinstance;
    wcex.hIcon = LoadIcon(mHinstance, MAKEINTRESOURCE(IDI_QPLAYER2DEMO));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_QPLAYER2DEMO);
    wcex.lpszClassName = mWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassExW(&wcex)) {
        throw "main window  create failed!";
    }

    mHwnd = CreateWindowW(mWindowClass, mTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHinstance, nullptr);

    if (mHwnd == nullptr)
    {
        throw "main window create failed!";
    }
    SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);
    
    onCreate();

  
    mpPlayerContext = QIPlayerContext::create();
    mpPlayerContext->init(QLogLevel::LOG_VERBOSE,
        std::filesystem::current_path().string(), "", "1.3.0", "eb4136eb62d064dcacb2afedee467384", mHwnd);
    mpPlayerContext->get_render_hander()->set_window_hwnd(mpVideoRenderWindow->getHWnd());


    QMediaModelBuilder builder;
    builder.add_stream_element("", QUrlType::QAUDIO_AND_VIDEO,0,
        "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
    mpPlayerContext->get_control_handler()->play_media_model(builder.build(false), 0);
    ShowWindow(mHwnd, nCmdShow);
    UpdateWindow(mHwnd);
}

MainWindow::~MainWindow()
{
}

HWND MainWindow::getHWnd()
{
	return mHwnd;
}

LRESULT MainWindow::onCreate()
{
    HWND child_hwnd;
    //视频显示窗口
    child_hwnd = createVideoRenderWindow(mHwnd);
    SetWindowLong(child_hwnd, GWL_ID, ID_VIDEO_RENDER_WINDOW);
    //进度时间
    child_hwnd = CreateWindow(TEXT("STATIC"), TEXT("00:07/03:56"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_TIME_STATIC_TEXT);
    //播放暂停按钮
    child_hwnd = CreateWindow(TEXT("BUTTON"), TEXT("Play"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 70, 54, 20, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_PAUSE_PLAY_BUTTON);
    /*SetWindowText*/
    //进度条
    child_hwnd = CreateWindow(TRACKBAR_CLASS, TEXT("Trackbar Control"), WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, 10, 40, 200, 30, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_SEEK_BAR);
    //下载速度
    child_hwnd = CreateWindow(TEXT("STATIC"), TEXT("111KB/s"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_DOWNLOAD_STATIC_TEXT);
    //码率
    child_hwnd = CreateWindow(TEXT("STATIC"), TEXT("842kbps"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_BITRATE_STATIC_TEXT);
    //FPS
    child_hwnd = CreateWindow(TEXT("STATIC"), TEXT("FPS:25"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, NULL, NULL, NULL);
    SetWindowLong(child_hwnd, GWL_ID, ID_FPS_STATIC_TEXT);
    
    
    return TRUE;
}

LRESULT MainWindow::onResize()
{
    RECT root_window_rect;
    GetClientRect(mHwnd, &root_window_rect);
    EnumChildWindows(mHwnd, resizeChildWindowsProc, (LPARAM)(&root_window_rect));
    notifyResizeToPlayer(&root_window_rect);
    return TRUE;
}

BOOL MainWindow::resizeChildWindowsProc(HWND hwndChild, LPARAM lParam)
{
    LPRECT proot_window_rect;
    int child_window_id;
    child_window_id = GetWindowLong(hwndChild, GWL_ID);
    proot_window_rect = (LPRECT)lParam;
    if (child_window_id == 0 || proot_window_rect == nullptr) {
        return FALSE;
    }
    int parent_width = proot_window_rect->right - proot_window_rect->left;
    int parent_height = proot_window_rect->bottom- proot_window_rect->top;
    if (child_window_id == ID_VIDEO_RENDER_WINDOW) {
        MoveWindow(hwndChild, 10, 10, getRenderWindowWidth(parent_width), getRenderWindowHeight(parent_height), TRUE);
    }
    else if (child_window_id == ID_TIME_STATIC_TEXT)
    {
        MoveWindow(hwndChild, 10, parent_height - 55, 80, 20, TRUE);
    }
    else if (child_window_id == ID_SEEK_BAR)
    {
        MoveWindow(hwndChild, 100, parent_height - 60, parent_width - 180, 30, TRUE);
    }
    else if (child_window_id == ID_PAUSE_PLAY_BUTTON)
    {
        MoveWindow(hwndChild, parent_width - 70, parent_height - 60, 60, 30, TRUE);
    }
    else if (child_window_id == ID_DOWNLOAD_STATIC_TEXT) {
        MoveWindow(hwndChild, 10, parent_height - 25, 60, 20, TRUE);
    }
    else if (child_window_id == ID_BITRATE_STATIC_TEXT) {
        MoveWindow(hwndChild, 80, parent_height - 25, 60, 20, TRUE);
    }
    else if (child_window_id == ID_FPS_STATIC_TEXT) {
        MoveWindow(hwndChild, 150, parent_height - 25, 60, 20, TRUE);
    }
    //MoveWindow(hwndChild,
    //    (rcParent->right / 3) * i,
    //    0,
    //    rcParent->right / 3,
    //    rcParent->bottom,
    //    TRUE);

    //ShowWindow(hwndChild, SW_SHOW);
    printf("child id=%d", child_window_id);

    return TRUE;
}

HWND MainWindow::createVideoRenderWindow(HWND parent_hwnd)
{

    mpVideoRenderWindow = new VideoRenderWindow(parent_hwnd, nullptr);
    
    return mpVideoRenderWindow->getHWnd();
}

int MainWindow::getRenderWindowHeight(int parent_window_height)
{
    return parent_window_height - 80;
}

int MainWindow::getRenderWindowWidth(int parent_window_width)
{
    return parent_window_width - 20;
}

bool MainWindow::notifyResizeToPlayer(LPRECT proot_window_rect)
{
    
    if (mpVideoRenderWindow != nullptr && mpPlayerContext != nullptr)
    {
        RECT render_window_rect;
        GetClientRect(mpVideoRenderWindow->getHWnd(), &render_window_rect);
        mpPlayerContext->get_render_hander()->synch_window_size(
            render_window_rect.right - render_window_rect.left,
            render_window_rect.bottom - render_window_rect.top);
        return true;

    }
    //int parent_width = proot_window_rect->right - proot_window_rect->left;
    //int parent_height = proot_window_rect->bottom - proot_window_rect->top;
    //int render_window_width = getRenderWindowWidth(parent_width) - 10;
    //int render_window_height = getRenderWindowHeight(parent_height) - 10;
    //if (mpPlayerContext != nullptr)
    //{
    //    mpPlayerContext->get_render_hander()->synch_window_size(render_window_width, render_window_height);
    //    return true;

    //}
    return false;
}
