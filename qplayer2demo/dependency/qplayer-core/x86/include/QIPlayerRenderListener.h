#pragma once

#include "QPlayerExport.h"

namespace QMedia {
	/// <summary>
	/// ��Ⱦ��ؼ���
	/// </summary>
	class QPLAYER_API QIPlayerRenderListener{
	public:
		QIPlayerRenderListener() = default;

		virtual ~QIPlayerRenderListener() = default;

		QIPlayerRenderListener(const QIPlayerRenderListener&) = delete;

		QIPlayerRenderListener(QIPlayerRenderListener&&) = delete;

		QIPlayerRenderListener& operator=(const QIPlayerRenderListener&) = delete;

		QIPlayerRenderListener& operator=(QIPlayerRenderListener&&) = delete;

		/// <summary>
		/// ��֡��ʱ�ص�
		/// </summary>
		/// <param name="elapsed_time"> �� play_media_model ��ʼ����֡��Ⱦ�������ܺ�ʱ ��λ������ </param>
		virtual void on_first_frame_rendered(int64_t elapsed_time) = 0;
	};
}
