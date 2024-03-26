#pragma once
#include "QPlayerExport.h"
#include <windows.h>
#include "QPlayerSetting.h"
#include "QUrlType.h"
#include "QPlayerSetting.h"
#include "QIPlayerListenersHeader.h"

namespace QMedia {

	/// <summary>
	/// ��������Ⱦ���
	/// </summary>
	class QPLAYER_API QIPlayerRenderHandler  {
	public:
		QIPlayerRenderHandler() = default;

		virtual ~QIPlayerRenderHandler() = default;

		QIPlayerRenderHandler(const QIPlayerRenderHandler&) = delete;

		QIPlayerRenderHandler(QIPlayerRenderHandler&&) = delete;

		QIPlayerRenderHandler& operator=(const QIPlayerRenderHandler&) = delete;

		QIPlayerRenderHandler& operator=(QIPlayerRenderHandler&&) = delete;

		/// <summary>
		/// ���� hwnd
		/// </summary>
		/// <param name="hwnd"> ���������ھ�� </param>
		/// <returns> true ���óɹ� false ����ʧ�� </returns>
		virtual bool set_window_hwnd(HWND hwnd) = 0;
		
		/// <summary>
		/// ������Ⱦview�Ĵ�С
		/// </summary>
		/// <param name="width"> ��� </param>
		/// <param name="height"> �߶� </param>
		/// <returns> true ���óɹ� false ����ʧ�� </returns>
		virtual bool synch_window_size(uint16_t width, uint16_t height) = 0;

		/// <summary>
		/// ������Ƶ��Ⱦ����
		/// </summary>
		/// <param name="ratio"> ��Ⱦ���� </param>
		/// <returns> true ���óɹ� false ����ʧ�� </returns>
		virtual bool set_render_ratio(QPlayerSetting::QPlayerRenderRatio ratio) = 0;

		/// <summary>
		/// ����ɫ���Ż�
		/// </summary>
		/// <param name="blind_type"> ɫäģʽ </param>
		/// <returns> true ���óɹ� false ����ʧ�� </returns>
		virtual bool set_blind_type(QPlayerSetting::QPlayerBlind blind_type) = 0;

		/// <summary>
		/// ����VR��Ƶ����ת�Ƕ�(windows �ݲ�֧�� VR ��Ƶ)
		/// </summary>
		/// <param name="rotatex"> ����Ƕ� ��360���ƣ� </param>
		/// <param name="rotatey"> ����Ƕ� ��360���ƣ� </param>
		/// <returns> true ���óɹ� false ����ʧ�� </returns>
		//virtual bool set_panorama_view_rotate(float rotatex, float rotatey) = 0;

		/// <summary>
		/// �����Ⱦ����
		/// </summary>
		/// <param name="plistener"> ��Ⱦ���� </param>
		virtual void add_render_listener(QMedia::QIPlayerRenderListener* plistener) = 0;

		/// <summary>
		/// �Ƴ���Ⱦ����
		/// </summary>
		/// <param name="plistener"> ��Ⱦ���� </param>
		virtual void remove_render_listener(QMedia::QIPlayerRenderListener* plistener) = 0;

		/// <summary>
		/// �Ƴ����е���Ⱦ����
		/// </summary>
		virtual void remove_all_render_listeners() = 0;
	};
}