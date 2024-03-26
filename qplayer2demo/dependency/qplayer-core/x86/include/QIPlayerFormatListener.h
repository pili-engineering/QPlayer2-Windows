#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ���ظ�ʽ������Ƶ sample ��ʽ��֧�ֵļ���
	/// </summary>
	class QPLAYER_API QIPlayerFormatListener
	{
	public:
		QIPlayerFormatListener() = default;
		virtual ~QIPlayerFormatListener() = default;
		QIPlayerFormatListener(const QIPlayerFormatListener&) = delete;

		QIPlayerFormatListener(QIPlayerFormatListener&&) = delete;

		QIPlayerFormatListener& operator=(const QIPlayerFormatListener&) = delete;

		QIPlayerFormatListener& operator=(QIPlayerFormatListener&&) = delete;

		/// <summary>
		/// ��ǰ�� format ��֧�֣���Ƶ�޷�����
		/// </summary>
		virtual void on_format_not_support() = 0;

	private:

	};
}