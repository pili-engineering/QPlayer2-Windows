#pragma once
#include "QPlayerExport.h"
namespace QMedia {
	/// <summary>
	/// �����ٶȼ���
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
		/// �����ٶȸı�ص�
		/// </summary>
		/// <param name="speed"> ��ǰ�Ĳ����ٶ� </param>
		virtual void on_speed_changed(float speed) = 0;
	private:

	};
}
