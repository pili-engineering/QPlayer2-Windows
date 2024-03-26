#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 实时码率监听
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
		/// 码率变化回调
		/// </summary>
		/// <param name="bit_rate"> 码率 单位：bps </param>
		virtual void on_bite_rate_changed(int bit_rate) = 0;
	private:

	};
}