#pragma once
#include "QAuthenticationErrorType.h"
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ��Ȩ����
	/// </summary>
	class QPLAYER_API QIPlayerAuthenticationListener
	{
	public:
		QIPlayerAuthenticationListener() = default;
		virtual ~QIPlayerAuthenticationListener() = default;
		QIPlayerAuthenticationListener(const QIPlayerAuthenticationListener&) = delete;

		QIPlayerAuthenticationListener(QIPlayerAuthenticationListener&&) = delete;

		QIPlayerAuthenticationListener& operator=(const QIPlayerAuthenticationListener&) = delete;

		QIPlayerAuthenticationListener& operator=(QIPlayerAuthenticationListener&&) = delete;

		/// <summary>
		/// ��Ȩʧ��
		/// </summary>
		/// <param name="error"> ��Ȩʧ�ܴ����� </param>
		virtual void on_authentication_failed(QMedia::QAuthenticationErrorType error) = 0;

		/// <summary>
		/// ��Ȩ�ɹ�
		/// </summary>
		virtual void on_authentication_success() = 0;
	private:

	};
}
