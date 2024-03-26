#pragma once

#include "QPlayerExport.h"
#include "QPlayerState.h"

namespace QMedia {
	/// <summary>
	/// ����״̬����
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
		/// ��ǰ�Ĳ���״̬�����ı�ʱ�ص�
		/// </summary>
		/// <param name="state"> ��ǰ�Ĳ���״̬ </param>
		virtual void on_state_changed(QMedia::QPlayerState state) = 0;
	};
}
