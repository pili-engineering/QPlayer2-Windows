#pragma once
#include <string>
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 字幕相关监听
	/// </summary>
	class QPLAYER_API QIPlayerSubtitleListener
	{
	public:
		QIPlayerSubtitleListener() = default;
		virtual ~QIPlayerSubtitleListener() = default;
		QIPlayerSubtitleListener(const QIPlayerSubtitleListener&) = delete;

		QIPlayerSubtitleListener(QIPlayerSubtitleListener&&) = delete;

		QIPlayerSubtitleListener& operator=(const QIPlayerSubtitleListener&) = delete;

		QIPlayerSubtitleListener& operator=(QIPlayerSubtitleListener&&) = delete;

		/// <summary>
		/// 字幕文本回调
		/// </summary>
		/// <param name="text"> 当前字幕的文本 </param>
		virtual void on_subtitle_text_changed(const std::string & text) = 0;

		/// <summary>
		/// 字幕切换回调
		/// </summary>
		/// <param name="name"> 当前的字幕名称 </param>
		virtual void on_subtitle_name_changed(const std::string & name) = 0;

		/// <summary>
		/// 字幕开启状态改变回调
		/// </summary>
		/// <param name="enable"> 当前字幕是否开启 true 开启 false 关闭 </param>
		virtual void on_subtitle_enable(bool enable) = 0;

		/// <summary>
		/// 字幕加载结果回调
		/// </summary>
		/// <param name="name"> 字幕名称 </param>
		/// <param name="result"> 字幕加载结果 true 成功 false 失败 </param>
		virtual void on_subtitle_loaded(const std::string & name, bool result) = 0;

		/// <summary>
		/// 字幕解码结果回调
		/// </summary>
		/// <param name="name"> 字幕名称 </param>
		/// <param name="result"> 字幕解码结果 true 成功 false 失败 </param>
		virtual void on_subtitle_decoded(const std::string & name, bool result) = 0;
	private:

	};
}
