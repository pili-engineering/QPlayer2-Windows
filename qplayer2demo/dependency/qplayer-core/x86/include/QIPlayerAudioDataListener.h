#pragma once
#include "QSampleFormat.h"
#include "QChannelLayout.h"
#include "QPlayerExport.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// 音频数据监听
	/// </summary>
	class QPLAYER_API QIPlayerAudioDataListener
	{
	public:
		QIPlayerAudioDataListener() = default;
		virtual ~QIPlayerAudioDataListener() = default;
		QIPlayerAudioDataListener(const QIPlayerAudioDataListener&) = delete;

		QIPlayerAudioDataListener(QIPlayerAudioDataListener&&) = delete;

		QIPlayerAudioDataListener& operator=(const QIPlayerAudioDataListener&) = delete;

		QIPlayerAudioDataListener& operator=(QIPlayerAudioDataListener&&) = delete;

		/// <summary>
		/// 音频数据回调
		/// </summary>
		/// <param name="sample_rate"> 采样率 </param>
		/// <param name="format"> 格式 </param>
		/// <param name="channel_num"> 通道数 </param>
		/// <param name="channel_layout"> 声道 </param>
		/// <param name="audio_data"> 音频数据 </param>
		/// <param name="size">数据大小</param>
		virtual void on_audio_data(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, const std::unique_ptr<uint8_t[]>& audio_data, uint64_t size) = 0;
	private:

	};
}
