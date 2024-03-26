#pragma once
#include "QLogLevel.h"
#include "QPlayerState.h"
#include <any>
#include <map>
#include <string>
#include "QPlayerNotify.h"
#include "QIPlayerContext.h"
#include "QMediaEnumHeader.h"
#include "QIPlayerStateChangeListener.h"
namespace QMedia {

    class PlayerControlHandlerImpl;
    class PlayerRenderHandlerImpl;
    class PlayerMessageLoopQueueAdapter;
    class QWindowsPlayer;
	class PlayerContextImpl : public QIPlayerContext , public QIPlayerStateChangeListener
	{

    public:
        PlayerContextImpl();

        ~PlayerContextImpl() override;

        PlayerContextImpl(const PlayerContextImpl&) = delete;

        PlayerContextImpl(PlayerContextImpl&&) = delete;

        PlayerContextImpl& operator=(const PlayerContextImpl&) = delete;

        PlayerContextImpl& operator=(PlayerContextImpl&&) = delete;

        QIPlayerRenderHandler* get_render_hander() const override;

        QIPlayerControlHandler* get_control_handler() const override;

        bool init(QLogLevel log_level, const std::string & local_storage_dir, 
            const std::string & app_id, const std::string & app_version, 
            const std::string & author_id, HWND proc_hwnd) override;
    
        bool on_receive_message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    
        bool release() override;


        void on_state_changed_sync(QMedia::QPlayerState state);

		void on_notify_async(QPlayerNotify notify_id, std::map<std::string, std::any>* pbundle);

    private:

        void on_state_changed(QMedia::QPlayerState state) override;

    private:

        QWindowsPlayer* mpInnerPlayer;
        PlayerControlHandlerImpl* mpPlayerControlHandler;
        PlayerRenderHandlerImpl* mpPlayerRenderHandler;
        PlayerMessageLoopQueueAdapter* mpPlayerMessageLoopQueueAdapter;
	};
}