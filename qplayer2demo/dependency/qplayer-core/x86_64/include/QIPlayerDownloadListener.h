#pragma once
#include "QPlayerExport.h"
#include <stdint.h>
namespace QMedia {
	/// <summary>
	/// 下载监听
	/// </summary>
	class QPLAYER_API QIPlayerDownloadListener
	{
	public:
		QIPlayerDownloadListener() = default;
		virtual ~QIPlayerDownloadListener() = default;
		QIPlayerDownloadListener(const QIPlayerDownloadListener&) = delete;

		QIPlayerDownloadListener(QIPlayerDownloadListener&&) = delete;

		QIPlayerDownloadListener& operator=(const QIPlayerDownloadListener&) = delete;

		QIPlayerDownloadListener& operator=(QIPlayerDownloadListener&&) = delete;

		/// <summary>
		/// 下载数据变化回调
		/// </summary>
		/// <param name="download_speed"> 下载速度 </param>
		/// <param name="buffer_pos"> 缓冲进度 </param>
		virtual void on_download_changed(int64_t download_speed, int64_t buffer_pos) = 0;

	private:

	};
}