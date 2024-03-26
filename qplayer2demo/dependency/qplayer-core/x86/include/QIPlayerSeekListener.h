#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// seek ����
	/// </summary>
	class QPLAYER_API QIPlayerSeekListener
	{
	public:
		QIPlayerSeekListener() = default;
		virtual ~QIPlayerSeekListener() = default;
		QIPlayerSeekListener(const QIPlayerSeekListener&) = delete;

		QIPlayerSeekListener(QIPlayerSeekListener&&) = delete;

		QIPlayerSeekListener& operator=(const QIPlayerSeekListener&) = delete;

		QIPlayerSeekListener& operator=(QIPlayerSeekListener&&) = delete;

		/// <summary>
		/// seek �ɹ��ص�
		/// </summary>
		virtual void on_seek_success() = 0;

		/// <summary>
		///  seek ʧ�ܻص�
		/// </summary>
		virtual void on_seek_failed() = 0;
	private:

	};
}
