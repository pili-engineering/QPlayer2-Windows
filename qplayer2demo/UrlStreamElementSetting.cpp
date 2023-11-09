#include "UrlStreamElementSetting.h"


#define CLASS_NAME L"UrlStreamElementSetting"

#define ID_USER_TYPE_INPUT 100

#define ID_AUDIO_AND_VIDEO_OPTION 200
#define ID_AUDIO_OPTION 201
#define ID_VIDEO_OPTION 202
#define ID_NONE_OPTION 203

#define ID_URL_INPUT 300

#define ID_QUALITY_INPUT 400

#define ID_IS_SELECTED_OPTION 500
#define ID_NOT_IS_SELECTED_OPTION 501

#define ID_BACK_UP_URL_INPUT 600

#define ID_REFERER_INPUT 700

#define ID_HLS_DRM_INPUT 800

#define ID_MP4_DRM_INPUT 900

#define ID_VIDEO_TYPE_PLAN_OPTIONAL 1000
#define ID_VIDEO_TYPE_AR_OPTIONAL 1001

#define ID_SUBMIT_BUTTON 1100
#define ID_CANCEL_BUTTON 1101
UrlStreamElementSetting::UrlStreamElementSetting(HWND hwnd, HINSTANCE hinstance, UrlClickType click_type, DemoMediaStreamElementModel* stream_element_model):
	mClickType(click_type),
	mStreamElementModel(stream_element_model),
	mHinstance(GetModuleHandle(NULL)),
	mUrlInputText(),
	mUserTypeInputText(),
	mUrlType(QMedia::QUrlType::NONE),
	mQualityInputText(0),
	mRefererInputText(),
	mBackUpUrlInputText(),
	mHlsDrmInputText(),
	mMp4DrmInputText()
{
	WNDCLASSEXW wcex;
	if (GetClassInfoExW(hinstance, CLASS_NAME, &wcex) != 0) {

	}
	else
	{
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = main_stream_element_setting_window_proc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = mHinstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = NULL;

		if (!RegisterClassExW(&wcex)) {
			throw "UrlStreamElementSetting  create failed!";
		}
	}
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = 800;
	int window_height = 800;
	int window_x = (screen_width - window_width) / 2;
	int window_y = (screen_height - window_height) / 2;
	mHwnd = CreateWindowW(wcex.lpszClassName, (LPCWSTR)_T("UrlStreamElementSetting"), WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
		window_x, window_y, window_width, window_height, hwnd, NULL, mHinstance, NULL);
	if (mHwnd == nullptr)
	{
		throw "UrlSetting window create failed!";
	}
	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);

	create_child_window();

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);
}

UrlStreamElementSetting::~UrlStreamElementSetting()
{
}


LRESULT CALLBACK  UrlStreamElementSetting::main_stream_element_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	UrlStreamElementSetting* pstream_element_setting_window = (UrlStreamElementSetting*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	HINSTANCE hinst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	switch (message) {
	case WM_DESTROY: {
		if (hwnd == pstream_element_setting_window->get_hwnd()) {
			pstream_element_setting_window->mCloseCallBack(WindowCloseType::SYSTEM_CLOSE,
					pstream_element_setting_window->mUserTypeInputText,
					pstream_element_setting_window->mUrlInputText,
					pstream_element_setting_window->mQualityInputText,
					pstream_element_setting_window->mUrlType,
					pstream_element_setting_window->mIsSelected,
					pstream_element_setting_window->mBackUpUrlInputText,
					pstream_element_setting_window->mRefererInputText,
					pstream_element_setting_window->mHlsDrmInputText,
					pstream_element_setting_window->mMp4DrmInputText,
					pstream_element_setting_window->mVideoType
				);
			pstream_element_setting_window = NULL;
			DestroyWindow(hwnd);
			return 0;
		}
	}

	case WM_COMMAND: {
		int wm_id = LOWORD(w_param);
		switch (wm_id)
		{
		case ID_AUDIO_AND_VIDEO_OPTION: {
			SendMessage(pstream_element_setting_window->mAudioAndVideoOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(pstream_element_setting_window->mAudioOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mNoneOption, BM_SETCHECK, BST_UNCHECKED, 0);
			pstream_element_setting_window->mUrlType = QMedia::QUrlType::QAUDIO_AND_VIDEO;
			break;
		}
		case ID_AUDIO_OPTION: {
			SendMessage(pstream_element_setting_window->mAudioAndVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mAudioOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mNoneOption, BM_SETCHECK, BST_UNCHECKED, 0);
			pstream_element_setting_window->mUrlType = QMedia::QUrlType::QAUDIO;
			break;
		}
		case ID_VIDEO_OPTION: {
			SendMessage(pstream_element_setting_window->mAudioAndVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mAudioOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(pstream_element_setting_window->mNoneOption, BM_SETCHECK, BST_UNCHECKED, 0);
			pstream_element_setting_window->mUrlType = QMedia::QUrlType::QVIDEO;
			break;
		}
		case ID_NONE_OPTION: {
			SendMessage(pstream_element_setting_window->mAudioAndVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mAudioOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mNoneOption, BM_SETCHECK, BST_CHECKED, 0);
			pstream_element_setting_window->mUrlType = QMedia::QUrlType::NONE;
			break;
		}
		case ID_IS_SELECTED_OPTION: {
			SendMessage(pstream_element_setting_window->mIsSelectedTrueOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(pstream_element_setting_window->mIsSelectedFalseOption, BM_SETCHECK, BST_UNCHECKED, 0);
			pstream_element_setting_window->mIsSelected = true;
			break;
		}
		case ID_NOT_IS_SELECTED_OPTION: {
			SendMessage(pstream_element_setting_window->mIsSelectedTrueOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mIsSelectedFalseOption, BM_SETCHECK, BST_CHECKED, 0);
			pstream_element_setting_window->mIsSelected = false;
			break;
		}
		case ID_URL_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mUrlInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mUrlInput);
			}
			break;
		}
		case ID_USER_TYPE_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mUserTypeInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mUserTypeInput);
			}
			break;
		}
		case ID_BACK_UP_URL_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mBackUpUrlInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mBackUpUrlInput);
			}
			break;
		}
		case ID_MP4_DRM_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mMp4DrmInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mMp4DrmInput);
			}
			break;
		}
		case ID_HLS_DRM_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mHlsDrmInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mHlsDrmInput);
			}
			break;
		}
		case ID_REFERER_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				pstream_element_setting_window->mRefererInputText = pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mRefererInput);
			}
			break;
		}
		case ID_QUALITY_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				int text_length = GetWindowTextLengthW(pstream_element_setting_window->mQualityInput);
				if (text_length == 0) {
					pstream_element_setting_window->mQualityInputText = 0;
				}
				else
				{
					try
					{
						pstream_element_setting_window->mQualityInputText = std::stoi(pstream_element_setting_window->wchar_to_string(pstream_element_setting_window->mQualityInput));
					}
					catch (const std::exception&)
					{
						pstream_element_setting_window->mQualityInputText = 0;
					}
				}
				
			}
			break;
		}
		case ID_VIDEO_TYPE_PLAN_OPTIONAL: {
			SendMessage(pstream_element_setting_window->mVideoTypeAROption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoTypePlanOption, BM_SETCHECK, BST_CHECKED, 0);
			pstream_element_setting_window->mVideoType = QMedia::QVideoRenderType::PLANE;

			break;
		}
		case ID_VIDEO_TYPE_AR_OPTIONAL: {
			SendMessage(pstream_element_setting_window->mVideoTypeAROption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(pstream_element_setting_window->mVideoTypePlanOption, BM_SETCHECK, BST_UNCHECKED, 0);
			pstream_element_setting_window->mVideoType = QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR;

			break;
		}
		case ID_SUBMIT_BUTTON: {
			pstream_element_setting_window->mCloseCallBack(WindowCloseType::SUBMIT_CLOSE,
				pstream_element_setting_window->mUserTypeInputText,
				pstream_element_setting_window->mUrlInputText,
				pstream_element_setting_window->mQualityInputText,
				pstream_element_setting_window->mUrlType,
				pstream_element_setting_window->mIsSelected,
				pstream_element_setting_window->mBackUpUrlInputText,
				pstream_element_setting_window->mRefererInputText,
				pstream_element_setting_window->mHlsDrmInputText,
				pstream_element_setting_window->mMp4DrmInputText,
				pstream_element_setting_window->mVideoType
			);
			pstream_element_setting_window = NULL;
			DestroyWindow(hwnd);
			break;
		}
		case ID_CANCEL_BUTTON: {
			pstream_element_setting_window->mCloseCallBack(WindowCloseType::CANCEL_CLOSE,
				pstream_element_setting_window->mUserTypeInputText,
				pstream_element_setting_window->mUrlInputText,
				pstream_element_setting_window->mQualityInputText,
				pstream_element_setting_window->mUrlType,
				pstream_element_setting_window->mIsSelected,
				pstream_element_setting_window->mBackUpUrlInputText,
				pstream_element_setting_window->mRefererInputText,
				pstream_element_setting_window->mHlsDrmInputText,
				pstream_element_setting_window->mMp4DrmInputText,
				pstream_element_setting_window->mVideoType
			);
			pstream_element_setting_window = NULL;
			DestroyWindow(hwnd);
			break;
		}
		default:
			break;
		}
	}

				  
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}
HWND UrlStreamElementSetting::get_hwnd() {
	return mHwnd;
}

std::string UrlStreamElementSetting::wchar_to_string(HWND hwnd) {
	int text_length = GetWindowTextLengthW(hwnd);
	if (text_length == 0)
	{

		return "";
	}
	wchar_t* buffer = new wchar_t[text_length + 1];
	GetWindowTextW(hwnd, buffer, text_length + 1);

	std::wstring wstr(buffer);
	std::string input_text;
	int strLength = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (strLength > 0)
	{
		char* str_buffer = new char[strLength];
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, str_buffer, strLength, NULL, NULL);
		input_text = str_buffer;
		delete[] str_buffer;
	}

	delete[] buffer;
	return input_text;
}

void UrlStreamElementSetting::create_child_window() {

	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	CreateWindow(TEXT("STATIC"), TEXT("user_type"), WS_CHILD | WS_VISIBLE, 10, 10, 90, 20, mHwnd, NULL, NULL, NULL);
	mUserTypeInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 10, width - 130, 20, mHwnd, (HMENU)ID_USER_TYPE_INPUT, NULL, NULL);


	CreateWindow(TEXT("STATIC"), TEXT("url_type"), WS_CHILD | WS_VISIBLE, 10, 50, 90, 20, mHwnd, NULL, NULL, NULL);
	mAudioAndVideoOption = CreateWindow(TEXT("BUTTON"), TEXT("audio and video"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 100, 50, 170, 20, mHwnd, (HMENU)ID_AUDIO_AND_VIDEO_OPTION, NULL, NULL);
	mAudioOption = CreateWindow(TEXT("BUTTON"), TEXT("audio"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 280, 50, 170, 20, mHwnd, (HMENU)ID_AUDIO_OPTION, NULL, NULL);
	mVideoOption = CreateWindow(TEXT("BUTTON"), TEXT("video"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 460, 50, 170, 20, mHwnd, (HMENU)ID_VIDEO_OPTION, NULL, NULL);
	mNoneOption = CreateWindow(TEXT("BUTTON"), TEXT("none"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 640, 50, 170, 20, mHwnd, (HMENU)ID_NONE_OPTION, NULL, NULL);
	
	

	CreateWindow(TEXT("STATIC"), TEXT("url"), WS_CHILD | WS_VISIBLE, 10, 90, 90, 20, mHwnd, NULL, NULL, NULL);
	mUrlInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 90, width - 130, 20, mHwnd, (HMENU)ID_URL_INPUT, NULL, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("quality"), WS_CHILD | WS_VISIBLE, 10, 130, 90, 20, mHwnd, NULL, NULL, NULL);
	mQualityInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_AUTOHSCROLL, 110, 130, width - 130, 20, mHwnd, (HMENU)ID_QUALITY_INPUT, mHinstance, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("is_selected"), WS_CHILD | WS_VISIBLE, 10, 170, 90, 20, mHwnd, NULL, NULL, NULL);
	mIsSelectedTrueOption = CreateWindow(TEXT("BUTTON"), TEXT("ture"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 100, 170, 170, 20, mHwnd, (HMENU)ID_IS_SELECTED_OPTION, NULL, NULL);
	mIsSelectedFalseOption = CreateWindow(TEXT("BUTTON"), TEXT("false"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 280, 170, 170, 20, mHwnd, (HMENU)ID_NOT_IS_SELECTED_OPTION, NULL, NULL);


	CreateWindow(TEXT("STATIC"), TEXT("backup_url"), WS_CHILD | WS_VISIBLE, 10, 210, 90, 20, mHwnd, NULL, NULL, NULL);
	mBackUpUrlInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 210, width - 130, 20, mHwnd, (HMENU)ID_BACK_UP_URL_INPUT, mHinstance, NULL);


	CreateWindow(TEXT("STATIC"), TEXT("referer"), WS_CHILD | WS_VISIBLE, 10, 250, 90, 20, mHwnd, NULL, NULL, NULL);
	mRefererInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 250, width - 130, 20, mHwnd, (HMENU)ID_REFERER_INPUT, mHinstance, NULL);


	CreateWindow(TEXT("STATIC"), TEXT("hls_drm_key"), WS_CHILD | WS_VISIBLE, 10, 290, 90, 20, mHwnd, NULL, NULL, NULL);
	mHlsDrmInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 290, width - 130, 20, mHwnd, (HMENU)ID_HLS_DRM_INPUT, mHinstance, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("mp4_drm_key"), WS_CHILD | WS_VISIBLE, 10, 330, 90, 20, mHwnd, NULL, NULL, NULL);
	mMp4DrmInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 330, width - 130, 20, mHwnd, (HMENU)ID_MP4_DRM_INPUT, mHinstance, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("video_type"), WS_CHILD | WS_VISIBLE, 10, 360, 90, 20, mHwnd, NULL, NULL, NULL);
	mVideoTypePlanOption = CreateWindow(TEXT("BUTTON"), TEXT("普通视频"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 100, 360, 170, 20, mHwnd, (HMENU)ID_VIDEO_TYPE_PLAN_OPTIONAL, NULL, NULL);
	mVideoTypeAROption = CreateWindow(TEXT("BUTTON"), TEXT("AR视频"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 280, 360, 170, 20, mHwnd, (HMENU)ID_VIDEO_TYPE_AR_OPTIONAL, NULL, NULL);


	if (mClickType == UrlClickType::MOTIFY_URL)
	{
		SetWindowText(mUserTypeInput, _T(mStreamElementModel->get_user_type().c_str()));
		if (mStreamElementModel->get_url_type() == QMedia::QUrlType::NONE)
		{
			SendMessage(mNoneOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		else if(mStreamElementModel->get_url_type() == QMedia::QUrlType::QAUDIO_AND_VIDEO)
		{
			SendMessage(mAudioAndVideoOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		else if (mStreamElementModel->get_url_type() == QMedia::QUrlType::QVIDEO)
		{
			SendMessage(mVideoOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		else if (mStreamElementModel->get_url_type() == QMedia::QUrlType::QAUDIO)
		{
			SendMessage(mAudioOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		mUrlType = mStreamElementModel->get_url_type();
		SetWindowText(mUrlInput, _T(mStreamElementModel->get_url().c_str()));
		SetWindowText(mQualityInput, _T(std::to_string(mStreamElementModel->get_quality()).c_str()));
		if (mStreamElementModel->get_is_selected())
		{
			SendMessage(mIsSelectedTrueOption, BM_SETCHECK, BST_CHECKED, 0);
			mIsSelected = true;
		}
		else
		{
			SendMessage(mIsSelectedFalseOption, BM_SETCHECK, BST_CHECKED, 0);
			mIsSelected = false;
		}
		SetWindowText(mBackUpUrlInput, _T(mStreamElementModel->get_backup_url().c_str()));
		SetWindowText(mRefererInput, _T(mStreamElementModel->get_referer().c_str()));
		SetWindowText(mHlsDrmInput, _T(mStreamElementModel->get_hls_drm().c_str()));
		if (mStreamElementModel->get_video_type() == QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR) {
			SendMessage(mVideoTypeAROption, BM_SETCHECK, BST_CHECKED, 0);
			mVideoType = QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR;
		}
		else
		{
			SendMessage(mVideoTypePlanOption, BM_SETCHECK, BST_CHECKED, 0);
			mVideoType = QMedia::QVideoRenderType::PLANE;
		}
	}
	else
	{
		SendMessage(mAudioAndVideoOption, BM_SETCHECK, BST_CHECKED, 0);
		mUrlType = QMedia::QUrlType::QAUDIO_AND_VIDEO;
		SendMessage(mIsSelectedTrueOption, BM_SETCHECK, BST_CHECKED, 0);
		mIsSelected = true;
		SendMessage(mVideoTypePlanOption, BM_SETCHECK, BST_CHECKED, 0);
		mVideoType = QMedia::QVideoRenderType::PLANE;
	}

	CreateWindow(TEXT("BUTTON"), TEXT("确定"), WS_CHILD | WS_VISIBLE, width / 2 - 55, height - 70, 50, 20, mHwnd, (HMENU)ID_SUBMIT_BUTTON, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("取消"), WS_CHILD | WS_VISIBLE, width / 2, height - 70, 50, 20, mHwnd, (HMENU)ID_CANCEL_BUTTON, NULL, NULL);
}

void UrlStreamElementSetting::set_close_call_back(streamElementSettingWindowCloseCallBackFunction call_back) {
	mCloseCallBack = call_back;
}

