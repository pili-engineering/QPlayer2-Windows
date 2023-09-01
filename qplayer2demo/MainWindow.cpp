#include "MainWindow.h"
#include "resource.h"
#include <commctrl.h>
#include "VideoRenderWindow.h"
#include "PlayerWindow.h"
#include "DemoLog.h"
#include "QIPlayerContext.h"
#include "QIPlayerControlHandler.h"
#include "QIPlayerRenderHandler.h"
#include "QMediaModelBuilder.h"
#include "QMediaModel.h"
#include <iostream>
#include <filesystem>
#include "UrlListWindow.h"
#include "PlayerMenuSettingModelManager.h"

#define TAG                     "MainWindow"
#define ID_VIDEO_RENDER_WINDOW  200
#define ID_PAUSE_PLAY_BUTTON    201
#define ID_SEEK_BAR             202
#define ID_FPS_STATIC_TEXT      203
#define ID_BITRATE_STATIC_TEXT  204
#define ID_DOWNLOAD_STATIC_TEXT 205
#define ID_TIME_STATIC_TEXT     206
#define ID_PLAYER_WINDOW        207
#define ID_URL_LIST_WINDOW      208


using namespace QMedia;

LRESULT MainWindow::main_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param)
{
    MainWindow* pmain_window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    
    
    switch (message)
    {
    case WM_CREATE:
    {
        //pmain_window->onCreatePlayMenu();
    }
    break;
    case WM_SIZE:
    {
        if (pmain_window != nullptr)
        {
            pmain_window->on_resize();
        }
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(w_param);
        pmain_window->button_click(wmId);
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
            return DefWindowProc(hwnd, message, w_param, l_param);
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
        return DefWindowProc(hwnd, message, w_param, l_param);
    }
    
    return 0;
}

void MainWindow::list_window_click(int item_id) {
    char buff[200];
    snprintf(buff, sizeof(buff),"list CLick %d", item_id);
    DemoLog::log_string(TAG, __LINE__,buff);
}


MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
	:mHinstance(hInstance),
    mHwnd(nullptr)
{
    LoadStringW(mHinstance, IDS_APP_TITLE, mTitle, MAX_LOADSTRING);
    LoadStringW(mHinstance, IDC_QPLAYER2DEMO, mWindowClass, MAX_LOADSTRING);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = main_window_proc;
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
    
    on_create();


	on_create_play_menu();
 
    ShowWindow(mHwnd, nCmdShow);
    UpdateWindow(mHwnd);
}

MainWindow::~MainWindow()
{
}

HWND MainWindow::get_hwnd()
{
	return mHwnd;
}

LRESULT MainWindow::on_create()
{
    HWND child_hwnd;
    //视频显示窗口
    //child_hwnd = createVideoRenderWindow(mHwnd);
	mpPlayerWindow = new PlayerWindow(mHwnd, mHinstance);
	child_hwnd = mpPlayerWindow->get_hwnd();
	SetWindowLong(child_hwnd, GWL_ID, ID_PLAYER_WINDOW);
    //进度时间
    CreateWindow(TEXT("STATIC"), TEXT("00:07/03:56"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_TIME_STATIC_TEXT, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_TIME_STATIC_TEXT);
    //播放暂停按钮
    CreateWindow(TEXT("BUTTON"), TEXT("Play"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 70, 54, 20, mHwnd, (HMENU)ID_PAUSE_PLAY_BUTTON, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_PAUSE_PLAY_BUTTON);
    /*SetWindowText*/
    //进度条
    CreateWindow(TRACKBAR_CLASS, TEXT("Trackbar Control"), WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, 10, 40, 200, 30, mHwnd, (HMENU)ID_SEEK_BAR, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_SEEK_BAR);
    //下载速度
     CreateWindow(TEXT("STATIC"), TEXT("111KB/s"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_DOWNLOAD_STATIC_TEXT, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_DOWNLOAD_STATIC_TEXT);
    //码率
    CreateWindow(TEXT("STATIC"), TEXT("842kbps"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_BITRATE_STATIC_TEXT, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_BITRATE_STATIC_TEXT);
    //FPS
    CreateWindow(TEXT("STATIC"), TEXT("FPS:25"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_FPS_STATIC_TEXT, NULL, NULL);
    //SetWindowLong(child_hwnd, GWL_ID, ID_FPS_STATIC_TEXT);
    mUrlListView = new UrlListWindow(mHwnd, mHinstance);
    mUrlListView->set_play_control_callback(
        [this](HWND hwnd, QMedia::QMediaModel* model) {
        url_Click_call_back(hwnd, model);
        }
    );
    SetWindowLong(mUrlListView->get_hwnd(), GWL_ID, ID_URL_LIST_WINDOW);
    


    
    return TRUE;
}

void MainWindow::url_Click_call_back(HWND hwnd, QMedia::QMediaModel* model) {
    //MainWindow* main_window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (mpPlayerWindow != nullptr)
    {
        mpPlayerWindow->get_control_handler()->play_media_model(model, 0);
    }
}
LRESULT MainWindow::on_create_play_menu() {
    
    PlayerMenuSettingModelManager* setting_menu_manager = new PlayerMenuSettingModelManager(mHwnd);
    std::list<PlayerMenuSettingModel*>* setting_model = setting_menu_manager->get_menu_setting_model();

    HMENU base_menu = CreateMenu();
	for (int parent_index = 0; parent_index < setting_model->size(); parent_index++) {
        auto parent_it = setting_model->begin();
        std::advance(parent_it, parent_index);
        
		AppendMenu(base_menu, MF_STRING | MF_POPUP, (UINT_PTR)((*parent_it)->mpChildMenu->mHmenu), (*parent_it)->mName.c_str());
        for (int child_index = 0; child_index < (*parent_it)->mpChildMenu->mpMenus->size(); child_index++) {

			auto child_it = (*parent_it)->mpChildMenu->mpMenus->begin();
			std::advance(child_it, child_index);
			AppendMenu((*parent_it)->mpChildMenu->mHmenu, MF_STRING, (*child_it)->mId, (*child_it)->mName.c_str());
        }

    }
    SetMenu(mHwnd, base_menu);

    return 0;
}
LRESULT MainWindow::on_resize()
{
    RECT root_window_rect;
    GetClientRect(mHwnd, &root_window_rect);
    EnumChildWindows(mHwnd, resize_child_windows_proc, (LPARAM)(&root_window_rect));
    notify_resize_to_player(&root_window_rect);
    return TRUE;
}

BOOL MainWindow::resize_child_windows_proc(HWND hwndChild, LPARAM lParam)
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
    if (child_window_id == ID_PLAYER_WINDOW) {
        MoveWindow(hwndChild, 10, 10, get_render_window_width(parent_width), get_render_window_height(parent_height), TRUE);
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
    else if (child_window_id == ID_URL_LIST_WINDOW)
    {
        MoveWindow(hwndChild, parent_width - 310 ,10, 300, parent_height - 80, TRUE);
    }
    printf("child id=%d", child_window_id);

    return TRUE;
}


int MainWindow::get_render_window_height(int parent_window_height)
{
    return parent_window_height - 80;
}

int MainWindow::get_render_window_width(int parent_window_width)
{
    return parent_window_width - 320;
}

bool MainWindow::notify_resize_to_player(LPRECT proot_window_rect)
{
    
    if (mpPlayerWindow != nullptr)
    {
        RECT render_window_rect;
        GetClientRect(mpPlayerWindow->get_hwnd(), &render_window_rect);
        return true;

    }

    return false;
}
void  MainWindow::button_click(int button_id) {
    if (mpPlayerWindow == nullptr) {
        DemoLog::log_string(TAG, __LINE__, "mPlayerWindow is null");
        return;
    }
    switch (button_id)
    {
    case ID_RESUME_BUTTON: {
        mpPlayerWindow->get_control_handler()->resume_render();
        break;
    }
    case ID_PAUSE_BUTTON:
        mpPlayerWindow->get_control_handler()->pause_render();
        break;
    case ID_STOP_BUTTON:
        mpPlayerWindow->get_control_handler()->stop();
        break;
    case ID_AUTO_DECODER_BUTTON:
		mpPlayerWindow->get_control_handler()->set_decode_type(QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO);
        break;
	case ID_HARD_DECODER_BUTTON:
		mpPlayerWindow->get_control_handler()->set_decode_type(QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY);
        break;
	case ID_SOFT_DECODER_BUTTON:
		mpPlayerWindow->get_control_handler()->set_decode_type(QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_SOFT_PRIORITY);
		break;
	case ID_SEEK_NORMAL_BUTTON:
		mpPlayerWindow->get_control_handler()->set_seek_mode(QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL);
		break;
	case ID_SEEK_ACCURATE_BUTTON:
		mpPlayerWindow->get_control_handler()->set_seek_mode(QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_ACCURATE);
		break;
	case ID_SEEK_START_PLAYING_BUTTON:
		mpPlayerWindow->get_control_handler()->set_start_action(QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING);
		break;
	case ID_SEEK_START_PAUSE_BUTTON:
		mpPlayerWindow->get_control_handler()->set_start_action(QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PAUSE);
		break;
	case ID_AURHENTICATION_BUTTON:
		mpPlayerWindow->get_control_handler()->force_authentication_from_network();
		break;
    default:
        break;
    }
}