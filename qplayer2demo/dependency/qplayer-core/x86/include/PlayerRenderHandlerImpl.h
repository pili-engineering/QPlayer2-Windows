#pragma once
#include "QIPlayerRenderHandler.h"
#include "QPlayerSetting.h"
#include <windows.h>
#include <list>
#include <map>
#include <any>
#include "QPlayerNotify.h"
#include "QLogLevel.h"
#include "LogInterface.h"
namespace QMedia {
	class QWindowsPlayer;
	class PlayerRenderHandlerImpl: public QIPlayerRenderHandler ,public LogInterface{
	public:
		PlayerRenderHandlerImpl(QWindowsPlayer* pinner_player);

		~PlayerRenderHandlerImpl() override;

		PlayerRenderHandlerImpl(const PlayerRenderHandlerImpl&) = delete;

		PlayerRenderHandlerImpl(PlayerRenderHandlerImpl&&) = delete;

		PlayerRenderHandlerImpl& operator=(const PlayerRenderHandlerImpl&) = delete;

		PlayerRenderHandlerImpl& operator=(PlayerRenderHandlerImpl&&) = delete;

		void log(QMedia::QLogLevel level, const std::string& message) override;
	
		/**
		 * ����surface
		 * @param surface see[android.view.Surface]
		 * @return true ���óɹ� false ����ʧ��
		 */
		bool set_window_hwnd(HWND hwnd) override;

		/***
		 * ������Ⱦview�Ĵ�С
		 * @param width ���
		 * @param height �߶�
		 * @return true ���óɹ� false ����ʧ��
		 */
		bool synch_window_size(uint16_t width, uint16_t height) override;

		/***
		 * ������Ƶ��Ⱦ����
		 * @param ratio see[QPlayerSetting.QPlayerRenderRatio]
		 * @return true ���óɹ� false ����ʧ��
		 */
		bool set_render_ratio(QPlayerSetting::QPlayerRenderRatio ratio) override;

		/***
		 * ����ɫ���Ż�
		 * @param type see[QPlayerSetting.QPlayerBlind]
		 * @return true ���óɹ� false ����ʧ��
		 */
		bool set_blind_type(QPlayerSetting::QPlayerBlind blind_type) override;

		/***
		 * ����VR��Ƶ����ת�Ƕ�
		 * @param rotatex ����Ƕ� ��360���ƣ�
		 * @param rotatey ����Ƕ� ��360���ƣ�
		 * @return true ���óɹ� false ����ʧ��
		 */
		bool set_panorama_view_rotate(float rotatex, float rotatey) override;

		void add_render_listener(QMedia::QIPlayerRenderListener* plistener) override;

		void remove_render_listener(QMedia::QIPlayerRenderListener* plistener) override;

		void remove_all_render_listeners() override;

		void on_render_sync(int64_t elapsed_time);

		void on_notify_async(QMedia::QPlayerNotify notify_id, std::map<std::string, std::any>* pbundle);
		

	private:
		QWindowsPlayer* mpInnerPlayer;

		std::list<QIPlayerRenderListener*> mPlayerRenderListeners;
	};
}