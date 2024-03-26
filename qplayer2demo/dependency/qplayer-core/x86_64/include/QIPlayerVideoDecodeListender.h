#pragma once
#include "QPlayerExport.h"
#include "QDecoderType.h"
namespace QMedia {
	/// <summary>
	/// 播放器解码监听
	/// </summary>
	class QPLAYER_API QIPlayerVideoDecodeListender
	{
	public:
		QIPlayerVideoDecodeListender() = default;
		virtual ~QIPlayerVideoDecodeListender() = default;
		QIPlayerVideoDecodeListender(const QIPlayerVideoDecodeListender&) = delete;

		QIPlayerVideoDecodeListender(QIPlayerVideoDecodeListender&&) = delete;

		QIPlayerVideoDecodeListender& operator=(const QIPlayerVideoDecodeListender&) = delete;

		QIPlayerVideoDecodeListender& operator=(QIPlayerVideoDecodeListender&&) = delete;

		/// <summary>
		/// 播放器解码类型回调
		/// </summary>
		/// <param name="type"> 解码类型 </param>
		virtual void on_video_decode_by_type(QMedia::QDecoderType type) = 0;

		/// <summary>
		/// 解码失败回调
		/// </summary>
		/// <param name="retry"> 是否降级重试成功 true 是 false 否 </param>
		virtual void on_decode_failed(bool retry) = 0;

		/// <summary>
		/// 如果当前视频解码所在设备或者 sdk 不支持，则回调该函数
		/// </summary>
		/// <param name="codec_id"> 视频解码的 id  </param>
		virtual void on_not_support_codec_format(int codec_id) = 0;
	private:

	};
}
