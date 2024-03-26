#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 推流端视频长宽变化监听
	/// </summary>
	class QPLAYER_API QIPlayerVideoFrameSizeChangeListener
	{
	public:
		QIPlayerVideoFrameSizeChangeListener() = default;
		virtual ~QIPlayerVideoFrameSizeChangeListener() = default;
		QIPlayerVideoFrameSizeChangeListener(const QIPlayerVideoFrameSizeChangeListener&) = delete;

		QIPlayerVideoFrameSizeChangeListener(QIPlayerVideoFrameSizeChangeListener&&) = delete;

		QIPlayerVideoFrameSizeChangeListener& operator=(const QIPlayerVideoFrameSizeChangeListener&) = delete;

		QIPlayerVideoFrameSizeChangeListener& operator=(QIPlayerVideoFrameSizeChangeListener&&) = delete;

		/// <summary>
		/// 推流端视频长宽变化回调
		/// </summary>
		/// <param name="width"> 宽度 </param>
		/// <param name="height"> 高度 </param>
		virtual void on_video_frame_size_changed(int width, int height) = 0;
	private:

	};
}
