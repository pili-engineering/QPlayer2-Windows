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
#include "CurrentDataModelManager.h"
#include <iomanip>
#include <sstream>

#define TAG                     "MainWindow"
#define ID_VIDEO_RENDER_WINDOW  200
#define ID_SEEK_BAR             202
#define ID_FPS_STATIC_TEXT      203
#define ID_BITRATE_STATIC_TEXT  204
#define ID_DOWNLOAD_STATIC_TEXT 205
#define ID_TIME_STATIC_TEXT     206
#define ID_PLAYER_WINDOW        207
#define ID_URL_LIST_WINDOW      208
#define ID_FIRST_FRAME_STATIC_TEXT      209
#define ID_PLAY_STATE_STATIC_TEXT      210
#define ID_TOAST_WINDOW         211
#define ID_PAUSE_PLAY_BUTTON    301
#define ID_RESUME_PLAY_BUTTON   302


using namespace QMedia;


LRESULT MainWindow::main_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param)
{
    MainWindow* pmain_window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    
    
    switch (message)
    {
	case WM_NOTIFY:
    {
        // 滑动条通知消息
        NMHDR* nmhdr = (NMHDR*)l_param;
        if (nmhdr->code == NM_CLICK)
        {
            // 鼠标点击事件
            NMUPDOWN* nmUpDown = (NMUPDOWN*)l_param;
			/* if (nmUpDown->hdr.hwndFrom == mSeekBar)
			 {
			 }*/
        }
    }
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

		//SetWindowPos(pmain_window->mToastWindow->get_hwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		break;
    }


	case WM_HSCROLL: {
		// 处理水平滚动条事件
		if (reinterpret_cast<HWND>(l_param) == pmain_window->mSeekBar)
		{
			int notificationCode = LOWORD(w_param);  // 获取通知代码
            if (notificationCode == TB_ENDTRACK) {
				// 进度条控件的位置发生改变
				long currentPosition = SendMessage(pmain_window->mSeekBar, TBM_GETPOS, 0, 0);
				// 执行相应的操作
				// ...
				pmain_window->seek_bar_click(currentPosition);
				CurrentDataModelManager::get_instance()->set_is_seeking(true);
            }
            else if(notificationCode == TB_PAGEDOWN || notificationCode == TB_PAGEUP)
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(pmain_window->mSeekBar, &pt);

				// 获取滑动条控件的范围
				int minValue, maxValue;
				SendMessage(pmain_window->mSeekBar, TBM_GETRANGEMIN, TRUE, (LPARAM)&minValue);
				SendMessage(pmain_window->mSeekBar, TBM_GETRANGEMAX, TRUE, (LPARAM)&maxValue);
				RECT rect;
				GetClientRect(pmain_window->mSeekBar, &rect);
				// 计算点击位置对应的值
                int pos = (int)(((double)(pt.x - 10) / (rect.right - rect.left - 10)) * (CurrentDataModelManager::get_instance()->get_duration_time()));

				// 设置滑动条控件的当前值
				SendMessage(pmain_window->mSeekBar, TBM_SETPOS, TRUE, pos);
				CurrentDataModelManager::get_instance()->set_is_seeking(true);
            }
            else
            {
                CurrentDataModelManager::get_instance()->set_is_seeking(true);
            }

		}

		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, w_param, l_param);
    }
    
    return 0;
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
    
    mHwnd = CreateWindowW(mWindowClass, mTitle, WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHinstance, nullptr);

    if (mHwnd == nullptr)
    {
        throw "main window create failed!";
    }
    SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);

	CurrentDataModelManager::get_instance()->set_is_seeking(false);

	//mpCurrentDataModelManager = CurrentDataModelManager::get_instance();

    on_create();

	on_create_play_menu();
    
    add_listeners();
    
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
	mpPlayerWindow = new PlayerWindow(mHwnd, mHinstance);
	child_hwnd = mpPlayerWindow->get_hwnd();
	SetWindowLong(child_hwnd, GWL_ID, ID_PLAYER_WINDOW);
    //进度时间
    mPlayerProgressAndDurationText = CreateWindow(TEXT("STATIC"), TEXT("00:00/00:00"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_TIME_STATIC_TEXT, NULL, NULL);
    //播放暂停按钮
    mPlayButton =  CreateWindow(TEXT("BUTTON"), TEXT("Play"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 70, 54, 20, mHwnd, (HMENU)ID_PAUSE_PLAY_BUTTON, NULL, NULL);

    /*SetWindowText*/
    //进度条
    mSeekBar = CreateWindow(TRACKBAR_CLASS, TEXT("Trackbar Control"), WS_CHILD | WS_VISIBLE , 10, 40, 200, 25, mHwnd, (HMENU)ID_SEEK_BAR, NULL, NULL);
    //下载速度
    mPlayerDownLoadText = CreateWindow(TEXT("STATIC"), TEXT("download speed:"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_DOWNLOAD_STATIC_TEXT, NULL, NULL);
    //码率
    mPlayerBiteRateText = CreateWindow(TEXT("STATIC"), TEXT("biterate:"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_BITRATE_STATIC_TEXT, NULL, NULL);
    //FPS
    mFPSText = CreateWindow(TEXT("STATIC"), TEXT("FPS:"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_FPS_STATIC_TEXT, NULL, NULL);

	//FPS
	mPlayerStateText = CreateWindow(TEXT("STATIC"), TEXT("play state:"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_PLAY_STATE_STATIC_TEXT, NULL, NULL);

	mFirstFrameText = CreateWindow(TEXT("STATIC"), TEXT("first frame:"), WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, mHwnd, (HMENU)ID_FIRST_FRAME_STATIC_TEXT, NULL, NULL);


    mUrlListWindow = new UrlListWindow(mHwnd, mHinstance);
    mUrlListWindow->set_play_control_callback(
        [this](HWND hwnd, QMedia::QMediaModel* model) {
        url_Click_call_back(hwnd, model);
        }
    );
    SetWindowLong(mUrlListWindow->get_hwnd(), GWL_ID, ID_URL_LIST_WINDOW);
	mToastWindow = new toast2(mHwnd, mHinstance);
	child_hwnd = mToastWindow->get_hwnd();
	SetWindowLong(child_hwnd, GWL_ID, ID_TOAST_WINDOW);

    
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
        MoveWindow(hwndChild, 100, parent_height - 60, parent_width - 180, 25, TRUE);
    }
    else if (child_window_id == ID_PAUSE_PLAY_BUTTON)
    {
        MoveWindow(hwndChild, parent_width - 70, parent_height - 60, 60, 30, TRUE);
    }
    else if (child_window_id == ID_DOWNLOAD_STATIC_TEXT) {
        MoveWindow(hwndChild, 10, parent_height - 25, 250, 20, TRUE);
    }
    else if (child_window_id == ID_BITRATE_STATIC_TEXT) {
        MoveWindow(hwndChild, 260, parent_height - 25, 150, 20, TRUE);
    }
    else if (child_window_id == ID_FPS_STATIC_TEXT) {
        MoveWindow(hwndChild, 420, parent_height - 25, 100, 20, TRUE);
    }
    else if (child_window_id == ID_FIRST_FRAME_STATIC_TEXT)
    {
        MoveWindow(hwndChild, 530, parent_height - 25, 170, 20, TRUE);
    }
	else if (child_window_id == ID_PLAY_STATE_STATIC_TEXT)
	{
		MoveWindow(hwndChild, 710, parent_height - 25, 220, 20, TRUE);
	}
    else if (child_window_id == ID_URL_LIST_WINDOW)
    {
        MoveWindow(hwndChild, parent_width - 310 ,10, 300, parent_height - 280, TRUE);
    }
	else if (child_window_id == ID_TOAST_WINDOW)
	{
		MoveWindow(hwndChild, parent_width - 310, parent_height - 280, 300, 200, TRUE);
	}
    return TRUE;
}


int MainWindow::get_render_window_height(int parent_window_height)
{
    if (parent_window_height - 80 < 0) {
        return 0;
    }
    return parent_window_height - 80;
}

int MainWindow::get_render_window_width(int parent_window_width)
{
	if (parent_window_width - 320 < 0) {
		return 0;
	}
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
void MainWindow::seek_bar_click(long current_time) {
    if (mpPlayerWindow != nullptr) {
        mpPlayerWindow->get_control_handler()->seek(current_time*100);
    }
	RECT clientRect;
	GetClientRect(mSeekBar, &clientRect);

	int progressBarWidth = clientRect.right - clientRect.left;
	std::string str = "seek_bar_click : " + std::to_string(current_time) + "width : " + std::to_string(progressBarWidth);
	DemoLog::log_string(TAG, __LINE__, str.c_str());
}
void  MainWindow::button_click(int button_id) {
    if (mpPlayerWindow == nullptr) {
        DemoLog::log_string(TAG, __LINE__, "mPlayerWindow is null");
        return;
    }
    switch (button_id)
    {
    case ID_PAUSE_PLAY_BUTTON: {
        //SetWindowLong(mPlayButton, GWL_ID, ID_RESUME_BUTTON);

		SetWindowLongPtr(mPlayButton, GWL_ID, (LONG_PTR)ID_RESUME_PLAY_BUTTON);
        SetWindowText(mPlayButton, TEXT("Resume"));
        mpPlayerWindow->get_control_handler()->pause_render();
        break;
    }
	case ID_RESUME_PLAY_BUTTON: {
        SetWindowLongPtr(mPlayButton, GWL_ID, (LONG_PTR)ID_PAUSE_PLAY_BUTTON);
		SetWindowText(mPlayButton, TEXT("Play"));
		mpPlayerWindow->get_control_handler()->resume_render();
		break;
	}
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
    case ID_RENDER_RADIO_AUTO_BUTTON:
        mpPlayerWindow->get_render_handler()->set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO);
        break;
    case ID_RENDER_RADIO_STRETCH_BUTTON:
		mpPlayerWindow->get_render_handler()->set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_STRETCH);
		break;
	case ID_RENDER_RADIO_FULL_SCREEN_BUTTON:
		mpPlayerWindow->get_render_handler()->set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_FULL_SCREEN);
		break;
	case ID_RENDER_RADIO_4_3_BUTTON:
		mpPlayerWindow->get_render_handler()->set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_4_3);
		break;
	case ID_RENDER_RADIO_16_9_BUTTON:
		mpPlayerWindow->get_render_handler()->set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_16_9);
		break;
	case ID_BLIND_NONE_BUTTON:
		mpPlayerWindow->get_render_handler()->set_blind_type(QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE);
		break;
	case ID_BLIND_RED_BUTTON:
		mpPlayerWindow->get_render_handler()->set_blind_type(QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_RED);
		break;
	case ID_BLIND_GREEN_BUTTON:
		mpPlayerWindow->get_render_handler()->set_blind_type(QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_GREEN);
		break;
	case ID_BLIND_BLUE_BUTTON:
		mpPlayerWindow->get_render_handler()->set_blind_type(QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_BLUE);
		break;
	case ID_SEI_CLOSE_BUTTON:
		mpPlayerWindow->get_control_handler()->set_sei_enable(false);
		break;
	case ID_SEI_OPEN_BUTTON:
		mpPlayerWindow->get_control_handler()->set_sei_enable(true);
		break;
	//最小化窗口---后台播放
	case ID_BACKGROUND_OPEN_BUTTON:
		//mpPlayerWindow->get_control_handler()->;
		break;
	case ID_BACKGROUND_CLOSE_BUTTON:
		//mpPlayerWindow->get_control_handler()->;
		break;
    //清晰度切换
	case ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON:
		//mpPlayerWindow->get_control_handler()->set_;
		break;
	case ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON:
		//mpPlayerWindow->get_control_handler()->set_;
		break;
	case ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON:
		//mpPlayerWindow->get_control_handler()->set_;
		break;

	//字幕设置
	case ID_SUBTITLE_CLOSE_BUTTON:
		break;
	case ID_SUBTITLE_CHINESE_BUTTON:
		break;
    case ID_SUBTITLE_ENGLISH_BUTTON:
        break;
	case ID_PLAY_SPEED_0_5_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(0.5);
		break;
	case ID_PLAY_SPEED_0_7_5_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(0.75);
		break;
	case ID_PLAY_SPEED_1_0_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(1.0);
		break;
	case ID_PLAY_SPEED_1_2_5_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(1.25);
		break;
	case ID_PLAY_SPEED_1_5_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(1.5);
		break;
	case ID_PLAY_SPEED_2_0_BUTTON:
		mpPlayerWindow->get_control_handler()->set_speed(2.0);
		break;
	case ID_MUTE_CLOSE_BUTTON:
		mpPlayerWindow->get_control_handler()->set_mute(false);
		break;
	case ID_MUTE_OPEN_BUTTON:
		mpPlayerWindow->get_control_handler()->set_mute(true);
		break;
    default:
        break;
    }
}

std::string  MainWindow::to_date_string(long time) {
	int inner_time = time / 1000;
	std::string inner_time_str = "";
	if (inner_time < 60) {
		if (inner_time < 10)
		{
            inner_time_str = "00:0" + std::to_string(inner_time);
		}
		else
		{
            inner_time_str = "00:" + std::to_string(inner_time);
		}
	}
	else {
		int second = inner_time % 60;
		int min = inner_time / 60;
		if (min < 60)
		{
			if (min < 10)
			{
                inner_time_str = "0" + std::to_string(min) + ":";
			}
			else
			{
                inner_time_str = std::to_string(min) + ":";
			}
            if (second < 10)
            {
                inner_time_str = inner_time_str + "0" + std::to_string(second);
            } 
            else
            {
                inner_time_str += std::to_string(second);
            }
		}
		else
		{
			int hour = min / 60;
			min = min % 60;
            inner_time_str = std::to_string(hour) + ":";
			if (min < 10)
			{
				inner_time_str = "0" + std::to_string(min) + ":";
			}
			else
			{
				inner_time_str = std::to_string(min) + ":";
			}
			if (second < 10)
			{
				inner_time_str = inner_time_str + "0" + std::to_string(second);
			}
			else
			{
				inner_time_str += std::to_string(second);
			}
		}
	}
    return inner_time_str;
}
void MainWindow::add_listeners() {
	mpPlayerWindow->get_control_handler()->add_player_state_change_listener(this);
    mpPlayerWindow->get_render_handler()->add_render_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_fps_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_download_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_audio_data_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_audio_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_authentication_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_bite_rate_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_buffering_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_command_not_allow_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_download_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_format_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_media_network_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_progress_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_quality_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_seek_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_sei_data_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_shoot_video_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_speed_change_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_subtitle_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_video_data_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_video_decode_type_listener(this);
    mpPlayerWindow->get_control_handler()->add_player_video_frame_size_change_listener(this);
    
}


/***********************qplayer listeners***********************/
void MainWindow::on_state_changed(QMedia::QPlayerState state) {
	DemoLog::log_string(TAG, __LINE__, "QPlayerState");
    //mpCurrentDataModelManager->set_player_state(state);
    CurrentDataModelManager::get_instance()->set_player_state(state);
    std::string state_string = "player state: ";
    switch (state)
    {
    case QMedia::QPlayerState::NONE:
        state_string += "none";
        break;
	case QMedia::QPlayerState::INIT:
		state_string += "init";
        break;
	case QMedia::QPlayerState::PREPARE:
		state_string += "prepare";
        break;
	case QMedia::QPlayerState::PLAYING:
		CurrentDataModelManager::get_instance()->set_is_seeking(false);
		state_string += "playing";
        break;
	case QMedia::QPlayerState::PAUSED_RENDER:
		state_string += "paused_render";
        break;
	case QMedia::QPlayerState::COMPLETED:
		state_string += "completed";
        break;
	case QMedia::QPlayerState::SEEKING:
		state_string += "seeking";
        break;
	case QMedia::QPlayerState::STOPPED:
		state_string += "stopping";
        break;
	case QMedia::QPlayerState::MISTAKE:
		state_string += "mistake";
        break;
	case QMedia::QPlayerState::END:
		state_string += "end";
        break;
	case QMedia::QPlayerState::MEDIA_ITEM_PREPARE:
		state_string += "media_item_prepare";
        break;
	case QMedia::QPlayerState::RELEASE:
		state_string += "release";
        break;
	default:
		state_string += "state is invalid";
        break;
    }
    SetWindowText(mPlayerStateText, state_string.c_str());

}

void MainWindow::on_first_frame_rendered(long elapsed_time) {
    DemoLog::log_string(TAG, __LINE__, "elapsed_time");
    std::string text = "first frame: " + std::to_string(elapsed_time) + "ms";
    
    SetWindowText(mFirstFrameText, text.c_str());
    mToastWindow->add_item(text);
}
void MainWindow::on_fps_changed(long fps) {

    std::string text = "FPS: " + std::to_string(fps);
    SetWindowText(mFPSText, text.c_str());
}

void  MainWindow::on_audio_data(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, uint8_t* audio_data, uint64_t size) {

}

void  MainWindow::on_mute_changed(bool is_mute) {}

void  MainWindow::on_authentication_failed(QMedia::QAuthenticationErrorType error) {}

void  MainWindow::on_authentication_success() {}

void  MainWindow::on_bite_rate_changed(int bit_rate) {

	std::string text = "biterate: " + std::to_string(bit_rate/1000) + "kbps";
	SetWindowText(mPlayerBiteRateText, text.c_str());
}

void  MainWindow::on_buffering_start() {}

void  MainWindow::on_buffering_end() {}

void  MainWindow::on_command_not_allow(std::string command_name, QMedia::QPlayerState state) {}

void  MainWindow::on_download_changed(int download_speed, int buffer_pos) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << download_speed / 1000.0;
	std::string result_str = oss.str();
	std::string text = "download speed: " + result_str + "kb/s";
    SetWindowText(mPlayerDownLoadText, text.c_str());

}

void  MainWindow::on_format_not_support() {}

void  MainWindow::on_reconnect_start(std::string user_type, QMedia::QUrlType url_type, std::string url, int retry_time) {}

void  MainWindow::on_reconnect_end(std::string user_type, QMedia::QUrlType url_type, std::string url, int retry_time, QMedia::QOpenError error) {}

void  MainWindow::on_open_failed(std::string user_type, QMedia::QUrlType url_type, std::string url, QMedia::QOpenError error) {}

void  MainWindow::on_progress_changed(long progress, long duration) {
    if (CurrentDataModelManager::get_instance()->get_duration_time() != duration/100)
	{
        CurrentDataModelManager::get_instance()->set_duration_time(duration / 100);
        SendMessage(mSeekBar, TBM_SETRANGE, TRUE, MAKELONG(0, CurrentDataModelManager::get_instance()->get_duration_time()));
    } 
    std::string progress_time_str = to_date_string(progress);
    std::string duraion_time_str = to_date_string(duration);
	std::string text = progress_time_str + "/" + duraion_time_str;
    if (!CurrentDataModelManager::get_instance()->get_is_seeking())
	{
		SendMessage(mSeekBar, TBM_SETPOS, TRUE, progress / 100);
    }
    if (mProgressTimeStr == progress_time_str) {
        return;
    }
	SetWindowText(mPlayerProgressAndDurationText, text.c_str());
    mProgressTimeStr = progress_time_str;
}

void  MainWindow::on_quality_switch_start(std::string user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) {}

void  MainWindow::on_quality_switch_complete(std::string user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) {}

void  MainWindow::on_quality_switch_canceled(std::string user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) {}

void  MainWindow::on_quality_switch_failed(std::string user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) {}

void  MainWindow::on_quality_switch_retry_later(std::string user_type, QMedia::QUrlType url_type) {}

void  MainWindow::on_seek_success() {

	//CurrentDataModelManager::get_instance()->set_is_seeking(false);
}

void  MainWindow::on_seek_failed() {

    //CurrentDataModelManager::get_instance()->set_is_seeking(false);
}

void  MainWindow::on_shoot_video_success(uint8_t* image_data, uint64_t size, int width, int height, QMedia::QShootVideoType type) {}

void  MainWindow::on_shoot_video_failed() {}

void  MainWindow::on_sei_data(uint8_t* data, uint64_t size) {}

void  MainWindow::on_speed_changed(int speed) {}

void  MainWindow::on_subtitle_text_changed(std::string text) {}

void  MainWindow::on_subtitle_name_changed(std::string name) {}

void  MainWindow::on_subtitle_enable(bool enable) {}

void  MainWindow::on_subtitle_loaded(std::string name, bool result) {}

void  MainWindow::on_subtitle_decoded(std::string name, bool result) {}

void  MainWindow::on_video_data(int width, int height, QMedia::QVideoType video_type, uint8_t* buffer, uint64_t size) {}

void  MainWindow::on_video_decode_by_type(QMedia::QDecoderType type) {}

void  MainWindow::on_not_support_codec_format(int codec_id) {}

void  MainWindow::on_video_frame_size_changed(int width, int height) {}