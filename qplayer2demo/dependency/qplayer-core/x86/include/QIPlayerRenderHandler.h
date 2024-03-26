#pragma once
#include "QPlayerExport.h"
#include <windows.h>
#include "QPlayerSetting.h"
#include "QUrlType.h"
#include "QPlayerSetting.h"
#include "QIPlayerListenersHeader.h"

namespace QMedia {

	/// <summary>
	/// 播放器渲染句柄
	/// </summary>
	class QPLAYER_API QIPlayerRenderHandler  {
	public:
		QIPlayerRenderHandler() = default;

		virtual ~QIPlayerRenderHandler() = default;

		QIPlayerRenderHandler(const QIPlayerRenderHandler&) = delete;

		QIPlayerRenderHandler(QIPlayerRenderHandler&&) = delete;

		QIPlayerRenderHandler& operator=(const QIPlayerRenderHandler&) = delete;

		QIPlayerRenderHandler& operator=(QIPlayerRenderHandler&&) = delete;

		/// <summary>
		/// 设置 hwnd
		/// </summary>
		/// <param name="hwnd"> 播放器窗口句柄 </param>
		/// <returns> true 设置成功 false 设置失败 </returns>
		virtual bool set_window_hwnd(HWND hwnd) = 0;
		
		/// <summary>
		/// 设置渲染view的大小
		/// </summary>
		/// <param name="width"> 宽度 </param>
		/// <param name="height"> 高度 </param>
		/// <returns> true 设置成功 false 设置失败 </returns>
		virtual bool synch_window_size(uint16_t width, uint16_t height) = 0;

		/// <summary>
		/// 设置视频渲染比例
		/// </summary>
		/// <param name="ratio"> 渲染比例 </param>
		/// <returns> true 设置成功 false 设置失败 </returns>
		virtual bool set_render_ratio(QPlayerSetting::QPlayerRenderRatio ratio) = 0;

		/// <summary>
		/// 设置色觉优化
		/// </summary>
		/// <param name="blind_type"> 色盲模式 </param>
		/// <returns> true 设置成功 false 设置失败 </returns>
		virtual bool set_blind_type(QPlayerSetting::QPlayerBlind blind_type) = 0;

		/// <summary>
		/// 设置VR视频的旋转角度(windows 暂不支持 VR 视频)
		/// </summary>
		/// <param name="rotatex"> 横向角度 （360度制） </param>
		/// <param name="rotatey"> 纵向角度 （360度制） </param>
		/// <returns> true 设置成功 false 设置失败 </returns>
		//virtual bool set_panorama_view_rotate(float rotatex, float rotatey) = 0;

		/// <summary>
		/// 添加渲染监听
		/// </summary>
		/// <param name="plistener"> 渲染监听 </param>
		virtual void add_render_listener(QMedia::QIPlayerRenderListener* plistener) = 0;

		/// <summary>
		/// 移除渲染监听
		/// </summary>
		/// <param name="plistener"> 渲染监听 </param>
		virtual void remove_render_listener(QMedia::QIPlayerRenderListener* plistener) = 0;

		/// <summary>
		/// 移除所有的渲染监听
		/// </summary>
		virtual void remove_all_render_listeners() = 0;
	};
}