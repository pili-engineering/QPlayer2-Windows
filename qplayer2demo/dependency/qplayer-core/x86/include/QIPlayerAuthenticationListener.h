#pragma once
#include "QAuthenticationErrorType.h"
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ¼øÈ¨¼àÌý
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
		/// ¼øÈ¨Ê§°Ü
		/// </summary>
		/// <param name="error"> ¼øÈ¨Ê§°Ü´íÎóÂë </param>
		virtual void on_authentication_failed(QMedia::QAuthenticationErrorType error) = 0;

		/// <summary>
		/// ¼øÈ¨³É¹¦
		/// </summary>
		virtual void on_authentication_success() = 0;
	private:

	};
}
