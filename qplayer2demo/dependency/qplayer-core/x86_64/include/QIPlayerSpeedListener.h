#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// 播放速度监听
	/// </summary>
	class QPLAYER_API QIPlayerSpeedListener
	{
	public:
		QIPlayerSpeedListener() = default;
		virtual ~QIPlayerSpeedListener() = default;
		QIPlayerSpeedListener(const QIPlayerSpeedListener&) = delete;

		QIPlayerSpeedListener(QIPlayerSpeedListener&&) = delete;

		QIPlayerSpeedListener& operator=(const QIPlayerSpeedListener&) = delete;

		QIPlayerSpeedListener& operator=(QIPlayerSpeedListener&&) = delete;

		/// <summary>
		/// 播放速度改变回调
		/// </summary>
		/// <param name="speed"> 当前的播放速度 </param>
		virtual void on_speed_changed(float speed) = 0;
	private:

	};
}
