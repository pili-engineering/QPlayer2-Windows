#pragma once
#include "framework.h"
#include <functional>
#include <QMediaModel.h>
#include "UrlClickType.h"
#include "WindowCloseType.h"
#include "DemoMediaStreamElementModel.h"
using StreamElementSettingWindowCloseCallBackFunction = std::function<void(WindowCloseType close_type,UrlClickType click_type, DemoMediaStreamElementModel* pstream_element_model)>;
class UrlStreamElementSetting
{
public:
	~UrlStreamElementSetting();
	UrlStreamElementSetting(HWND hwnd, HINSTANCE hinstance,UrlClickType click_type, DemoMediaStreamElementModel * pstream_element_model);


	HWND get_hwnd();

	void set_close_call_back(StreamElementSettingWindowCloseCallBackFunction call_back);
private:

	static LRESULT CALLBACK main_stream_element_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void create_child_window();

	std::string wchar_to_string(HWND hwnd);

private:
	HWND mHwnd;
	UrlClickType mClickType;
	DemoMediaStreamElementModel* mpStreamElementModel;
	HINSTANCE mHinstance;


	HWND mUserTypeInput;

	HWND mUrlInput;

	HWND mQualityInput;

	HWND mBackUpUrlInput;

	HWND mRefererInput;

	HWND mHlsDrmInput;

	HWND mMp4DrmInput;

	HWND mAudioAndVideoOption;
	HWND mAudioOption;
	HWND mVideoOption;
	HWND mNoneOption;

	HWND mIsSelectedTrueOption;

	HWND mIsSelectedFalseOption;

	HWND mVideoTypePlanOption;
	HWND mVideoTypeAROption;
	StreamElementSettingWindowCloseCallBackFunction mCloseCallBack;
};

