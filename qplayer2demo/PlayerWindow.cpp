#include "PlayerWindow.h"
#include "resource.h"
#include <QIPlayerContext.h>

#include <QIPlayerControlHandler.h>
#include <QIPlayerRenderHandler.h>
#include <QMediaModelBuilder.h>
#include <QMediaModel.h>
#include "VideoRenderWindow.h"
#include "DemoLog.h"
#include <iostream>
#include <filesystem>


using namespace QMedia;

#define CLASS_NAME              "PlayerWindow"
#define ID_RENDER_WINDOW 200
//����
PlayerWindow::PlayerWindow(HWND parent_hwnd, HINSTANCE instance, CurrentDataModelManager* pcurrent_data_model_manager)
	:mHwnd(nullptr),
	mpPlayerContext(nullptr),
	mpCurrentDataModelManager(pcurrent_data_model_manager)
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

	char current_path[FILENAME_MAX];
	GetCurrentDirectoryA(MAX_PATH, current_path);
	mpPlayerContext->init(QLogLevel::LOG_VERBOSE, std::string(current_path), "com.qiniu.qplayer2", QPLAYER_DEMO_VERSION, "eb4136eb62d064dcacb2afedee467384", mHwnd);
	mpPlayerContext->get_render_hander()->set_window_hwnd(mpVideoRenderWindow->get_hwnd());
}

//����
PlayerWindow::~PlayerWindow()
{
	if (mpPlayerContext != nullptr)
	{
		delete mpPlayerContext;
		mpPlayerContext = nullptr;
	}
	if (mpVideoRenderWindow != nullptr)
	{
		delete mpVideoRenderWindow;
		mpVideoRenderWindow = nullptr;
	}
	mpCurrentDataModelManager = nullptr;
	DestroyWindow(mHwnd);
}

//�����¼�ѭ��
LRESULT CALLBACK  PlayerWindow::main_player_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	PlayerWindow* pplayer_window = (PlayerWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if (pplayer_window != nullptr && pplayer_window->mpCurrentDataModelManager != nullptr && pplayer_window->mpCurrentDataModelManager->get_player_state() != QMedia::QPlayerState::END) {

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
		
	default:
		break;
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

//����Ϣ���ݸ�������
LRESULT PlayerWindow::on_receive_message(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param){
	if (mpPlayerContext != nullptr) {
		mpPlayerContext->on_receive_message(hwnd, message, w_param, l_param);
		return 0;
	}
	return -1;
}

//���ش��ھ��
HWND PlayerWindow::get_hwnd() {
	return mHwnd;
}

//�޸Ĵ��ڴ�С
LRESULT PlayerWindow::on_resize()
{
	RECT root_window_rect;
	GetClientRect(mHwnd, &root_window_rect);
	EnumChildWindows(mHwnd, resize_child_windows_proc, (LPARAM)(&root_window_rect));
	notify_resize_to_player();
	return TRUE;
}

BOOL CALLBACK PlayerWindow::resize_child_windows_proc(HWND hwndChild, LPARAM lParam)
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
		MoveWindow(hwndChild, 0, 0, parent_width, parent_height, TRUE);
	}
	char str[256] = "childe_id =";
	snprintf(str, sizeof(str), "%s %d", str, child_window_id);
	
	DemoLog::log_string(CLASS_NAME, __LINE__, str);

	return TRUE;
}

bool PlayerWindow::notify_resize_to_player()
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

//��ȡ��������ģ��
QMedia::QIPlayerControlHandler* PlayerWindow::get_control_handler() {
	if (mpPlayerContext != nullptr)
	{
		return mpPlayerContext->get_control_handler();
	}
	return nullptr;
}

//��ò�������Ⱦģ��
QMedia::QIPlayerRenderHandler* PlayerWindow::get_render_handler() {
	if (mpPlayerContext != nullptr) {
		return mpPlayerContext->get_render_hander();
	}
	return nullptr;
}


QMedia::QIPlayerContext* PlayerWindow::get_context() {
	if (mpPlayerContext != nullptr) {
		return mpPlayerContext;
	}
	return nullptr;
}
