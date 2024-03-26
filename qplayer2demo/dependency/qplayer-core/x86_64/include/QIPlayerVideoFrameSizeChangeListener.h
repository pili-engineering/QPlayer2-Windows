#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ��������Ƶ����仯����
	/// </summary>
	class QPLAYER_API QIPlayerVideoFrameSizeChangeListener
	{
	public:
		QIPlayerVideoFrameSizeChangeListener() = default;
		virtual ~QIPlayerVideoFrameSizeChangeListener() = default;
		QIPlayerVideoFrameSizeChangeListener(const QIPlayerVideoFrameSizeChangeListener&) = delete;

		QIPlayerVideoFrameSizeChangeListener(QIPlayerVideoFrameSizeChangeListener&&) = delete;

		QIPlayerVideoFrameSizeChangeListener& operator=(const QIPlayerVideoFrameSizeChangeListener&) = delete;

		QIPlayerVideoFrameSizeChangeListener& operator=(QIPlayerVideoFrameSizeChangeListener&&) = delete;

		/// <summary>
		/// ��������Ƶ����仯�ص�
		/// </summary>
		/// <param name="width"> ��� </param>
		/// <param name="height"> �߶� </param>
		virtual void on_video_frame_size_changed(int width, int height) = 0;
	private:

	};
}
