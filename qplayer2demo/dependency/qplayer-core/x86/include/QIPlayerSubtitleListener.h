#pragma once
#include <string>
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ��Ļ��ؼ���
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
		/// ��Ļ�ı��ص�
		/// </summary>
		/// <param name="text"> ��ǰ��Ļ���ı� </param>
		virtual void on_subtitle_text_changed(const std::string & text) = 0;

		/// <summary>
		/// ��Ļ�л��ص�
		/// </summary>
		/// <param name="name"> ��ǰ����Ļ���� </param>
		virtual void on_subtitle_name_changed(const std::string & name) = 0;

		/// <summary>
		/// ��Ļ����״̬�ı�ص�
		/// </summary>
		/// <param name="enable"> ��ǰ��Ļ�Ƿ��� true ���� false �ر� </param>
		virtual void on_subtitle_enable(bool enable) = 0;

		/// <summary>
		/// ��Ļ���ؽ���ص�
		/// </summary>
		/// <param name="name"> ��Ļ���� </param>
		/// <param name="result"> ��Ļ���ؽ�� true �ɹ� false ʧ�� </param>
		virtual void on_subtitle_loaded(const std::string & name, bool result) = 0;

		/// <summary>
		/// ��Ļ�������ص�
		/// </summary>
		/// <param name="name"> ��Ļ���� </param>
		/// <param name="result"> ��Ļ������ true �ɹ� false ʧ�� </param>
		virtual void on_subtitle_decoded(const std::string & name, bool result) = 0;
	private:

	};
}
