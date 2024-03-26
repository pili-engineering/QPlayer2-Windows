#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ÒôÆµ¼àÌý
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
		/// ¾²Òô×´Ì¬¸Ä±ä»Øµ÷
		/// </summary>
		/// <param name="is_mute"> ÊÇ·ñ¾²Òô true ¾²Òô false ·Ç¾²Òô </param>
		virtual void on_mute_changed(bool is_mute) = 0;
	private:

	};
}
