#pragma once
#include "QPlayerExport.h"
#include "QPlayerState.h"
#include <string>
namespace QMedia {
	/// <summary>
	/// ���ò������ӿ�ʱ״̬�쳣�ļ���
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
		/// ������������Ļص�
		/// </summary>
		/// <param name="command_name"> �������� </param>
		/// <param name="state"> ���������ʱ��������״̬ </param>
		virtual void on_command_not_allow(const std::string& command_name, QMedia::QPlayerState state) = 0;

	private:

	};
}