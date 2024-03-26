#pragma once

#include "QPlayerExport.h"

namespace QMedia {
	/// <summary>
	/// 渲染相关监听
	/// </summary>
	class QPLAYER_API QIPlayerRenderListener{
	public:
		QIPlayerRenderListener() = default;

		virtual ~QIPlayerRenderListener() = default;

		QIPlayerRenderListener(const QIPlayerRenderListener&) = delete;

		QIPlayerRenderListener(QIPlayerRenderListener&&) = delete;

		QIPlayerRenderListener& operator=(const QIPlayerRenderListener&) = delete;

		QIPlayerRenderListener& operator=(QIPlayerRenderListener&&) = delete;

		/// <summary>
		/// 首帧耗时回调
		/// </summary>
		/// <param name="elapsed_time"> 从 play_media_model 开始到首帧渲染出来的总耗时 单位：毫秒 </param>
		virtual void on_first_frame_rendered(int64_t elapsed_time) = 0;
	};
}
