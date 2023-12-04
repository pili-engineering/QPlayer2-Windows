#pragma once

#include "framework.h"
#include <list>
#include <string>
class PlayStartPostitionWindow
{
public:
	PlayStartPostitionWindow(HWND hwnd,HINSTANCE hinstance);
	~PlayStartPostitionWindow();

private:

	static LRESULT CALLBACK main_play_start_position_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	void on_list_create();

	std::string wchar_to_string(HWND hwnd);
private:

	HWND mHwnd;
	HINSTANCE mHinstance;
	HWND mPlayStartPositionInput;
};

