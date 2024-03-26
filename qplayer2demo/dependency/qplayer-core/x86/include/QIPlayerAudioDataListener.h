#pragma once
#include "QSampleFormat.h"
#include "QChannelLayout.h"
#include "QPlayerExport.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// ��Ƶ���ݼ���
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
		/// ��Ƶ���ݻص�
		/// </summary>
		/// <param name="sample_rate"> ������ </param>
		/// <param name="format"> ��ʽ </param>
		/// <param name="channel_num"> ͨ���� </param>
		/// <param name="channel_layout"> ���� </param>
		/// <param name="audio_data"> ��Ƶ���� </param>
		/// <param name="size">���ݴ�С</param>
		virtual void on_audio_data(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, const std::unique_ptr<uint8_t[]>& audio_data, uint64_t size) = 0;
	private:

	};
}
