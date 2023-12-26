#pragma once
#include "framework.h"
#include "CurrentDataModelManager.h"
namespace QMedia {
	class QIPlayerContext;
	class QIPlayerControlHandler;
	class QIPlayerRenderHandler;
}
class VideoRenderWindow;
class PlayerWindow
{
private:
	static LRESULT CALLBACK main_player_window_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);

	LRESULT on_receive_message(HWND hwnd, UINT massage, WPARAM w_param, LPARAM l_param);

	LRESULT on_resize();

	bool notify_resize_to_player();

	static BOOL CALLBACK resize_child_windows_proc(HWND hwnd_child, LPARAM l_param);


public:
	PlayerWindow(HWND parent_hwnd, HINSTANCE instance, CurrentDataModelManager* pcurrent_data_model_manager);

	~PlayerWindow();

	PlayerWindow(PlayerWindow&&) = delete;

	PlayerWindow(const PlayerWindow&) = delete;

	PlayerWindow& operator=(PlayerWindow &&) = delete;

	PlayerWindow& operator=(const PlayerWindow&) = delete;

	HWND get_hwnd();

	QMedia::QIPlayerControlHandler* get_control_handler();

	QMedia::QIPlayerRenderHandler* get_render_handler();

	QMedia::QIPlayerContext* get_context();

private:

	HWND mHwnd;

	QMedia::QIPlayerContext* mpPlayerContext;

	VideoRenderWindow* mpVideoRenderWindow;

	CurrentDataModelManager* mpCurrentDataModelManager;
};

