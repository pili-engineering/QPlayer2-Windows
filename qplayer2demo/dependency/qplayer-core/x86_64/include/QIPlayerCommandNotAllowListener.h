#pragma once
#include "QPlayerExport.h"
#include "QPlayerState.h"
#include <string>
namespace QMedia {
	/// <summary>
	/// 调用播放器接口时状态异常的监听
	/// </summary>
	class QPLAYER_API QIPlayerCommandNotAllowListener
	{
	public:
		QIPlayerCommandNotAllowListener() = default;
		virtual ~QIPlayerCommandNotAllowListener() = default;
		QIPlayerCommandNotAllowListener(const QIPlayerCommandNotAllowListener&) = delete;

		QIPlayerCommandNotAllowListener(QIPlayerCommandNotAllowListener&&) = delete;

		QIPlayerCommandNotAllowListener& operator=(const QIPlayerCommandNotAllowListener&) = delete;

		QIPlayerCommandNotAllowListener& operator=(QIPlayerCommandNotAllowListener&&) = delete;

		/// <summary>
		/// 操作不被允许的回调
		/// </summary>
		/// <param name="command_name"> 操作名称 </param>
		/// <param name="state"> 操作被检测时播放器的状态 </param>
		virtual void on_command_not_allow(const std::string& command_name, QMedia::QPlayerState state) = 0;

	private:

	};
}