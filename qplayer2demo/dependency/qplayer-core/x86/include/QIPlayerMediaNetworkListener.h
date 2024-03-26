#pragma once
#include <string>
#include "QOpenError.h"
#include "QPlayerExport.h"
#include "QUrlType.h"
namespace QMedia {
	/// <summary>
	/// 播放器网络相关监听
	/// </summary>
	class QPLAYER_API QIPlayerMediaNetworkListener
	{
	public:
		QIPlayerMediaNetworkListener() = default;
		virtual ~QIPlayerMediaNetworkListener() = default;
		QIPlayerMediaNetworkListener(const QIPlayerMediaNetworkListener&) = delete;

		QIPlayerMediaNetworkListener(QIPlayerMediaNetworkListener&&) = delete;

		QIPlayerMediaNetworkListener& operator=(const QIPlayerMediaNetworkListener&) = delete;

		QIPlayerMediaNetworkListener& operator=(QIPlayerMediaNetworkListener&&) = delete;

		/// <summary>
		/// 开始重连
		/// </summary>
		/// <param name="user_type"> 重连 url 的 userType </param>
		/// <param name="url_type">重连 url 的 urlType </param>
		/// <param name="url"> 重连的 url </param>
		/// <param name="retry_time"> 重连 url 的次数 </param>
		virtual void on_reconnect_start(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, int retry_time) = 0;

		/// <summary>
		/// 重连结束
		/// </summary>
		/// <param name="user_type"> 重连 url 的 userType </param>
		/// <param name="url_type"> 重连 url 的 urlType </param>
		/// <param name="url"> 重连的 url </param>
		/// <param name="retry_time"></param>
		/// <param name="error"> 重连 url 的次数 </param>
		virtual void on_reconnect_end(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, int retry_time, QMedia::QOpenError error) = 0;
		
		/// <summary>
		/// 打开失败
		/// </summary>
		/// <param name="user_type"> 打开失败 url 的 userType </param>
		/// <param name="url_type"> 打开失败 url 的 urlType </param>
		/// <param name="url"> 打开失败的 url </param>
		/// <param name="error">  打开失败 url 的 错误码 </param>
		virtual void on_open_failed(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, QMedia::QOpenError error) = 0;
	private:

	};
}
