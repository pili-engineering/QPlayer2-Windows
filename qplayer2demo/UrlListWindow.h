#pragma once
#include <string>
#include <list>
#include <functional>
#include "framework.h"
#include "PlayerUrlListModelManager.h"
#include <codecvt>
#include "UrlClickType.h"
#define ID_RESUME_BUTTON        1001
#define ID_PAUSE_BUTTON         1002
#define ID_STOP_BUTTON          1003

using playCallbackFunction = std::function<void(HWND, QMedia::QMediaModel*)>;

using mouseRightClickCallbackFunction = std::function<void(int, UrlClickType)>;

class UrlListWindow
{
private:
	static LRESULT CALLBACK main_url_list_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	LRESULT on_list_create();

	LPWSTR string_to_LPWSTR(const std::string& str);

	void url_list_resize();

	void mouse_right_click_menu(HWND hwnd);

	void mouse_right_click_add();

	void mouse_right_click_motify(int item_id);

	void mouse_right_click_delete(int item_id);
public:
	UrlListWindow(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purlmanager);
	~UrlListWindow();

	HWND get_hwnd();

	void url_click(int url_id);

	void set_play_control_callback(playCallbackFunction call_back);

	void set_mouse_right_click_callback(mouseRightClickCallbackFunction call_back);

	void set_item_id(int url_id);

	int get_item_id();
private:
	HWND mHwnd;
	HINSTANCE mHinstance;
	std::list<PlayerUrlListModel *> mUrlModels;
	HWND mListWindow;
	PlayerUrlListModelManager* mpModelManager;

	playCallbackFunction mPlayControlCallback;

	mouseRightClickCallbackFunction mMouseRightClickCallBack;


	int mItemId;
};

