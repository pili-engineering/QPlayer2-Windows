#include "ToastWindow.h"
#include <CommCtrl.h>

ToastWindow::ToastWindow(HWND hwnd)
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

	mToastNum = 0;
	on_list_create();
}

ToastWindow::~ToastWindow()
{
}
 LRESULT CALLBACK ToastWindow::main_toast_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
	ToastWindow* toast_window = (ToastWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (message)
	{

	case WM_SIZE:
	{
		if (toast_window != nullptr) {
			toast_window->toast_list_resize();
		}
		break;
	}
	default:
		break;
	}
	return (DefWindowProc(hwnd, message, w_param, l_param));
}

void ToastWindow::toast_list_resize() {
	RECT windowRect;
	GetWindowRect(mHwnd, &windowRect);

	// 计算窗口的宽度和高度
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	SetWindowPos(mListWindow, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

}
HWND ToastWindow::get_hwnd() {
	return mHwnd;
}
LRESULT ToastWindow::on_list_create() {

	// 创建列表视图控件
	mListWindow = CreateWindowEx(0, WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOCOLUMNHEADER, 0, 0, 500, 400, mHwnd, NULL, mHinstance, NULL);

	// 设置列表视图控件的样式
	ListView_SetExtendedListViewStyle(mListWindow, LVS_EX_FULLROWSELECT);

	// 添加列头
	LVCOLUMNW  lvColumn;
	lvColumn.mask =  LVCF_WIDTH;
	lvColumn.cx = 300;
	ListView_InsertColumn(mListWindow, 0, &lvColumn);

	return LRESULT();
}

void ToastWindow::add_item(std::string text) {
	// 添加行数据
	LVITEMW  lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPWSTR)_T(text.c_str());
	lvItem.iItem = 0;
	ListView_InsertItem(mListWindow, &lvItem);
}