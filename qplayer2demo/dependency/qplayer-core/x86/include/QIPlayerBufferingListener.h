#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// ������ buffering ״̬֪ͨ
	class QPLAYER_API QIPlayerBufferingListener
	{
	public:
		QIPlayerBufferingListener() = default;
		virtual ~QIPlayerBufferingListener() = default;
		QIPlayerBufferingListener(const QIPlayerBufferingListener&) = delete;

		QIPlayerBufferingListener(QIPlayerBufferingListener&&) = delete;

		QIPlayerBufferingListener& operator=(const QIPlayerBufferingListener&) = delete;

		QIPlayerBufferingListener& operator=(QIPlayerBufferingListener&&) = delete;

		/// <summary>
		/// buffering ��ʼ֪ͨ
		/// </summary>
		virtual void on_buffering_start() = 0;

		/// <summary>
		/// buffering ����֪ͨ
		/// </summary>
		virtual void on_buffering_end() = 0;
	private:

	};
}