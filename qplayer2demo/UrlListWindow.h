#pragma once
#include <string>
#include <list>
#include <functional>
#include "framework.h"
#include "PlayerUrlListModelManager.h"
#include <codecvt>

#define ID_RESUME_BUTTON        1001
#define ID_PAUSE_BUTTON         1002
#define ID_STOP_BUTTON          1003

using playCallbackFunction = std::function<void(HWND, QMedia::QMediaModel*)>;

class UrlListWindow
{
private:
	static LRESULT CALLBACK main_url_list_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	LRESULT on_list_create();

	LPWSTR string_to_LPWSTR(const std::string& str);

	void url_list_resize();
public:
	UrlListWindow(HWND hwnd, HINSTANCE hinstance);
	~UrlListWindow();

	HWND get_hwnd();

	void url_click(int url_id);

	void set_play_control_callback(playCallbackFunction callBack);
private:
	HWND mHwnd;
	HINSTANCE mHinstance;
	std::list<PlayerUrlListModel *> mUrlModels;
	HWND mListWindow;
	PlayerUrlListModelManager* mpModelManager;

	playCallbackFunction mPlayControlCallback;
};

