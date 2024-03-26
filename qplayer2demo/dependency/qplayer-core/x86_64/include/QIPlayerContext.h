#pragma once
#include "QPlayerExport.h"
#include <string>
#include "QLogLevel.h"
#include <windows.h>

namespace QMedia {
    class QIPlayerRenderHandler;
    class QIPlayerControlHandler;

    /// <summary>
    /// 播放器 context
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
        /// 初始化播放器配置
        /// </summary>
        /// <param name="log_level"> 日志等级 </param>
        /// <param name="local_storage_dir"> 日志保存路径 </param>
        /// <param name="app_id"> app id </param>
        /// <param name="app_version"> app 版本号 </param>
        /// <param name="author_id"> author id </param>
        /// <param name="proc_hwnd"> 窗口句柄 </param>
        /// <returns></returns>
        virtual bool init(QLogLevel log_level, const std::string & local_storage_dir,
            const std::string & app_id, const std::string & app_version,
            const std::string & author_id, HWND proc_hwnd) = 0;

        /// <summary>
        /// 配置播放器事件循环
        /// </summary>
        /// <param name="hwnd"> 窗口句柄 </param>
        /// <param name="uMsg"> message </param>
        /// <param name="wParam"> wParam </param>
        /// <param name="lParam"> lParam </param>
        /// <returns> true 设置成功 false 设置失败 </returns>
        virtual bool on_receive_message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

        /// <summary>
        /// 释放播放器
        /// </summary>
        /// <returns> true 设置成功 false 设置失败 </returns>
        virtual  bool release() = 0;

        /// <summary>
        /// 创建播放器 context 
        /// </summary>
        /// <returns> 播放器 context </returns>
        static QIPlayerContext* create();


    };
}
