#pragma once

#include "QPlayerExport.h"
#include "QPlayerState.h"

namespace QMedia {
	/// <summary>
	/// 播放状态监听
	/// </summary>
	class QPLAYER_API QIPlayerStateChangeListener {
	public:
		QIPlayerStateChangeListener() = default;

		virtual ~QIPlayerStateChangeListener() = default;

		QIPlayerStateChangeListener(const QIPlayerStateChangeListener&) = delete;

		QIPlayerStateChangeListener(QIPlayerStateChangeListener&&) = delete;

		QIPlayerStateChangeListener& operator=(const QIPlayerStateChangeListener&) = delete;

		QIPlayerStateChangeListener& operator=(QIPlayerStateChangeListener&&) = delete;

		/// <summary>
		/// 当前的播放状态发生改变时回调
		/// </summary>
		/// <param name="state"> 当前的播放状态 </param>
		virtual void on_state_changed(QMedia::QPlayerState state) = 0;
	};
}
