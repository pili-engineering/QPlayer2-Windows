#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// seek 监听
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
		/// seek 成功回调
		/// </summary>
		virtual void on_seek_success() = 0;

		/// <summary>
		///  seek 失败回调
		/// </summary>
		virtual void on_seek_failed() = 0;
	private:

	};
}
