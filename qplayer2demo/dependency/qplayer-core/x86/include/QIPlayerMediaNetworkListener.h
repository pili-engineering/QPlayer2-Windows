#pragma once
#include <string>
#include "QOpenError.h"
#include "QPlayerExport.h"
#include "QUrlType.h"
namespace QMedia {
	/// <summary>
	/// ������������ؼ���
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
		/// ��ʼ����
		/// </summary>
		/// <param name="user_type"> ���� url �� userType </param>
		/// <param name="url_type">���� url �� urlType </param>
		/// <param name="url"> ������ url </param>
		/// <param name="retry_time"> ���� url �Ĵ��� </param>
		virtual void on_reconnect_start(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, int retry_time) = 0;

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="user_type"> ���� url �� userType </param>
		/// <param name="url_type"> ���� url �� urlType </param>
		/// <param name="url"> ������ url </param>
		/// <param name="retry_time"></param>
		/// <param name="error"> ���� url �Ĵ��� </param>
		virtual void on_reconnect_end(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, int retry_time, QMedia::QOpenError error) = 0;
		
		/// <summary>
		/// ��ʧ��
		/// </summary>
		/// <param name="user_type"> ��ʧ�� url �� userType </param>
		/// <param name="url_type"> ��ʧ�� url �� urlType </param>
		/// <param name="url"> ��ʧ�ܵ� url </param>
		/// <param name="error">  ��ʧ�� url �� ������ </param>
		virtual void on_open_failed(const std::string & user_type, QMedia::QUrlType url_type, const std::string & url, QMedia::QOpenError error) = 0;
	private:

	};
}
