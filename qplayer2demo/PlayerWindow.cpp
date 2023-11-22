#include "PlayerWindow.h"
#include "resource.h"
#include "QIPlayerContext.h"

#include "QIPlayerControlHandler.h"
#include "QIPlayerRenderHandler.h"
#include "QMediaModelBuilder.h"
#include "QMediaModel.h"
#include "VideoRenderWindow.h"
#include "DemoLog.h"
#include <iostream>
#include <filesystem>
using namespace QMedia;

#define TAG              "PlayerWindow"
#define ID_RENDER_WINDOW 200

//构造
PlayerWindow::PlayerWindow(HWND parent_hwnd, HINSTANCE hInstance):mHwnd(nullptr),mpPlayerContext(nullptr)
{

	HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(parent_hwnd, GWLP_HINSTANCE);
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = main_player_window_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT(L"QPlayerWindow");
	wcex.hIconSm = NULL;

	if (!RegisterClassExW(&wcex)) {
		throw "PlayerWindow  create failed!";
	}

	mHwnd = CreateWindowW(wcex.lpszClassName, TEXT(L"QPlayerWindow"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		10, 10, 80, 20, parent_hwnd, NULL, hInst, NULL);
	if (mHwnd == nullptr)
	{
		throw "PlayerWindow create failed!";
	}


	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);
	mpVideoRenderWindow = new VideoRenderWindow(mHwnd, nullptr);

	SetWindowLongPtr(mpVideoRenderWindow->get_hwnd(), GWL_ID, ID_RENDER_WINDOW);


	mpPlayerContext = QIPlayerContext::create();
	mpPlayerContext->init(QLogLevel::LOG_VERBOSE, std::filesystem::current_path().string(), "com.qiniu.qplayer2", "1.3.2", "eb4136eb62d064dcacb2afedee467384", mHwnd);
	mpPlayerContext->get_render_hander()->set_window_hwnd(mpVideoRenderWindow->get_hwnd());
}

//析构
PlayerWindow::~PlayerWindow()
{
	if (mpPlayerContext != nullptr)
	{
		delete mpPlayerContext;
		mpPlayerContext = nullptr;
	}
}

//处理事件循环
LRESULT CALLBACK  PlayerWindow::main_player_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	PlayerWindow* pplayer_window = (PlayerWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (pplayer_window != nullptr) {

		 pplayer_window->on_receive_message(hwnd, message, w_param, l_param);
	}
	switch (message)
	{
	case WM_SIZE:
		if (pplayer_window != nullptr)
		{
			pplayer_window->on_resize();
		}
		break;

	case WM_CREATE:
		
	default:
		break;
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

//将消息传递给播放器
LRESULT PlayerWindow::on_receive_message(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param){
	if (mpPlayerContext != nullptr) {
		mpPlayerContext->on_receive_message(hwnd, message, w_param, l_param);
		return 0;
	}
	return -1;
}

//返回窗口句柄
HWND PlayerWindow::get_hwnd() {
	return mHwnd;
}

//修改窗口大小
LRESULT PlayerWindow::on_resize()
{
	RECT root_window_rect;
	GetClientRect(mHwnd, &root_window_rect);
	EnumChildWindows(mHwnd, resize_child_windows_proc, (LPARAM)(&root_window_rect));
	notify_resize_to_player(&root_window_rect);
	return TRUE;
}
BOOL PlayerWindow::resize_child_windows_proc(HWND hwndChild, LPARAM lParam)
{
	LPRECT proot_window_rect;
	int child_window_id;
	child_window_id = GetWindowLong(hwndChild, GWL_ID);
	proot_window_rect = (LPRECT)lParam;
	if (child_window_id == 0 || proot_window_rect == nullptr) {
		return FALSE;
	}
	int parent_width = proot_window_rect->right - proot_window_rect->left;
	int parent_height = proot_window_rect->bottom - proot_window_rect->top;
	if (child_window_id == ID_RENDER_WINDOW) {
		MoveWindow(hwndChild, 10, 10, parent_width, parent_height, TRUE);
	}
	char str[256] = "childe_id =";
	snprintf(str, sizeof(str), "%s %d", str, child_window_id);
	
	DemoLog::log_string(TAG, __LINE__, str);

	return TRUE;
}

bool PlayerWindow::notify_resize_to_player(LPRECT proot_window_rect)
{

	if (mpVideoRenderWindow != nullptr && mpPlayerContext != nullptr)
	{
		RECT render_window_rect;
		GetClientRect(mpVideoRenderWindow->get_hwnd(), &render_window_rect);
		mpPlayerContext->get_render_hander()->synch_window_size(
			render_window_rect.right - render_window_rect.left,
			render_window_rect.bottom - render_window_rect.top);
		return true;

	}
	return false;
}

//获取播放器控模块
QMedia::QIPlayerControlHandler* PlayerWindow::get_control_handler() {
	if (mpPlayerContext != nullptr)
	{
		return mpPlayerContext->get_control_handler();
	}
	return nullptr;
}

//获得播放器渲染模块
QMedia::QIPlayerRenderHandler* PlayerWindow::get_render_handler() {
	if (mpPlayerContext != nullptr) {
		return mpPlayerContext->get_render_hander();
	}
	return nullptr;
}


