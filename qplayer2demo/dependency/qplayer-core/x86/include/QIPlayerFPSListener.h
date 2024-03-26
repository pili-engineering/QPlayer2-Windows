#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// ʵʱ fps ����
	/// </summary>
	class QPLAYER_API QIPlayerFPSListener
	{
	public:
		QIPlayerFPSListener() = default;
		virtual ~QIPlayerFPSListener() = default;
		QIPlayerFPSListener(const QIPlayerFPSListener&) = delete;

		QIPlayerFPSListener(QIPlayerFPSListener&&) = delete;

		QIPlayerFPSListener& operator=(const QIPlayerFPSListener&) = delete;

		QIPlayerFPSListener& operator=(QIPlayerFPSListener&&) = delete;

		/// <summary>
		/// fps �ı�ص�
		/// </summary>
		/// <param name="fps"> fps ֡�� </param>
		virtual void on_fps_changed(long fps) = 0;
	private:

	};
}
