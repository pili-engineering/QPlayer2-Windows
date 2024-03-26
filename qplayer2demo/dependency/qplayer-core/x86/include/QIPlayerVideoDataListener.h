#pragma once
#include "QPlayerExport.h"
#include "QVideoType.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// 视频数据上抛监听
	/// </summary>
	class QPLAYER_API QIPlayerVideoDataListener
	{
	public:
		QIPlayerVideoDataListener() = default;
		virtual ~QIPlayerVideoDataListener() = default;
		QIPlayerVideoDataListener(const QIPlayerVideoDataListener&) = delete;

		QIPlayerVideoDataListener(QIPlayerVideoDataListener&&) = delete;

		QIPlayerVideoDataListener& operator=(const QIPlayerVideoDataListener&) = delete;

		QIPlayerVideoDataListener& operator=(QIPlayerVideoDataListener&&) = delete;

		/// <summary>
		/// 视频数据上抛回调
		/// </summary>
		/// <param name="width"> 视频宽度 </param>
		/// <param name="height"> 视频高度 </param>
		/// <param name="video_type"> 视频类型 </param>
		/// <param name="buffer"> 视频数据 </param>
		/// <param name="size"> 视频数据长度 </param>
		virtual void on_video_data(int width, int height, QMedia::QVideoType video_type, const std::unique_ptr<uint8_t[]>& buffer, uint64_t size) = 0;
	private:

	};
}
