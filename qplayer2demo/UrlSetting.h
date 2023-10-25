#pragma once
#include "framework.h"
#include "PlayerUrlListModelManager.h"
#include <functional>
#include "UrlClickType.h"
#include "WindowCloseType.h"
using urlSettingWindowCloseCallBackFunction = std::function<void()>;
class UrlSetting
{
public:
	UrlSetting(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purl_manager, UrlClickType click_type);
	~UrlSetting();


	HWND get_hwnd();

	void set_url_setting_close_call_back(urlSettingWindowCloseCallBackFunction call_back);
private:
	static LRESULT CALLBACK main_url_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void create_child_window();

	LRESULT on_streem_elements_list_update(const std ::string & name);

	LRESULT on_subtitle_elements_list_update(const std::string& name);

	void add_subtitle_elements_window_create();

	void add_stream_elements_window_create();

	void submit_button_click();
private:
	HWND mHwnd;
	HINSTANCE mHinstance;

	PlayerUrlListModelManager* mpPlayerUrlModelManager;

	urlSettingWindowCloseCallBackFunction mCloseCallBack;

	bool mIsLive;

	HWND mUrlNameInput;


	HWND mUrlStreamElementsListWindow;
	

	HWND mUrlSubtitleElementsListWindow;

	std::string mUrlNameInputText;

	UrlClickType mUrlClickType;

	int mStreamElementIndex;

	int mSubtitleElementIndex;
};

