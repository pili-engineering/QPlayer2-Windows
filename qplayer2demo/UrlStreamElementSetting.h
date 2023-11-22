#pragma once
#include "framework.h"
#include <functional>
#include "QMediaModel.h"
#include "UrlClickType.h"
#include "WindowCloseType.h"
#include "DemoMediaStreamElementModel.h"
//using streamElementSettingWindowCloseCallBackFunction = std::function<void(WindowCloseType close_type, const std::string& user_type, const std::string & url, int quality, QMedia::QUrlType type, bool is_selected, const std::string& backup_url, const std::string & referer, const std::string & hls_drm ,const std::string & mp4_drm, QMedia::QVideoRenderType video_type) > ;
using streamElementSettingWindowCloseCallBackFunction = std::function<void(WindowCloseType close_type,UrlClickType click_type, DemoMediaStreamElementModel* stream_element_model)>;
class UrlStreamElementSetting
{
public:
	~UrlStreamElementSetting();
	UrlStreamElementSetting(HWND hwnd, HINSTANCE hinstance,UrlClickType click_type, DemoMediaStreamElementModel * stream_element_model);


	HWND get_hwnd();

	void set_close_call_back(streamElementSettingWindowCloseCallBackFunction call_back);
private:

	static LRESULT CALLBACK main_stream_element_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void create_child_window();

	std::string wchar_to_string(HWND hwnd);

private:
	HWND mHwnd;
	UrlClickType mClickType;
	DemoMediaStreamElementModel* mStreamElementModel;
	HINSTANCE mHinstance;


	HWND mUserTypeInput;
	//std::string mUserTypeInputText;

	HWND mUrlInput;
	//std::string mUrlInputText;

	HWND mQualityInput;
	//int mQualityInputText;

	HWND mBackUpUrlInput;
	//std::string mBackUpUrlInputText;

	HWND mRefererInput;
	//std::string mRefererInputText;

	HWND mHlsDrmInput;
	//std::string mHlsDrmInputText;

	HWND mMp4DrmInput;
	//std::string mMp4DrmInputText;

	HWND mAudioAndVideoOption;
	HWND mAudioOption;
	HWND mVideoOption;
	HWND mNoneOption;
	//QMedia::QUrlType mUrlType;

	HWND mIsSelectedTrueOption;

	HWND mIsSelectedFalseOption;
	//bool mIsSelected;

	HWND mVideoTypePlanOption;
	HWND mVideoTypeAROption;
	//QMedia::QVideoRenderType mVideoType;
	streamElementSettingWindowCloseCallBackFunction mCloseCallBack;
};

