#include "UrlSubtitleElementSetting.h"

#define CLASS_NAME L"UrlSubtitleElementSetting"
#define ID_NAME_INPUT 100

#define ID_IS_SELECTED_OPTION 200
#define ID_NOT_IS_SELECTED_OPTION 201

#define ID_URL_INPUT 300

#define ID_SUBMIT_BUTTON 400
#define ID_CANCEL_BUTTON 401
UrlSubtitleElementSetting::UrlSubtitleElementSetting(HWND hwnd, HINSTANCE hinstance, UrlClickType click_type, DemoMediaSubtitleElementModel* subtitle_element_model):
	mHwnd(hwnd),
	mHinstance(hinstance),
	mIsSelected(true),
	mNameInputText(""),
	mUrlInputText(""),
	mClickType(click_type),
	mSubtitleElementModel(subtitle_element_model)
{
	WNDCLASSEXW wcex;
	if (GetClassInfoExW(hinstance, CLASS_NAME, &wcex) != 0) {

	}
	else
	{
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = main_subtitle_element_setting_window_proc;
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
			throw "UrlSubtitleElementSetting  create failed!";
		}
	}
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = 800;
	int window_height = 800;
	int window_x = (screen_width - window_width) / 2;
	int window_y = (screen_height - window_height) / 2;
	mHwnd = CreateWindowW(wcex.lpszClassName, (LPCWSTR)_T("UrlSubtitleElementSetting"), WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
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

UrlSubtitleElementSetting::~UrlSubtitleElementSetting()
{
}

HWND UrlSubtitleElementSetting::get_hwnd() {
	return mHwnd;
}

void UrlSubtitleElementSetting::set_close_call_back(SubtitleElementSettingWindowCloseCallBackFunction call_back) {
	mCloseCallBack = call_back;
}
LRESULT CALLBACK UrlSubtitleElementSetting::main_subtitle_element_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	UrlSubtitleElementSetting* psubtitle_element_setting_window = (UrlSubtitleElementSetting*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	HINSTANCE hinst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	switch (message) {
	case WM_DESTROY: {
		if (hwnd == psubtitle_element_setting_window->get_hwnd()) {
			psubtitle_element_setting_window->mCloseCallBack(WindowCloseType::SYSTEM_CLOSE,
				psubtitle_element_setting_window->mNameInputText,
				psubtitle_element_setting_window->mUrlInputText,
				psubtitle_element_setting_window->mIsSelected
			);
			psubtitle_element_setting_window = NULL;
			DestroyWindow(hwnd);
			return 0;
		}
	}
	case WM_COMMAND: {
		int wm_id = LOWORD(w_param);
		switch (wm_id)
		{
		case ID_NAME_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				psubtitle_element_setting_window->mNameInputText = psubtitle_element_setting_window->wchar_to_string(psubtitle_element_setting_window->mNameInput);
			}
			break;
		}
		case ID_URL_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				psubtitle_element_setting_window->mUrlInputText = psubtitle_element_setting_window->wchar_to_string(psubtitle_element_setting_window->mUrlInput);
			}
			break;
		}
		case ID_IS_SELECTED_OPTION: {
			SendMessage(psubtitle_element_setting_window->mIsSelectedTrueOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(psubtitle_element_setting_window->mIsSelectedFalseOption, BM_SETCHECK, BST_UNCHECKED, 0);
			psubtitle_element_setting_window->mIsSelected = true;
			break;
		}
		case ID_NOT_IS_SELECTED_OPTION: {
			SendMessage(psubtitle_element_setting_window->mIsSelectedTrueOption, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(psubtitle_element_setting_window->mIsSelectedFalseOption, BM_SETCHECK, BST_CHECKED, 0);
			psubtitle_element_setting_window->mIsSelected = false;
			break;
		}

		case ID_SUBMIT_BUTTON: {
			psubtitle_element_setting_window->mCloseCallBack(WindowCloseType::SUBMIT_CLOSE,
				psubtitle_element_setting_window->mNameInputText,
				psubtitle_element_setting_window->mUrlInputText,
				psubtitle_element_setting_window->mIsSelected
			);
			psubtitle_element_setting_window = NULL;
			DestroyWindow(hwnd);
			break;
		}
		case ID_CANCEL_BUTTON: {
			psubtitle_element_setting_window->mCloseCallBack(WindowCloseType::CANCEL_CLOSE,
				psubtitle_element_setting_window->mNameInputText,
				psubtitle_element_setting_window->mUrlInputText,
				psubtitle_element_setting_window->mIsSelected
			);
			psubtitle_element_setting_window = NULL;
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

void UrlSubtitleElementSetting::create_child_window() {

	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	CreateWindow(TEXT("STATIC"), TEXT("name"), WS_CHILD | WS_VISIBLE, 10, 10, 90, 20, mHwnd, NULL, NULL, NULL);
	mNameInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 10, width - 130, 20, mHwnd, (HMENU)ID_NAME_INPUT, NULL, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("url"), WS_CHILD | WS_VISIBLE, 10, 40, 90, 20, mHwnd, NULL, NULL, NULL);
	mUrlInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 40, width - 130, 20, mHwnd, (HMENU)ID_URL_INPUT, NULL, NULL);

	CreateWindow(TEXT("STATIC"), TEXT("is_selected"), WS_CHILD | WS_VISIBLE, 10, 70, 90, 20, mHwnd, NULL, NULL, NULL);
	mIsSelectedTrueOption = CreateWindow(TEXT("BUTTON"), TEXT("ture"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 100, 70, 170, 20, mHwnd, (HMENU)ID_IS_SELECTED_OPTION, NULL, NULL);
	mIsSelectedFalseOption = CreateWindow(TEXT("BUTTON"), TEXT("false"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 280, 70, 170, 20, mHwnd, (HMENU)ID_NOT_IS_SELECTED_OPTION, NULL, NULL);
	SendMessage(mIsSelectedTrueOption, BM_SETCHECK, BST_CHECKED, 0);
	mIsSelected = true;

	CreateWindow(TEXT("BUTTON"), TEXT("确定"), WS_CHILD | WS_VISIBLE, width / 2 - 55, height - 70, 50, 20, mHwnd, (HMENU)ID_SUBMIT_BUTTON, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("取消"), WS_CHILD | WS_VISIBLE, width / 2, height - 70, 50, 20, mHwnd, (HMENU)ID_CANCEL_BUTTON, NULL, NULL);
}
std::string UrlSubtitleElementSetting::wchar_to_string(HWND hwnd) {
	int text_length = GetWindowTextLengthW(hwnd);
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
