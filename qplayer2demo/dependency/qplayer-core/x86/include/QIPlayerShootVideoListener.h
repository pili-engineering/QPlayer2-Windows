#pragma once
#include "QPlayerExport.h"
#include "QShootVideoType.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// 截图监听
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
		/// 截图成功回调
		/// </summary>
		/// <param name="image_data"> 图片数据 </param>
		/// <param name="size"> 图片数据的长度 </param>
		/// <param name="width"> 图片的宽度 </param>
		/// <param name="height"> 图片的高度 </param>
		/// <param name="type"> 图片类型 </param>
		virtual void on_shoot_video_success(const std::unique_ptr<uint8_t[]>& image_data, uint64_t size, int width, int height, QMedia::QShootVideoType type) = 0;

		/// <summary>
		/// 截图失败回调
		/// </summary>
		virtual void on_shoot_video_failed() = 0;

	private:

	};
}
