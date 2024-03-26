#pragma once
#include "QPlayerExport.h"
#include "QShootVideoType.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// ��ͼ����
	/// </summary>
	class QPLAYER_API QIPlayerShootVideoListener
	{
	public:
		QIPlayerShootVideoListener() = default;
		virtual ~QIPlayerShootVideoListener() = default;
		QIPlayerShootVideoListener(const QIPlayerShootVideoListener&) = delete;

		QIPlayerShootVideoListener(QIPlayerShootVideoListener&&) = delete;

		QIPlayerShootVideoListener& operator=(const QIPlayerShootVideoListener&) = delete;

		QIPlayerShootVideoListener& operator=(QIPlayerShootVideoListener&&) = delete;

		/// <summary>
		/// ��ͼ�ɹ��ص�
		/// </summary>
		/// <param name="image_data"> ͼƬ���� </param>
		/// <param name="size"> ͼƬ���ݵĳ��� </param>
		/// <param name="width"> ͼƬ�Ŀ�� </param>
		/// <param name="height"> ͼƬ�ĸ߶� </param>
		/// <param name="type"> ͼƬ���� </param>
		virtual void on_shoot_video_success(const std::unique_ptr<uint8_t[]>& image_data, uint64_t size, int width, int height, QMedia::QShootVideoType type) = 0;

		/// <summary>
		/// ��ͼʧ�ܻص�
		/// </summary>
		virtual void on_shoot_video_failed() = 0;

	private:

	};
}
