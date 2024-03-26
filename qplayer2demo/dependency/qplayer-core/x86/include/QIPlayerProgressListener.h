#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ���������ȼ���
	/// </summary>
	class QPLAYER_API QIPlayerProgressListener
	{
	public:
		QIPlayerProgressListener() = default;
		virtual ~QIPlayerProgressListener() = default;
		QIPlayerProgressListener(const QIPlayerProgressListener&) = delete;

		QIPlayerProgressListener(QIPlayerProgressListener&&) = delete;

		QIPlayerProgressListener& operator=(const QIPlayerProgressListener&) = delete;

		QIPlayerProgressListener& operator=(QIPlayerProgressListener&&) = delete;

		/// <summary>
		/// ���ȱ���ص�
		/// </summary>
		/// <param name="progress"> ��ǰ���� ��λ������ </param>
		/// <param name="duration"> ��ǰ��Ƶ��ʱ�� ��λ�� ���� </param>
		virtual void on_progress_changed(int64_t progress, int64_t duration) = 0;
	private:

	};
}
