#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 实时 fps 监听
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
		/// fps 改变回调
		/// </summary>
		/// <param name="fps"> fps 帧率 </param>
		virtual void on_fps_changed(long fps) = 0;
	private:

	};
}
