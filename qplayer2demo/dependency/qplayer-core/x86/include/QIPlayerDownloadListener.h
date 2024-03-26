#pragma once
#include "QPlayerExport.h"
#include <stdint.h>
namespace QMedia {
	/// <summary>
	/// ���ؼ���
	/// </summary>
	class QPLAYER_API QIPlayerDownloadListener
	{
	public:
		QIPlayerDownloadListener() = default;
		virtual ~QIPlayerDownloadListener() = default;
		QIPlayerDownloadListener(const QIPlayerDownloadListener&) = delete;

		QIPlayerDownloadListener(QIPlayerDownloadListener&&) = delete;

		QIPlayerDownloadListener& operator=(const QIPlayerDownloadListener&) = delete;

		QIPlayerDownloadListener& operator=(QIPlayerDownloadListener&&) = delete;

		/// <summary>
		/// �������ݱ仯�ص�
		/// </summary>
		/// <param name="download_speed"> �����ٶ� </param>
		/// <param name="buffer_pos"> ������� </param>
		virtual void on_download_changed(int64_t download_speed, int64_t buffer_pos) = 0;

	private:

	};
}