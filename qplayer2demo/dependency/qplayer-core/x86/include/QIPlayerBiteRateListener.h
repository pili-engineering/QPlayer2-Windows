#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ʵʱ���ʼ���
	/// </summary>
	class QPLAYER_API QIPlayerBiteRateListener
	{
	public:
		QIPlayerBiteRateListener() = default;
		virtual ~QIPlayerBiteRateListener() = default;
		QIPlayerBiteRateListener(const QIPlayerBiteRateListener&) = delete;

		QIPlayerBiteRateListener(QIPlayerBiteRateListener&&) = delete;

		QIPlayerBiteRateListener& operator=(const QIPlayerBiteRateListener&) = delete;

		QIPlayerBiteRateListener& operator=(QIPlayerBiteRateListener&&) = delete;

		/// <summary>
		/// ���ʱ仯�ص�
		/// </summary>
		/// <param name="bit_rate"> ���� ��λ��bps </param>
		virtual void on_bite_rate_changed(int bit_rate) = 0;
	private:

	};
}