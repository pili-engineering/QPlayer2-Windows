#pragma once
#include "QPlayerExport.h"
#include <memory>
namespace QMedia {
	/// <summary>
	/// SEI ���ݼ���
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
		/// SEI ���ݻص����һص�ʱ��Ϊ SEI ��������֡��ʱ��
		/// </summary>
		/// <param name="data"> SEI ���� </param>
		/// <param name="size"> SEI ���ݵĳ��� </param>
		virtual void on_sei_data(const std::unique_ptr<uint8_t[]>& data, uint64_t size) = 0;
	private:

	};
}
