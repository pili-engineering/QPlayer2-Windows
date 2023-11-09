#pragma once
#include "framework.h"
#include <functional>
#include "QMediaModel.h"
#include "UrlClickType.h"
#include "WindowCloseType.h"
#include "DemoMediaSubtitleElementModel.h"
using SubtitleElementSettingWindowCloseCallBackFunction = std::function<void(WindowCloseType close_type, const std::string& name, const std::string& url, bool is_selected) >;

class UrlSubtitleElementSetting
{
public:
	UrlSubtitleElementSetting(HWND hwnd, HINSTANCE hinstance, UrlClickType click_type, DemoMediaSubtitleElementModel* subtitle_element_model);
	~UrlSubtitleElementSetting();

	HWND get_hwnd();

	void set_close_call_back(SubtitleElementSettingWindowCloseCallBackFunction call_back);
private:

	static LRESULT CALLBACK main_subtitle_element_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void create_child_window();

	std::string wchar_to_string(HWND hwnd);
private:
	HWND mHwnd;

	HINSTANCE mHinstance;

	SubtitleElementSettingWindowCloseCallBackFunction mCloseCallBack;


	HWND mNameInput;
	std::string mNameInputText;

	HWND mUrlInput;
	std::string mUrlInputText;


	HWND mIsSelectedTrueOption;

	HWND mIsSelectedFalseOption;
	bool mIsSelected;
	UrlClickType mClickType;
	DemoMediaSubtitleElementModel* mSubtitleElementModel;
};
