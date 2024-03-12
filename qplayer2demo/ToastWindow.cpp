#include "ToastWindow.h"
#include <CommCtrl.h>

ToastWindow::ToastWindow(HWND hwnd):mToastNum(0)
{

	HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	mHinstance = hInst;
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = main_toast_window_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT(L"ToastWindow");
	wcex.hIconSm = NULL;

	if (!RegisterClassExW(&wcex)) {
		throw "ToastWindow  create failed!";
	}

	mHwnd = CreateWindowW(wcex.lpszClassName, TEXT(L"ToastWindow"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 500, 280, 220, hwnd, NULL, hInst, NULL);

	if (mHwnd == nullptr)
	{
		throw "ToastWindow create failed!";
	}

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);

	on_list_create();
}

ToastWindow::~ToastWindow()
{
}
 LRESULT CALLBACK ToastWindow::main_toast_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	ToastWindow* ptoast_window = (ToastWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (message)
	{

	case WM_SIZE:
	{
		if (ptoast_window != nullptr) {
			ptoast_window->toast_list_resize();
		}
		break;
	}
	case WM_NOTIFY:
	{
		NMHDR* pnmhdr = (NMHDR*)l_param;
		if (pnmhdr->hwndFrom == ptoast_window->mListWindow) {
			if ((int)(pnmhdr->code) == (int)LVN_INSERTITEM)
			{
				for (int i = 0; i < ptoast_window->mToastNum; i++)
				{
					ListView_SetItemState(ptoast_window->mListWindow, i, 0, LVIS_SELECTED);
				}
				ListView_SetItemState(ptoast_window->mListWindow, ptoast_window->mToastNum, LVIS_SELECTED, LVIS_SELECTED);
				ListView_EnsureVisible(ptoast_window->mListWindow, ptoast_window->mToastNum, FALSE);
			}
		}
		break;
	}
	default:
		break;
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

void ToastWindow::toast_list_resize() {
	RECT window_rect;
	GetWindowRect(mHwnd, &window_rect);
	int width = window_rect.right - window_rect.left;
	int height = window_rect.bottom - window_rect.top;
	SetWindowPos(mListWindow, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

}
HWND ToastWindow::get_hwnd() {
	return mHwnd;
}
LRESULT ToastWindow::on_list_create() {

	// �����б���ͼ�ؼ�
	mListWindow = CreateWindowEx(0, WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 0, 0, 500, 400, mHwnd, NULL, mHinstance, NULL);
	ListView_SetExtendedListViewStyle(mListWindow, LVS_EX_FULLROWSELECT);

	// �����ͷ
	LVCOLUMNW  lv_column;
	lv_column.mask = LVCF_WIDTH | LVCF_TEXT;
	lv_column.pszText = (LPWSTR)_T("��־");
	lv_column.cx = 300;
	ListView_InsertColumn(mListWindow, 0, &lv_column);

	return LRESULT();
}

void ToastWindow::add_item(const std::string& text) {
	// ���������
	LVITEMW  lv_item;
	lv_item.mask = LVIF_TEXT;
	lv_item.iSubItem = 0;
	lv_item.pszText = (LPWSTR)_T(text.c_str());
	lv_item.iItem = mToastNum;
	ListView_InsertItem(mListWindow, &lv_item);
	mToastNum++;
}