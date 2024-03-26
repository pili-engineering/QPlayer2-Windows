#pragma once
#include <windows.h>
#include "QMediaEnumHeader.h"
#include "PlayerBaseMessageLoopQueueAdapter.h"

namespace QMedia {
	#define WM_QPLAYER_STATE (WM_USER + 600)
	#define WM_QPLAYER_NOTIFY (WM_USER + 601)
	class PlayerMessageLoopQueueAdapter: public PlayerBaseMessageLoopQueueAdapter {
	public:
		//�����ھ��������Ⱦ���ھ����ֻҪ��messageLoop���ڵĴ��ھ������
		PlayerMessageLoopQueueAdapter(HWND hwnd);

		~PlayerMessageLoopQueueAdapter() override;

		void on_state_changed_async_send(QPlayerState state) override;

		void on_notify_async_send(int notify_id, std::map<std::string, std::any>* pbundle) override;

		bool on_receive_message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		DWORD mMainThreadId;
		HWND mMainThreadWinWnd;
	};
}