#pragma once
#include <string>
#include "QPlayerExport.h"
#include "QUrlType.h"
namespace QMedia {
	/// <summary>
	/// 播放器清晰度相关监听
	/// </summary>
	class QPLAYER_API QIPlayerQualityListener
	{
	public:
		QIPlayerQualityListener() = default;
		virtual ~QIPlayerQualityListener() = default;
		QIPlayerQualityListener(const QIPlayerQualityListener&) = delete;

		QIPlayerQualityListener(QIPlayerQualityListener&&) = delete;

		QIPlayerQualityListener& operator=(const QIPlayerQualityListener&) = delete;

		QIPlayerQualityListener& operator=(QIPlayerQualityListener&&) = delete;

		/// <summary>
		/// 开始切换清晰度
		/// </summary>
		/// <param name="user_type"> 切换清晰度的 URL 的 userType </param>
		/// <param name="url_type"> 切换清晰度的 URL 的 urlType </param>
		/// <param name="old_quality"> 切换清晰度前的清晰度 </param>
		/// <param name="new_quality"> 切换清晰度后的清晰度 </param>
		virtual void on_quality_switch_start(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// 清晰度切换完成
		/// </summary>
		/// <param name="user_type"> 切换清晰度的 URL 的 userType </param>
		/// <param name="url_type"> 切换清晰度的 URL 的 urlType </param>
		/// <param name="old_quality"> 切换清晰度前的清晰度 </param>
		/// <param name="new_quality"> 切换清晰度后的清晰度 </param>
		virtual void on_quality_switch_complete(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// 清晰度切换取消
		/// </summary>
		/// <param name="user_type"> 切换清晰度的 URL 的 userType </param>
		/// <param name="url_type"> 切换清晰度的 URL 的 urlType </param>
		/// <param name="old_quality"> 切换清晰度前的清晰度 </param>
		/// <param name="new_quality"> 切换清晰度后的清晰度 </param>
		virtual void on_quality_switch_canceled(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// 清晰度切换失败
		/// </summary>
		/// <param name="user_type"> 切换清晰度的 URL 的 userType </param>
		/// <param name="url_type"> 切换清晰度的 URL 的 urlType </param>
		/// <param name="old_quality"> 切换清晰度前的清晰度 </param>
		/// <param name="new_quality"> 切换清晰度后的清晰度 </param>
		virtual void on_quality_switch_failed(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// 目前仅支持同时有一个清晰度切换事件，如果前一个切换还未完成，再次切换清晰度，则会回调该函数
		/// </summary>
		/// <param name="user_type"> 切换清晰度的 URL 的 userType </param>
		/// <param name="url_type"> 切换清晰度的 URL 的 urlType </param>
		virtual void on_quality_switch_retry_later(const std::string & user_type, QMedia::QUrlType url_type) = 0;
	private:

	};
}
