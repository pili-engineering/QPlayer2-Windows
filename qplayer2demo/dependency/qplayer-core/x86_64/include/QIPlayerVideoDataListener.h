#pragma once
#include "QPlayerExport.h"
#include "QVideoType.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// ��Ƶ�������׼���
	/// </summary>
	class QPLAYER_API QIPlayerVideoDataListener
	{
	public:
		QIPlayerVideoDataListener() = default;
		virtual ~QIPlayerVideoDataListener() = default;
		QIPlayerVideoDataListener(const QIPlayerVideoDataListener&) = delete;

		QIPlayerVideoDataListener(QIPlayerVideoDataListener&&) = delete;

		QIPlayerVideoDataListener& operator=(const QIPlayerVideoDataListener&) = delete;

		QIPlayerVideoDataListener& operator=(QIPlayerVideoDataListener&&) = delete;

		/// <summary>
		/// ��Ƶ�������׻ص�
		/// </summary>
		/// <param name="width"> ��Ƶ��� </param>
		/// <param name="height"> ��Ƶ�߶� </param>
		/// <param name="video_type"> ��Ƶ���� </param>
		/// <param name="buffer"> ��Ƶ���� </param>
		/// <param name="size"> ��Ƶ���ݳ��� </param>
		virtual void on_video_data(int width, int height, QMedia::QVideoType video_type, const std::unique_ptr<uint8_t[]>& buffer, uint64_t size) = 0;
	private:

	};
}
