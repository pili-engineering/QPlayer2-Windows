#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 像素格式或者音频 sample 格式不支持的监听
	/// </summary>
	class QPLAYER_API QIPlayerFormatListener
	{
	public:
		QIPlayerFormatListener() = default;
		virtual ~QIPlayerFormatListener() = default;
		QIPlayerFormatListener(const QIPlayerFormatListener&) = delete;

		QIPlayerFormatListener(QIPlayerFormatListener&&) = delete;

		QIPlayerFormatListener& operator=(const QIPlayerFormatListener&) = delete;

		QIPlayerFormatListener& operator=(QIPlayerFormatListener&&) = delete;

		/// <summary>
		/// 当前有 format 不支持，视频无法播放
		/// </summary>
		virtual void on_format_not_support() = 0;

	private:

	};
}