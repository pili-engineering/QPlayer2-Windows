#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 播放器进度监听
	/// </summary>
	class QPLAYER_API QIPlayerProgressListener
	{
	public:
		QIPlayerProgressListener() = default;
		virtual ~QIPlayerProgressListener() = default;
		QIPlayerProgressListener(const QIPlayerProgressListener&) = delete;

		QIPlayerProgressListener(QIPlayerProgressListener&&) = delete;

		QIPlayerProgressListener& operator=(const QIPlayerProgressListener&) = delete;

		QIPlayerProgressListener& operator=(QIPlayerProgressListener&&) = delete;

		/// <summary>
		/// 进度变更回调
		/// </summary>
		/// <param name="progress"> 当前进度 单位：毫秒 </param>
		/// <param name="duration"> 当前视频总时长 单位： 毫秒 </param>
		virtual void on_progress_changed(int64_t progress, int64_t duration) = 0;
	private:

	};
}
