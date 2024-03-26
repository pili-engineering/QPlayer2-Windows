#pragma once
#include <string>
#include "QPlayerExport.h"
#include "QUrlType.h"
namespace QMedia {
	/// <summary>
	/// ��������������ؼ���
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
		/// ��ʼ�л�������
		/// </summary>
		/// <param name="user_type"> �л������ȵ� URL �� userType </param>
		/// <param name="url_type"> �л������ȵ� URL �� urlType </param>
		/// <param name="old_quality"> �л�������ǰ�������� </param>
		/// <param name="new_quality"> �л������Ⱥ�������� </param>
		virtual void on_quality_switch_start(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// �������л����
		/// </summary>
		/// <param name="user_type"> �л������ȵ� URL �� userType </param>
		/// <param name="url_type"> �л������ȵ� URL �� urlType </param>
		/// <param name="old_quality"> �л�������ǰ�������� </param>
		/// <param name="new_quality"> �л������Ⱥ�������� </param>
		virtual void on_quality_switch_complete(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// �������л�ȡ��
		/// </summary>
		/// <param name="user_type"> �л������ȵ� URL �� userType </param>
		/// <param name="url_type"> �л������ȵ� URL �� urlType </param>
		/// <param name="old_quality"> �л�������ǰ�������� </param>
		/// <param name="new_quality"> �л������Ⱥ�������� </param>
		virtual void on_quality_switch_canceled(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// �������л�ʧ��
		/// </summary>
		/// <param name="user_type"> �л������ȵ� URL �� userType </param>
		/// <param name="url_type"> �л������ȵ� URL �� urlType </param>
		/// <param name="old_quality"> �л�������ǰ�������� </param>
		/// <param name="new_quality"> �л������Ⱥ�������� </param>
		virtual void on_quality_switch_failed(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) = 0;

		/// <summary>
		/// Ŀǰ��֧��ͬʱ��һ���������л��¼������ǰһ���л���δ��ɣ��ٴ��л������ȣ����ص��ú���
		/// </summary>
		/// <param name="user_type"> �л������ȵ� URL �� userType </param>
		/// <param name="url_type"> �л������ȵ� URL �� urlType </param>
		virtual void on_quality_switch_retry_later(const std::string & user_type, QMedia::QUrlType url_type) = 0;
	private:

	};
}
