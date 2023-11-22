#pragma once
#include "framework.h"
#include "PlayerUrlListModelManager.h"
#include <functional>
#include "UrlClickType.h"
#include "WindowCloseType.h"
#include "DemoMediaStreamElementModel.h"
#include "DemoMediaSubtitleElementModel.h"

using urlSettingWindowCloseCallBackFunction = std::function<void()>;
class UrlSetting
{
public:
	UrlSetting(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purl_manager, UrlClickType click_type, int url_id = 0);
	~UrlSetting();


	HWND get_hwnd();

	void set_url_setting_close_call_back(urlSettingWindowCloseCallBackFunction call_back);
private:
	static LRESULT CALLBACK main_url_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void create_child_window();

	LRESULT on_streem_elements_list_update(const std ::string & name);

	LRESULT on_subtitle_elements_list_update(const std::string& name);

	void add_subtitle_elements_window_create();
	
	void motify_stream_elements_window_create(int item_id);

	void motify_subtitle_elements_window_create(int item_id);


	void delete_stream_elements_window_create(int item_id);

	void delete_subtitle_elements_window_create(int item_id);

	void add_stream_elements_window_create();

	void submit_button_click();

	void set_stream_item_id(int url_id);

	int get_stream_item_id();

	void set_subtitle_item_id(int url_id);

	int get_subtitle_item_id();
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

	int mUrlModelIndex;
	std::list<DemoMediaStreamElementModel*> mStreamElementModelList;

	std::list<DemoMediaSubtitleElementModel*> mSubtitleElementModelList;
};

