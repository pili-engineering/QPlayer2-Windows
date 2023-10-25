#include "UrlSetting.h"
#include "QMediaModelBuilder.h"
#include <CommCtrl.h>
#include "UrlStreamElementSetting.h"
#include "UrlSubtitleElementSetting.h"
//const wchar_t* mpClassName = L"UrlSetting";
#define CLASS_NAME L"UrlSetting"
#define TAG  "UrlSetting"

#define ID_IS_LIVE_TRUE_OPTION 100
#define ID_IS_LIVE_FALSE_OPTION 101

#define ID_SUBMIT_BUTTON 200
#define ID_CANCEL_BUTTON 201

#define ID_URL_NAME_INPUT 300

#define ID_URL_ADD_STREAM_BUTTON 400
#define ID_URL_ADD_SUBTITLE_BUTTON 401

#define ID_URL_ADD_STREAM_WINDOW 500
#define ID_URL_ADD_SUBTITLE_WINDOW 501

UrlSetting::UrlSetting(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purl_manager, UrlClickType click_type):
	mpPlayerUrlModelManager(purl_manager),
	mIsLive(FALSE),
	mUrlNameInputText(""),
	mUrlClickType(click_type),
	mStreamElementIndex(0),
	mSubtitleElementIndex(0)
{

	mHinstance = GetModuleHandle(NULL);
	WNDCLASSEXW wcex;
	if (GetClassInfoExW(hinstance, CLASS_NAME, &wcex) != 0) {

	}
	else
	{
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = main_url_setting_window_proc;
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
			throw "UrlSetting  create failed!";
		}
	}
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = 800;
	int window_height = 800;
	int window_x = (screen_width - window_width) / 2;
	int window_y = (screen_height - window_height) / 2;
	mHwnd = CreateWindowW(wcex.lpszClassName, CLASS_NAME, WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
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

UrlSetting::~UrlSetting() {
}

HWND UrlSetting::get_hwnd() {
	return mHwnd;
}

LRESULT CALLBACK UrlSetting::main_url_setting_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	UrlSetting* purl_setting_window = (UrlSetting*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	HINSTANCE hinst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	switch (message) {
	case WM_DESTROY: {
		if (hwnd == purl_setting_window->get_hwnd()) {
			purl_setting_window->mCloseCallBack();
			purl_setting_window = NULL;
			DestroyWindow(hwnd);
			return 0;
		}

	}
	case WM_COMMAND: {
		int wm_id = LOWORD(w_param);
		switch (wm_id)
		{
		case ID_IS_LIVE_TRUE_OPTION: {
			purl_setting_window->mIsLive = TRUE;
			break;
		}
		case ID_IS_LIVE_FALSE_OPTION: {
			purl_setting_window->mIsLive = FALSE;
			break;
		}
		case ID_SUBMIT_BUTTON: {
			purl_setting_window->submit_button_click();
			break;
		}
		case ID_CANCEL_BUTTON: {
			if (hwnd == purl_setting_window->get_hwnd()) {
				purl_setting_window->mCloseCallBack();
				purl_setting_window = NULL;
				DestroyWindow(hwnd);
				return 0;
			}
			break;
		}
		case ID_URL_ADD_STREAM_BUTTON: {
			purl_setting_window->add_stream_elements_window_create();
			break;
		}
		case ID_URL_ADD_SUBTITLE_BUTTON: {
			purl_setting_window->add_subtitle_elements_window_create();
			break;
		}
		case ID_URL_NAME_INPUT: {
			if (HIWORD(w_param) == EN_CHANGE) {
				int text_length = GetWindowTextLengthW(purl_setting_window->mUrlNameInput);
				wchar_t* buffer = new wchar_t[text_length + 1];
				GetWindowTextW(purl_setting_window->mUrlNameInput, buffer, text_length + 1);

				std::wstring wstr(buffer);
				std::string str;
				int strLength = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
				if (strLength > 0)
				{
					char* str_buffer = new char[strLength];
					WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, str_buffer, strLength, NULL, NULL);
					purl_setting_window->mUrlNameInputText = str_buffer;
					delete[] str_buffer;
				}

				delete[] buffer;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	}
	
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

void UrlSetting::set_url_setting_close_call_back(urlSettingWindowCloseCallBackFunction call_back) {
	mCloseCallBack = call_back;
}

void UrlSetting::create_child_window() {


	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);
	
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	HWND child_window;
	CreateWindow(TEXT("STATIC"), TEXT("是否直播"), WS_CHILD | WS_VISIBLE, 10, 10, 60, 20, mHwnd, NULL, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("是"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 80, 10, 50, 20, mHwnd, (HMENU)ID_IS_LIVE_TRUE_OPTION, NULL, NULL);
	child_window = CreateWindow(TEXT("BUTTON"), TEXT("否"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 140, 10, 50, 20, mHwnd, (HMENU)ID_IS_LIVE_FALSE_OPTION, NULL, NULL);
	if (mUrlClickType == UrlClickType::ADD_URL)
	{
		SendMessage(child_window, BM_SETCHECK, BST_CHECKED, 0);
	}
	CreateWindow(TEXT("STATIC"), TEXT("地址名称"), WS_CHILD | WS_VISIBLE, 10, 40, 60, 20, mHwnd, NULL, NULL, NULL);
	mUrlNameInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 80, 40, width - 100, 20, mHwnd, (HMENU)ID_URL_NAME_INPUT, NULL, NULL);


	CreateWindow(TEXT("STATIC"), TEXT("地址"), WS_CHILD | WS_VISIBLE, 10, 70, 60, 20, mHwnd, NULL, NULL, NULL);


	CreateWindow(TEXT("BUTTON"), TEXT("添加"), WS_CHILD | WS_VISIBLE, 80, 70, 60, 20, mHwnd, (HMENU)ID_URL_ADD_STREAM_BUTTON, NULL, NULL);

	mUrlStreamElementsListWindow = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 80, 100, width - 100, (height - 200) / 2 - 10, mHwnd, NULL, NULL, NULL);

	ListView_SetExtendedListViewStyle(mUrlStreamElementsListWindow, LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);

	// 添加列头
	LVCOLUMNW  stream_column;
	stream_column.mask = LVCF_WIDTH | LVCF_TEXT;
	stream_column.pszText = (LPWSTR)_T("url");
	stream_column.cx = windowRect.right - windowRect.left;
	if (ListView_InsertColumn(mUrlStreamElementsListWindow, 0, &stream_column) == -1) {
		throw "ListView_InsertColumn error";
	}
	if (mUrlClickType == UrlClickType::MOTIFY_URL)
	{
		on_streem_elements_list_update("");
	}

	CreateWindow(TEXT("STATIC"), TEXT("字幕地址"), WS_CHILD | WS_VISIBLE, 10, height / 2 + 5, 60, 20, mHwnd, NULL, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("添加"), WS_CHILD | WS_VISIBLE, 80, height / 2 + 5, 60, 20, mHwnd, (HMENU)ID_URL_ADD_SUBTITLE_BUTTON, NULL, NULL);
	mUrlSubtitleElementsListWindow = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 80, height / 2 + 40, width - 100, (height - 200) / 2 - 10, mHwnd, NULL, NULL, NULL);

	ListView_SetExtendedListViewStyle(mUrlSubtitleElementsListWindow, LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);

	// 添加列头
	LVCOLUMNW  subtitle_column;
	subtitle_column.mask = LVCF_WIDTH | LVCF_TEXT;
	subtitle_column.pszText = (LPWSTR)_T("url");
	subtitle_column.cx = windowRect.right - windowRect.left;
	if (ListView_InsertColumn(mUrlSubtitleElementsListWindow, 0, &subtitle_column) == -1) {
		throw "ListView_InsertColumn error";
	}
	if (mUrlClickType == UrlClickType::MOTIFY_URL)
	{
		on_subtitle_elements_list_update("");
	}


	CreateWindow(TEXT("BUTTON"), TEXT("确定"), WS_CHILD | WS_VISIBLE, width / 2 - 55, height - 70, 50, 20, mHwnd, (HMENU)ID_SUBMIT_BUTTON, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("取消"), WS_CHILD | WS_VISIBLE, width / 2, height - 70, 50, 20, mHwnd, (HMENU)ID_CANCEL_BUTTON, NULL, NULL);
}


void UrlSetting::submit_button_click() {
	switch (mUrlClickType)
	{
	case ADD_URL: {
		mpPlayerUrlModelManager->build(mIsLive, mUrlNameInputText);

		break;
	}
	case MOTIFY_URL:
		break;
	case DELETE_URL:
		break;
	default:
		break;
	}
	mpPlayerUrlModelManager->url_update();
	mCloseCallBack();
	DestroyWindow(mHwnd);

}

LRESULT UrlSetting::on_streem_elements_list_update(const std::string& name) {

	// 添加行数据
	LVITEMW  lv_item;
	lv_item.mask = LVIF_TEXT;
	lv_item.iSubItem = 0;
	lv_item.pszText = (LPWSTR)_T(name.c_str());
	lv_item.iItem = mStreamElementIndex;
	ListView_InsertItem(mUrlStreamElementsListWindow, &lv_item);
	return 0;
}
LRESULT UrlSetting::on_subtitle_elements_list_update(const std::string& name) {
	// 添加行数据
	LVITEMW  lv_item;
	lv_item.mask = LVIF_TEXT;
	lv_item.iSubItem = 0;
	lv_item.pszText = (LPWSTR)_T(name.c_str());
	lv_item.iItem = mSubtitleElementIndex;
	ListView_InsertItem(mUrlSubtitleElementsListWindow, &lv_item);
	return 0;
}
void UrlSetting::add_subtitle_elements_window_create() {
	UrlSubtitleElementSetting* purl_subtitle_element_window = new UrlSubtitleElementSetting(mHwnd, mHinstance);
	EnableWindow(mHwnd, FALSE);
	purl_subtitle_element_window->set_close_call_back(
		[this](WindowCloseType close_type, const std::string& name, const std::string& url, bool is_selected) {
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				mSubtitleElementIndex++;
				mpPlayerUrlModelManager->add_subtitle_element(name,url,is_selected);
				on_subtitle_elements_list_update(url);
			}
		}
	);
	SetWindowLong(purl_subtitle_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_SUBTITLE_WINDOW);
}

void UrlSetting::add_stream_elements_window_create() {
	UrlStreamElementSetting* purl_stream_element_window = new UrlStreamElementSetting(mHwnd, mHinstance);
	EnableWindow(mHwnd, FALSE);
	purl_stream_element_window->set_close_call_back(
		[this](WindowCloseType close_type, const std::string& user_type, const std::string& url, int quality, QMedia::QUrlType type, bool is_selected, const std::string& backup_url, const std::string& referer, const std::string& hls_drm, const std::string& mp4_drm,QMedia::QVideoRenderType video_type) {
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				mStreamElementIndex++;
				mpPlayerUrlModelManager->add_stream_element(user_type, type, quality, url.c_str(), is_selected, backup_url, referer, video_type, hls_drm, mp4_drm);
				on_streem_elements_list_update(url);
			}
		}
	);
	SetWindowLong(purl_stream_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_STREAM_WINDOW);
}

