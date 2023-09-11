
#include "toast2.h"
#include <iostream>
#include "resource.h"
#include "DemoLog.h"
#include <CommCtrl.h>

toast2::toast2(HWND hwnd ,HINSTANCE hinstance)
	: mHwnd(nullptr),
	mHinstance(nullptr)
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
	wcex.lpszClassName = TEXT(L"toast2");
	wcex.hIconSm = NULL;

	if (!RegisterClassExW(&wcex)) {
		throw "UrlListWindow  create failed!";
	}

	mHwnd = CreateWindowW(wcex.lpszClassName, TEXT(L"toast2"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		1255, 510, 280, 220, hwnd, NULL, hInst, NULL);

	if (mHwnd == nullptr)
	{
		throw "main window create failed!";
	}

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);

	on_list_create();
}

toast2::~toast2()
{
}

LRESULT CALLBACK toast2::main_toast_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	toast2* url_window = (toast2*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (message)
	{
	case WM_SIZE:
	{
		if (url_window != nullptr) {
			url_window->toast_list_resize();
		}
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(w_param);
		break;
	}

	default:
		break;
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

void toast2::toast_list_resize() {
	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);

	// 计算窗口的宽度和高度
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	SetWindowPos(mListWindow, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

}
LRESULT toast2::on_list_create() {

	// 创建列表视图控件
	mListWindow = CreateWindowEx(0, WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOCOLUMNHEADER, 0, 0, 500, 400, mHwnd, NULL, mHinstance, NULL);

	// 设置列表视图控件的样式
	ListView_SetExtendedListViewStyle(mListWindow, LVS_EX_FULLROWSELECT);

	// 添加列头
	LVCOLUMNW  lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.pszText = (LPWSTR)_T("url");
	lvColumn.cx = 300;
	ListView_InsertColumn(mListWindow, 0, &lvColumn);



	return 0;
}


HWND toast2::get_hwnd() {
	return mHwnd;
}

void toast2::add_item(std::string text) {
	// 添加行数据
	LVITEMW  lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPWSTR)_T(text.c_str());
	lvItem.iItem = 0;
	ListView_InsertItem(mListWindow, &lvItem);
}