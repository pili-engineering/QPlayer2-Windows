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
		 * 设置surface
		 * @param surface see[android.view.Surface]
		 * @return true 设置成功 false 设置失败
		 */
		bool set_window_hwnd(HWND hwnd) override;

		/***
		 * 设置渲染view的大小
		 * @param width 宽度
		 * @param height 高度
		 * @return true 设置成功 false 设置失败
		 */
		bool synch_window_size(uint16_t width, uint16_t height) override;

		/***
		 * 设置视频渲染比例
		 * @param ratio see[QPlayerSetting.QPlayerRenderRatio]
		 * @return true 设置成功 false 设置失败
		 */
		bool set_render_ratio(QPlayerSetting::QPlayerRenderRatio ratio) override;

		/***
		 * 设置色觉优化
		 * @param type see[QPlayerSetting.QPlayerBlind]
		 * @return true 设置成功 false 设置失败
		 */
		bool set_blind_type(QPlayerSetting::QPlayerBlind blind_type) override;

		/***
		 * 设置VR视频的旋转角度
		 * @param rotatex 横向角度 （360度制）
		 * @param rotatey 纵向角度 （360度制）
		 * @return true 设置成功 false 设置失败
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