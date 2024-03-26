#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// 播放器 buffering 状态通知
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
		/// buffering 开始通知
		/// </summary>
		virtual void on_buffering_start() = 0;

		/// <summary>
		/// buffering 结束通知
		/// </summary>
		virtual void on_buffering_end() = 0;
	private:

	};
}