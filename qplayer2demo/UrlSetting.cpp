#include "UrlSetting.h"
#include <QMediaModelBuilder.h>
#include <CommCtrl.h>
#include "UrlStreamElementSetting.h"
#include "UrlSubtitleElementSetting.h"

#define CLASS_NAME L"UrlSetting"

#define ID_IS_LIVE_TRUE_OPTION 100
#define ID_IS_LIVE_FALSE_OPTION 101

#define ID_SUBMIT_BUTTON 200
#define ID_CANCEL_BUTTON 201

#define ID_URL_NAME_INPUT 300

#define ID_URL_ADD_STREAM_BUTTON 400
#define ID_URL_ADD_SUBTITLE_BUTTON 401

#define ID_URL_ADD_STREAM_WINDOW 500
#define ID_URL_ADD_SUBTITLE_WINDOW 501

#define ID_RECONSTRUCT_TIME_LINE_TRUE_OPTION 600
#define ID_RECONSTRUCT_TIME_LINE_FALSE_OPTION 601

#define RIGHT_STREAM_MENU_ADD          1000
#define RIGHT_STREAM_MENU_MODIFY       1001
#define RIGHT_STREAM_MENU_DELETE       1002

#define RIGHT_SUBTITLE_MENU_ADD          2000
#define RIGHT_SUBTITLE_MENU_MODIFY       2001
#define RIGHT_SUBTITLE_MENU_DELETE       2002
UrlSetting::UrlSetting(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purl_manager, UrlClickType click_type ,int url_id) :
	mpPlayerUrlModelManager(purl_manager),
	mIsLive(FALSE),
	mUrlNameInputText(""),
	mUrlClickType(click_type),
	mStreamElementIndex(0),
	mSubtitleElementIndex(0),
	mStreamElementModelList(),
	mSubtitleElementModelList(),
	mUrlModelIndex(url_id),
	mReconstructTimeLine(false)
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
	mHwnd = CreateWindowW(wcex.lpszClassName, (LPCWSTR)_T("UrlSetting"), WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_MINIMIZEBOX,
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
	case WM_NOTIFY:
	{
		NMHDR* pnmhdr = (NMHDR*)l_param;
		if (pnmhdr->hwndFrom == purl_setting_window->mUrlStreamElementsListWindow)
		{
			LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
			int selected_index = pnmia->iItem;
			if ((int)(pnmhdr->code) == (int)NM_RCLICK)
			{
				LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
				int selected_index = pnmia->iItem;
				purl_setting_window->set_stream_item_id(selected_index);
				HMENU right_menu = CreatePopupMenu();
				AppendMenu(right_menu, MF_STRING, RIGHT_STREAM_MENU_ADD, "添加");
				AppendMenu(right_menu, MF_STRING, RIGHT_STREAM_MENU_MODIFY, "修改");
				AppendMenu(right_menu, MF_STRING, RIGHT_STREAM_MENU_DELETE, "删除");
				POINT pt;
				GetCursorPos(&pt);
				//SetMenu(mUrlStreamElementsListWindow, right_menu);
				SetForegroundWindow(purl_setting_window->get_hwnd());
				TrackPopupMenu(right_menu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, purl_setting_window->get_hwnd(), NULL);
				DestroyMenu(right_menu);
			}
		}
		else if(pnmhdr->hwndFrom == purl_setting_window->mUrlSubtitleElementsListWindow)
		{
			LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
			int selected_index = pnmia->iItem;
			if ((int)(pnmhdr->code) == (int)NM_RCLICK)
			{
				LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
				int selected_index = pnmia->iItem;
				purl_setting_window->set_subtitle_item_id(selected_index);
				HMENU right_menu = CreatePopupMenu();
				AppendMenu(right_menu, MF_STRING, RIGHT_SUBTITLE_MENU_ADD, "添加");
				AppendMenu(right_menu, MF_STRING, RIGHT_SUBTITLE_MENU_MODIFY, "修改");
				AppendMenu(right_menu, MF_STRING, RIGHT_SUBTITLE_MENU_DELETE, "删除");
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(purl_setting_window->get_hwnd());
				TrackPopupMenu(right_menu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, purl_setting_window->get_hwnd(), NULL);
				DestroyMenu(right_menu);
			}
		}
		break;
	}
	case WM_COMMAND: {
		int wm_id = LOWORD(w_param);
		switch (wm_id)
		{
		case ID_IS_LIVE_TRUE_OPTION: {
			SendMessage(purl_setting_window->mIsLiveTrueOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(purl_setting_window->mIsLiveFalseOption, BM_SETCHECK, BST_UNCHECKED, 0);
			purl_setting_window->mIsLive = TRUE;
			break;
		}
		case ID_IS_LIVE_FALSE_OPTION: {
			SendMessage(purl_setting_window->mIsLiveFalseOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(purl_setting_window->mIsLiveTrueOption, BM_SETCHECK, BST_UNCHECKED, 0);
			purl_setting_window->mIsLive = FALSE;
			break;
		}
		case ID_RECONSTRUCT_TIME_LINE_TRUE_OPTION: {
			SendMessage(purl_setting_window->mReconstructTimeLineTrueOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(purl_setting_window->mReconstructTimeLineFalseOption, BM_SETCHECK, BST_UNCHECKED, 0);
			purl_setting_window->mReconstructTimeLine = TRUE;
			break;
		}
		case ID_RECONSTRUCT_TIME_LINE_FALSE_OPTION: {
			SendMessage(purl_setting_window->mReconstructTimeLineFalseOption, BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(purl_setting_window->mReconstructTimeLineTrueOption, BM_SETCHECK, BST_UNCHECKED, 0);
			purl_setting_window->mReconstructTimeLine = FALSE;
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
				wchar_t* pbuffer = new wchar_t[text_length + 1];
				GetWindowTextW(purl_setting_window->mUrlNameInput, pbuffer, text_length + 1);

				std::wstring wstr(pbuffer);
				std::string str;
				int strLength = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
				if (strLength > 0)
				{
					char* str_buffer = new char[strLength];
					WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, str_buffer, strLength, NULL, NULL);
					purl_setting_window->mUrlNameInputText = str_buffer;
					delete[] str_buffer;
				}

				delete[] pbuffer;
			}
			break;
		}
		case RIGHT_STREAM_MENU_ADD: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->add_stream_elements_window_create();
			}
			break;
		}
		case RIGHT_STREAM_MENU_MODIFY: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->motify_stream_elements_window_create(purl_setting_window->mStreamElementIndex);
			}
			break;
		}
		case RIGHT_STREAM_MENU_DELETE: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->delete_stream_elements_window_create(purl_setting_window->mStreamElementIndex);
			}
			break;
		}
		case RIGHT_SUBTITLE_MENU_ADD: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->add_subtitle_elements_window_create();
			}
			break;
		}
		case RIGHT_SUBTITLE_MENU_MODIFY: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->motify_subtitle_elements_window_create(purl_setting_window->mSubtitleElementIndex);
			}
			break;
		}
		case RIGHT_SUBTITLE_MENU_DELETE: {
			if (purl_setting_window != nullptr) {
				purl_setting_window->delete_subtitle_elements_window_create(purl_setting_window->mSubtitleElementIndex);
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

void UrlSetting::set_url_setting_close_call_back(UrlSettingWindowCloseCallBackFunction call_back) {
	mCloseCallBack = call_back;
}

void UrlSetting::create_child_window() {
	if (mUrlClickType == UrlClickType::MOTIFY_URL || mUrlClickType == UrlClickType::DELETE_URL)
	{
		for (auto it : mpPlayerUrlModelManager->get_url_model_for_index(mUrlModelIndex)->get_media_model()->get_stream_elements()) {
			DemoMediaStreamElementModel* pinner_ele_model = new DemoMediaStreamElementModel;
			pinner_ele_model->set_backup_url(it->get_back_url());
			pinner_ele_model->set_hls_drm(it->get_hls_drm_key());
			pinner_ele_model->set_is_selected(it->is_selected());
			pinner_ele_model->set_mp4_drm(it->get_mp4_drm_key());
			pinner_ele_model->set_quality(it->get_quality_index());
			pinner_ele_model->set_referer(it->get_referer());
			pinner_ele_model->set_url(it->get_url());
			pinner_ele_model->set_url_type(it->get_url_type());
			pinner_ele_model->set_user_type(it->get_user_type());
			mStreamElementModelList.emplace_back(pinner_ele_model);
		}
		for (auto it : mpPlayerUrlModelManager->get_url_model_for_index(mUrlModelIndex)->get_media_model()->get_subtitle_elements()) {
			DemoMediaSubtitleElementModel* pinner_ele_model = new DemoMediaSubtitleElementModel;
			pinner_ele_model->set_name(it->get_name());
			pinner_ele_model->set_is_selected(it->is_selected());
			pinner_ele_model->set_url(it->get_url());
			mSubtitleElementModelList.emplace_back(pinner_ele_model);
		}
	}
	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	HWND child_window;
	CreateWindow(TEXT("STATIC"), TEXT("是否直播"), WS_CHILD | WS_VISIBLE, 10, 10, 60, 20, mHwnd, NULL, NULL, NULL);
	mIsLiveTrueOption = CreateWindow(TEXT("BUTTON"), TEXT("是"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 80, 10, 50, 20, mHwnd, (HMENU)ID_IS_LIVE_TRUE_OPTION, NULL, NULL);
	mIsLiveFalseOption = CreateWindow(TEXT("BUTTON"), TEXT("否"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 140, 10, 50, 20, mHwnd, (HMENU)ID_IS_LIVE_FALSE_OPTION, NULL, NULL);
	if (mUrlClickType == UrlClickType::ADD_URL)
	{
		SendMessage(mIsLiveFalseOption, BM_SETCHECK, BST_CHECKED, 0);
	}
	CreateWindow(TEXT("STATIC"), TEXT("是否重置时间轴"), WS_CHILD | WS_VISIBLE, 10, 40, 120, 20, mHwnd, NULL, NULL, NULL);
	mReconstructTimeLineTrueOption = CreateWindow(TEXT("BUTTON"), TEXT("是"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 140, 40, 50, 20, mHwnd, (HMENU)ID_RECONSTRUCT_TIME_LINE_TRUE_OPTION, NULL, NULL);
	mReconstructTimeLineFalseOption = CreateWindow(TEXT("BUTTON"), TEXT("否"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 200, 40, 50, 20, mHwnd, (HMENU)ID_RECONSTRUCT_TIME_LINE_FALSE_OPTION, NULL, NULL);
	if (mUrlClickType == UrlClickType::ADD_URL)
	{
		SendMessage(mReconstructTimeLineFalseOption, BM_SETCHECK, BST_CHECKED, 0);
	}

	CreateWindow(TEXT("STATIC"), TEXT("地址名称"), WS_CHILD | WS_VISIBLE, 10, 70, 60, 20, mHwnd, NULL, NULL, NULL);
	mUrlNameInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 80, 70, width - 100, 20, mHwnd, (HMENU)ID_URL_NAME_INPUT, NULL, NULL);
	CreateWindow(TEXT("STATIC"), TEXT("地址"), WS_CHILD | WS_VISIBLE, 10, 100, 60, 20, mHwnd, NULL, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("添加"), WS_CHILD | WS_VISIBLE, 80, 100, 60, 20, mHwnd, (HMENU)ID_URL_ADD_STREAM_BUTTON, NULL, NULL);
	mUrlStreamElementsListWindow = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 80, 130, width - 100, (height - 200) / 2 - 40, mHwnd, NULL, NULL, NULL);
	ListView_SetExtendedListViewStyle(mUrlStreamElementsListWindow, LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);

	// 添加列头
	LVCOLUMNW  stream_column;
	stream_column.mask = LVCF_WIDTH | LVCF_TEXT;
	stream_column.pszText = (LPWSTR)_T("url");
	stream_column.cx = windowRect.right - windowRect.left;
	if (ListView_InsertColumn(mUrlStreamElementsListWindow, 0, &stream_column) == -1) {
		throw "ListView_InsertColumn error";
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
		if (mpPlayerUrlModelManager->get_url_model_for_index(mUrlModelIndex)->get_media_model()->is_live())
		{
			SendMessage(mIsLiveTrueOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendMessage(mIsLiveFalseOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		if (mpPlayerUrlModelManager->get_url_model_for_index(mUrlModelIndex)->get_media_model()->is_reconstruct_time_line())
		{
			SendMessage(mReconstructTimeLineTrueOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendMessage(mReconstructTimeLineFalseOption, BM_SETCHECK, BST_CHECKED, 0);
		}
		for (DemoMediaStreamElementModel* pinner_model : mStreamElementModelList)
		{
			on_streem_elements_list_update(pinner_model->get_url());
			mStreamElementIndex++;
		}
		for (DemoMediaSubtitleElementModel* pinner_model : mSubtitleElementModelList)
		{
			on_subtitle_elements_list_update(pinner_model->get_url());
			mSubtitleElementIndex++;
		}
		SetWindowText(mUrlNameInput, _T(mpPlayerUrlModelManager->get_url_model_for_index(mUrlModelIndex)->get_name().c_str()));
	}

	CreateWindow(TEXT("BUTTON"), TEXT("确定"), WS_CHILD | WS_VISIBLE, width / 2 - 55, height - 70, 50, 20, mHwnd, (HMENU)ID_SUBMIT_BUTTON, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("取消"), WS_CHILD | WS_VISIBLE, width / 2, height - 70, 50, 20, mHwnd, (HMENU)ID_CANCEL_BUTTON, NULL, NULL);
}


void UrlSetting::submit_button_click() {
	for (auto it : mStreamElementModelList)
	{
		mpPlayerUrlModelManager->add_stream_element(it->get_user_type(),
			it->get_url_type(),
			it->get_quality(),
			it->get_url(),
			it->get_is_selected(),
			it->get_referer(),
			it->get_backup_url(),
			it->get_video_type(),
			it->get_hls_drm(),
			it->get_mp4_drm()
		);
	}
	for (auto it : mSubtitleElementModelList) {
		mpPlayerUrlModelManager->add_subtitle_element(
			it->get_name(),
			it->get_url(),
			it->get_is_selected()
		);
	}
	switch (mUrlClickType)
	{
	case ADD_URL: {
		
		mpPlayerUrlModelManager->build(mIsLive, mReconstructTimeLine, mUrlNameInputText);
		break;
	}
	case MOTIFY_URL:
		mpPlayerUrlModelManager->build(mIsLive, mReconstructTimeLine, mUrlNameInputText,mUrlModelIndex);
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
	UrlSubtitleElementSetting* purl_subtitle_element_window = new UrlSubtitleElementSetting(mHwnd, mHinstance,UrlClickType::ADD_URL,nullptr);
	EnableWindow(mHwnd, FALSE);
	purl_subtitle_element_window->set_close_call_back(
		[this](WindowCloseType close_type, UrlClickType click_type, DemoMediaSubtitleElementModel* pmodel) {
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				mSubtitleElementIndex = mSubtitleElementModelList.size() + 1;
				mSubtitleElementModelList.emplace_back(pmodel);
				on_subtitle_elements_list_update(pmodel->get_url());
			}
		}
	);
	SetWindowLong(purl_subtitle_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_SUBTITLE_WINDOW);
}

void UrlSetting::motify_subtitle_elements_window_create(int item_id) {
	auto it = mSubtitleElementModelList.begin();
	if (mSubtitleElementModelList.size() < item_id) {
		return;
	}
	std::advance(it, item_id);
	UrlSubtitleElementSetting* purl_stream_element_window = new UrlSubtitleElementSetting(mHwnd, mHinstance, UrlClickType::MOTIFY_URL, *it);
	EnableWindow(mHwnd, FALSE);
	purl_stream_element_window->set_close_call_back(
		[this](WindowCloseType close_type, UrlClickType click_type, DemoMediaSubtitleElementModel* pmodel) {
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				int index = 0;
				std::list<DemoMediaSubtitleElementModel*> new_element_model = std::list<DemoMediaSubtitleElementModel*>();
				for (auto it : mSubtitleElementModelList)
				{
					if (index == mSubtitleElementIndex)
					{
						new_element_model.emplace_back(pmodel);
					}
					else
					{
						new_element_model.emplace_back(it);
					}
					index++;
				}
				mSubtitleElementModelList = new_element_model;
				// 添加行数据
				std::string url = pmodel->get_url();
				LVITEMW  lv_item;
				lv_item.mask = LVIF_TEXT;
				lv_item.iSubItem = 0;
				lv_item.pszText = (LPWSTR)_T(url.c_str());
				lv_item.iItem = mStreamElementIndex;
				ListView_SetItem(mUrlSubtitleElementsListWindow, &lv_item);
			}
		}
	);
	SetWindowLong(purl_stream_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_STREAM_WINDOW);
}

void UrlSetting::add_stream_elements_window_create() {
	UrlStreamElementSetting* purl_stream_element_window = new UrlStreamElementSetting(mHwnd, mHinstance,UrlClickType::ADD_URL,nullptr);
	EnableWindow(mHwnd, FALSE);
	purl_stream_element_window->set_close_call_back(
		[this](WindowCloseType close_type,UrlClickType click_type, DemoMediaStreamElementModel* pmodel){
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				mStreamElementIndex = mStreamElementModelList.size() +1;
				mStreamElementModelList.emplace_back(pmodel);
				on_streem_elements_list_update(pmodel->get_url());
			}
		}
	);
	SetWindowLong(purl_stream_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_STREAM_WINDOW);
}


void UrlSetting::motify_stream_elements_window_create(int item_id) {
	auto it = mStreamElementModelList.begin();
	if (mStreamElementModelList.size() < item_id || item_id < 0) {
		return;
	}
	std::advance(it, item_id);
	UrlStreamElementSetting* purl_stream_element_window = new UrlStreamElementSetting(mHwnd, mHinstance, UrlClickType::MOTIFY_URL, *it);
	EnableWindow(mHwnd, FALSE);
	purl_stream_element_window->set_close_call_back(
		[this](WindowCloseType close_type, UrlClickType click_type, DemoMediaStreamElementModel* pmodel) {
			EnableWindow(mHwnd, TRUE);
			if (close_type == WindowCloseType::SUBMIT_CLOSE) {
				
				int index = 0;
				std::list<DemoMediaStreamElementModel*> new_element_model = std::list<DemoMediaStreamElementModel*>();
				for (auto it : mStreamElementModelList)
				{
					if (index == mStreamElementIndex)
					{
						new_element_model.emplace_back(pmodel);
					}
					else
					{
						new_element_model.emplace_back(it);
					}
					index++;
				}

				mStreamElementModelList = new_element_model;
				// 添加行数据
				std::string url = pmodel->get_url();
				LVITEMW  lv_item;
				lv_item.mask = LVIF_TEXT;
				lv_item.iSubItem = 0;
				lv_item.pszText = (LPWSTR)_T(url.c_str());
				lv_item.iItem = mStreamElementIndex;
				ListView_SetItem(mUrlStreamElementsListWindow, &lv_item);
			}
		}
	);
	SetWindowLong(purl_stream_element_window->get_hwnd(), GWL_ID, ID_URL_ADD_STREAM_WINDOW);
}


void UrlSetting::delete_stream_elements_window_create(int item_id) {
	if (!mStreamElementModelList.empty() && item_id < mStreamElementModelList.size())
	{
		auto it = mStreamElementModelList.begin();
		std::advance(it, item_id);
		mStreamElementModelList.erase(it);
		ListView_DeleteItem(mUrlStreamElementsListWindow, item_id);
	}
}

void UrlSetting::delete_subtitle_elements_window_create(int item_id) {
	if (!mSubtitleElementModelList.empty() && item_id < mSubtitleElementModelList.size())
	{
		auto it = mSubtitleElementModelList.begin();
		std::advance(it, item_id);
		mSubtitleElementModelList.erase(it);
		ListView_DeleteItem(mUrlSubtitleElementsListWindow, item_id);
	}
}

void UrlSetting::set_stream_item_id(int url_id) {
	mStreamElementIndex = url_id;
}

int UrlSetting::get_stream_item_id() {
	return mStreamElementIndex;
}
void UrlSetting::set_subtitle_item_id(int url_id) {
	mSubtitleElementIndex = url_id;
}

int UrlSetting::get_subtitle_item_id() {
	return mSubtitleElementIndex;
}