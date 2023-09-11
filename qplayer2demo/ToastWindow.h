#pragma once
#include "framework.h"
#include <list>
#include <string>
class ToastWindow
{
public:
	ToastWindow(HWND hwnd);
	~ToastWindow();
	
public:
	HWND get_hwnd();

	void add_item(std::string text);
private:
	static LRESULT CALLBACK main_toast_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);
	LRESULT on_list_create();
	void toast_list_resize();
private:
	int mToastNum;

	HWND mHwnd;
	HINSTANCE mHinstance;
	HWND mListWindow;
};
