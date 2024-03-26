#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ��Ƶ����
	/// </summary>
	class QPLAYER_API QIPlayerAudioListener
	{
	public:
		QIPlayerAudioListener() = default;
		virtual ~QIPlayerAudioListener() = default;
		QIPlayerAudioListener(const QIPlayerAudioListener&) = delete;

		QIPlayerAudioListener(QIPlayerAudioListener&&) = delete;

		QIPlayerAudioListener& operator=(const QIPlayerAudioListener&) = delete;

		QIPlayerAudioListener& operator=(QIPlayerAudioListener&&) = delete;

		/// <summary>
		/// ����״̬�ı�ص�
		/// </summary>
		/// <param name="is_mute"> �Ƿ��� true ���� false �Ǿ��� </param>
		virtual void on_mute_changed(bool is_mute) = 0;
	private:

	};
}
