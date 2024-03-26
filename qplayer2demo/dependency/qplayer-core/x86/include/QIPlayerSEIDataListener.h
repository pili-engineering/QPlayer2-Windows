#pragma once
#include "QPlayerExport.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// SEI 数据监听
	/// </summary>
	class QPLAYER_API QIPlayerSEIDataListener
	{
	public:
		QIPlayerSEIDataListener() = default;
		virtual ~QIPlayerSEIDataListener() = default;
		QIPlayerSEIDataListener(const QIPlayerSEIDataListener&) = delete;

		QIPlayerSEIDataListener(QIPlayerSEIDataListener&&) = delete;

		QIPlayerSEIDataListener& operator=(const QIPlayerSEIDataListener&) = delete;

		QIPlayerSEIDataListener& operator=(QIPlayerSEIDataListener&&) = delete;

		/// <summary>
		/// SEI 数据回调，且回调时机为 SEI 数据所在帧的时间
		/// </summary>
		/// <param name="data"> SEI 数据 </param>
		/// <param name="size"> SEI 数据的长度 </param>
		virtual void on_sei_data(const std::unique_ptr<uint8_t[]>& data, uint64_t size) = 0;
	private:

	};
}
