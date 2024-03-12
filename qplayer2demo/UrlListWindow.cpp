#include "UrlListWindow.h"
#include "resource.h"
#include "DemoLog.h"
#include <CommCtrl.h>

#define CLASS_NAME					    "UrlListWindow"
#define RIGHT_MENU_ADD          100
#define RIGHT_MENU_MODIFY       101
#define RIGHT_MENU_DELETE       102

UrlListWindow::UrlListWindow(HWND hwnd, HINSTANCE hinstance, PlayerUrlListModelManager* purlmanager)
	: mHwnd(nullptr),
	mHinstance(nullptr),
	mItemId(0),
	mpModelManager(purlmanager),
	mListWindow(nullptr)
{

	HINSTANCE hinst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	mHinstance = hinst;
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = main_url_list_window_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinst;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT(L"UrlListWindow");
	wcex.hIconSm = NULL;

	if (!RegisterClassExW(&wcex)) {
		throw "UrlListWindow  create failed!";
	}

	mHwnd = CreateWindowW(wcex.lpszClassName, TEXT(L"UrlListWindow"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		10, 10, 300, 20, hwnd, NULL, hinst, NULL);

	if (mHwnd == nullptr)
	{
		throw "main window create failed!";
	}

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);


	mpModelManager->set_url_update_call_back(
		[this]() {
			if (mListWindow != nullptr)
			{
				DestroyWindow(mListWindow);
				mListWindow = nullptr;
			}
			on_list_create();
		}
	);
	mpModelManager->url_update();

}

UrlListWindow::~UrlListWindow()
{
	if (mpModelManager != nullptr)
	{
		mpModelManager = nullptr;
	} 	
}

LRESULT CALLBACK UrlListWindow::main_url_list_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	UrlListWindow* purl_window = (UrlListWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (message)
	{
	case WM_COMMAND: {

		switch (LOWORD(w_param)) {
		case RIGHT_MENU_ADD: {
			if (purl_window != nullptr) {
				purl_window->mouse_right_click_add();
			}
			break;
		}
		case RIGHT_MENU_MODIFY: {
			if (purl_window != nullptr) {
				purl_window->mouse_right_click_motify(purl_window->get_item_id());
			}
			break;
		}
		case RIGHT_MENU_DELETE: {
			if (purl_window != nullptr) {
				purl_window->mouse_right_click_delete(purl_window->get_item_id());
			}
			break;
		}
		default:
			break;
		}

	}
	case WM_SIZE:
	{
		if (purl_window != nullptr) {
			purl_window->url_list_resize();
		}
		break;
	}
	case WM_NOTIFY:
	{
		NMHDR* pnmhdr = (NMHDR*)l_param;
		if (pnmhdr->hwndFrom == purl_window->mListWindow)
		{
			LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
			int selected_index = pnmia->iItem;
			if ((int)(pnmhdr->code) == (int)LVN_ITEMACTIVATE)
			{
				purl_window->url_click(selected_index);
			}
			else if((int)(pnmhdr->code) == (int)NM_RCLICK)
			{LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)l_param;
				int selected_index = pnmia->iItem;
				purl_window->set_item_id(selected_index);
			}
		}
		break;
	}
	case WM_CONTEXTMENU: {

		purl_window->mouse_right_click_menu(hwnd);
		break;
	}
	default:
		return (DefWindowProc(hwnd, message, w_param, l_param));
		break;
	}
	return 0;
}

void UrlListWindow::url_list_resize() {
	RECT window_rect;
	GetWindowRect(mHwnd, &window_rect);

	int width = window_rect.right - window_rect.left;
	int height = window_rect.bottom - window_rect.top;
	SetWindowPos(mListWindow, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	ListView_SetColumnWidth(mListWindow, width, 20);

}
//�����б�
LRESULT UrlListWindow::on_list_create() {

	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);

	mListWindow = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 0, 0, windowRect.right - windowRect.left, 20, mHwnd, NULL, NULL, NULL);

	ListView_SetExtendedListViewStyle(mListWindow, LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);

	// �����ͷ
	LVCOLUMNW  lv_column;
	lv_column.mask = LVCF_WIDTH | LVCF_TEXT;
	lv_column.pszText = (LPWSTR)_T("url");
	lv_column.cx = windowRect.right - windowRect.left;
	if (ListView_InsertColumn(mListWindow, 0, &lv_column) == -1) {
		throw "ListView_InsertColumn error";
	}

	// ���������
	LVITEMW  lv_item;
	lv_item.mask = LVIF_TEXT;
	lv_item.iSubItem = 0;
	for (int i = 0; i < mpModelManager->get_url_models_count();i++)
	{
		std::string name_str = mpModelManager->get_url_model_for_index(i)->get_name();
		lv_item.pszText = (LPWSTR)_T(name_str.c_str());
		lv_item.iItem = i;
		ListView_InsertItem(mListWindow, &lv_item);
	}
	url_list_resize();
	return 0;
}
//�ַ���ת LPWSTR ������ UI ��ʾ
LPWSTR UrlListWindow::string_to_LPWSTR(const std::string& str) {
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	LPWSTR buffer = new WCHAR[size];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
	return buffer;
}

HWND UrlListWindow::get_hwnd() {
	return mHwnd;
}
//��ַ�б��������¼�
void  UrlListWindow::url_click(int url_id) {

	DemoLog::log_string(CLASS_NAME, __LINE__, "url_click");
	mPlayControlCallback(mHwnd,mpModelManager->get_url_model_for_index(url_id)->get_media_model());
	
}
//���ûص�����ָ��
void UrlListWindow::set_play_control_callback(playCallbackFunction call_back) {
	mPlayControlCallback = call_back;
}

// �����Զ����Ҽ��˵�
void UrlListWindow::mouse_right_click_menu(HWND hwnd) {
	
	HMENU right_menu = CreatePopupMenu();
	AppendMenu(right_menu, MF_STRING, RIGHT_MENU_ADD, "���");
	AppendMenu(right_menu, MF_STRING, RIGHT_MENU_MODIFY, "�޸�");
	AppendMenu(right_menu, MF_STRING, RIGHT_MENU_DELETE, "ɾ��");
	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(hwnd);
	TrackPopupMenu(right_menu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hwnd, NULL);
	DestroyMenu(right_menu);
}
//��� URL �ص�
void UrlListWindow::mouse_right_click_add() {
	mMouseRightClickCallBack(0, UrlClickType::ADD_URL);
}
//�޸� URL �ص�
void UrlListWindow::mouse_right_click_motify(int item_id) {
	mMouseRightClickCallBack(item_id, UrlClickType::MOTIFY_URL);
}
//ɾ�� URL �ص�
void UrlListWindow::mouse_right_click_delete(int item_id) {
	mMouseRightClickCallBack(item_id, UrlClickType::DELETE_URL);

}

//�����Ҽ��ص�
void UrlListWindow::set_mouse_right_click_callback(mouseRightClickCallbackFunction call_back) {
	mMouseRightClickCallBack = call_back;
}

//��¼�Ҽ��������һ�� itemid
void UrlListWindow::set_item_id(int url_id) {
	mItemId = url_id;
}

//��ȡ���һ���Ҽ��������һ�� itemid
int UrlListWindow::get_item_id() {
	return mItemId;
}