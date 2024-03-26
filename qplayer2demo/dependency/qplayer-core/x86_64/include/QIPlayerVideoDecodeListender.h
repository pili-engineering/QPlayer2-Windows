#pragma once
#include "QPlayerExport.h"
#include "QDecoderType.h"
namespace QMedia {
	/// <summary>
	/// �������������
	/// </summary>
	class QPLAYER_API QIPlayerVideoDecodeListender
	{
	public:
		QIPlayerVideoDecodeListender() = default;
		virtual ~QIPlayerVideoDecodeListender() = default;
		QIPlayerVideoDecodeListender(const QIPlayerVideoDecodeListender&) = delete;

		QIPlayerVideoDecodeListender(QIPlayerVideoDecodeListender&&) = delete;

		QIPlayerVideoDecodeListender& operator=(const QIPlayerVideoDecodeListender&) = delete;

		QIPlayerVideoDecodeListender& operator=(QIPlayerVideoDecodeListender&&) = delete;

		/// <summary>
		/// �������������ͻص�
		/// </summary>
		/// <param name="type"> �������� </param>
		virtual void on_video_decode_by_type(QMedia::QDecoderType type) = 0;

		/// <summary>
		/// ����ʧ�ܻص�
		/// </summary>
		/// <param name="retry"> �Ƿ񽵼����Գɹ� true �� false �� </param>
		virtual void on_decode_failed(bool retry) = 0;

		/// <summary>
		/// �����ǰ��Ƶ���������豸���� sdk ��֧�֣���ص��ú���
		/// </summary>
		/// <param name="codec_id"> ��Ƶ����� id  </param>
		virtual void on_not_support_codec_format(int codec_id) = 0;
	private:

	};
}
