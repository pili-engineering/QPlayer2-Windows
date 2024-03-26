#pragma once
#include "QPlayerExport.h"
#include <string>
#include "QLogLevel.h"
#include <windows.h>

namespace QMedia {
    class QIPlayerRenderHandler;
    class QIPlayerControlHandler;

    /// <summary>
    /// ������ context
    /// </summary>
    class QPLAYER_API QIPlayerContext {
    public:
        QIPlayerContext() = default;

        virtual ~QIPlayerContext() = default;

        QIPlayerContext(const QIPlayerContext&) = delete;

        QIPlayerContext(QIPlayerContext&&) = delete;

        QIPlayerContext& operator=(const QIPlayerContext&) = delete;

        QIPlayerContext& operator=(QIPlayerContext&&) = delete;

        virtual QIPlayerRenderHandler* get_render_hander() const = 0;

        virtual QIPlayerControlHandler* get_control_handler() const = 0;

        /// <summary>
        /// ��ʼ������������
        /// </summary>
        /// <param name="log_level"> ��־�ȼ� </param>
        /// <param name="local_storage_dir"> ��־����·�� </param>
        /// <param name="app_id"> app id </param>
        /// <param name="app_version"> app �汾�� </param>
        /// <param name="author_id"> author id </param>
        /// <param name="proc_hwnd"> ���ھ�� </param>
        /// <returns></returns>
        virtual bool init(QLogLevel log_level, const std::string & local_storage_dir,
            const std::string & app_id, const std::string & app_version,
            const std::string & author_id, HWND proc_hwnd) = 0;

        /// <summary>
        /// ���ò������¼�ѭ��
        /// </summary>
        /// <param name="hwnd"> ���ھ�� </param>
        /// <param name="uMsg"> message </param>
        /// <param name="wParam"> wParam </param>
        /// <param name="lParam"> lParam </param>
        /// <returns> true ���óɹ� false ����ʧ�� </returns>
        virtual bool on_receive_message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

        /// <summary>
        /// �ͷŲ�����
        /// </summary>
        /// <returns> true ���óɹ� false ����ʧ�� </returns>
        virtual  bool release() = 0;

        /// <summary>
        /// ���������� context 
        /// </summary>
        /// <returns> ������ context </returns>
        static QIPlayerContext* create();


    };
}
